#include "guestnetworkhandler.h"
#include "error.h"
#include <QNetworkProxy>

GuestNetworkHandler::GuestNetworkHandler(QObject* parent) : QObject(parent) {
  tcpSocket.setProxy(QNetworkProxy::NoProxy);
  udpSocket.setProxy(QNetworkProxy::NoProxy);
}

GuestNetworkHandler::~GuestNetworkHandler() {}

bool GuestNetworkHandler::connectToHost(QHostAddress hostAddress,
                                        QString portIn) {
  if (!tcpSocket.isOpen()) {
    port = portIn.toInt();
    tcpSocket.connectToHost(hostAddress, port);
    if (tcpSocket.waitForConnected(3000)) {

      connect(&tcpSocket, &QTcpSocket::connected, this,
              &GuestNetworkHandler::onTCPConnected);

      connect(&tcpSocket, &QTcpSocket::disconnected, this,
              &GuestNetworkHandler::onTCPDisconnected);
      connect(&tcpSocket, &QTcpSocket::readyRead, this,
              &GuestNetworkHandler::onTCPDataReady);
      return true;
    }
  }
  return false;
}

void GuestNetworkHandler::disconnectFromHost() {
  if (tcpSocket.isOpen()) {
    tcpSocket.close();
  }
}

bool GuestNetworkHandler::listenOnUDP() {
  if (udpSocket.isOpen()) {
    udpSocket.close();
  }
  bool status = udpSocket.bind(QHostAddress::AnyIPv4, port);
  status = udpSocket.joinMulticastGroup(multicastAddress);
  connect(&udpSocket, &QUdpSocket::readyRead, this,
          &GuestNetworkHandler::onUDPReadPendingDatagrams);
  return status;
}

void GuestNetworkHandler::stopListeningOnUDP() {
  if (udpSocket.isOpen()) {
    udpSocket.close();
  }
}

void GuestNetworkHandler::onTCPConnected() {
  qDebug() << "In client onTCPConnected()";
}

void GuestNetworkHandler::onTCPDisconnected() {
  qDebug() << "In client onTCPDisconnected()";

  emit this->tcpConnectionDropped();
}

void GuestNetworkHandler::onTCPDataReady() {
  qDebug() << "In onTCPDataReady()\n";
  QTcpSocket* tcpSocket = dynamic_cast<QTcpSocket*>(sender());
  while (tcpSocket->bytesAvailable()) {
    // Read from socket here
    PacketType pType;
    BlockReader(tcpSocket).stream() >> pType;
    if (pType == PacketType::ROOMCODESTATUS) {
      qDebug() << "pType == ROOMCODESTATUS\n";
      NPRoomCodeStatus roomCodeStatus;
      bool status;
      BlockReader(tcpSocket).stream() >> status;
      roomCodeStatus.setRoomCodeStatus(status);
      qDebug() << "Room Code Status Received";
      emit this->recvRoomCodeStatus(roomCodeStatus);
    } else if (pType == PacketType::ENDGAMEINFO) {
      qDebug() << "pType == ENDGAMEINFO\n";
      NPEndGameInfo endGameInfo;
      // BlockReader(tcpSocket).stream() >> spacePressedPacket;
      emit this->recvEndGameInfo(endGameInfo);
    } else if (pType == PacketType::WELCOMETOROOM) {
      qDebug() << "pType == WELCOMETOROOM\n";
      NPWelcomeToRoom welcomeToRoom;
      // BlockReader(tcpSocket).stream() >> spacePressedPacket;
      emit this->recvWelcomeToRoom(welcomeToRoom);
    } else if (pType == PacketType::NULLPACKETTYPE) {
      qDebug() << "pType == NULLPACKETTYPE\n";
      // Throw an error
      error* throwError = new error;
      throwError->throwErrorMsg("ERROR: Received a NULL packet type");
      throwError->exec();
      delete throwError;
    } else {
      qDebug() << "Unknown packet type\n";
    }
  }
}

void GuestNetworkHandler::onTCPBytesWritten() {}

void GuestNetworkHandler::onUDPReadPendingDatagrams() {
  qDebug() << "In onUDPReadPendingDatagrams()";
  QByteArray datagram;

  while (udpSocket.hasPendingDatagrams()) {
    datagram.resize(int(udpSocket.pendingDatagramSize()));
    udpSocket.readDatagram(datagram.data(), datagram.size());

    // Process the incoming datagram

    NPInGameInfo inGameInfo;
    QDataStream in(&datagram, QIODevice::ReadOnly);

    in >> inGameInfo;
    emit this->recvInGameInfo(inGameInfo);
  }
}

void GuestNetworkHandler::provideRoomCode(
    NPProvideRoomCode provideRoomCodePacket) {

  QString roomcode = provideRoomCodePacket.getRoomCode();
  QString name = provideRoomCodePacket.getName();
  int uid = provideRoomCodePacket.getUID();
  BlockWriter(&tcpSocket).stream() << PacketType::PROVIDEROOMCODE;
  BlockWriter(&tcpSocket).stream() << uid << roomcode << name;
  qDebug() << "room code provided";
}

void GuestNetworkHandler::terminateMe(NPTerminateMe terminateMePacket) {
  int uid = terminateMePacket.getUID();
  BlockWriter(&tcpSocket).stream() << PacketType::TERMINATEME;
  BlockWriter(&tcpSocket).stream() << uid;
}

void GuestNetworkHandler::spacePressed(NPSpacePressed spacePressedPacket) {

  int uid = spacePressedPacket.getUID();
  BlockWriter(&tcpSocket).stream() << PacketType::SPACEPRESSED;
  BlockWriter(&tcpSocket).stream() << uid;
}
