#include "hostnetworkhandler.h"
#include "error.h"
#include <QNetworkProxy>

HostNetworkHandler::HostNetworkHandler(QObject* parent) : QObject(parent) {
  connect(&tcpServer, &QTcpServer::newConnection, this,
          &HostNetworkHandler::onNewTCPConnection);

  udpServer.setProxy(QNetworkProxy::NoProxy);
}

HostNetworkHandler::~HostNetworkHandler() {
  stopTCPServer();

  const QObjectList& list = tcpServer.children();
  for (int i = 0; i < list.length(); i++) {
    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(list[i]);

    if (tcp != nullptr) {
      tcp->close();
    }
  }
}

bool HostNetworkHandler::startTCPServer(QHostAddress hostAddress, int portIn) {
  if (tcpServer.isListening()) {
    stopTCPServer();
  }
  port = portIn;
  return tcpServer.listen(hostAddress, port);
}

void HostNetworkHandler::stopTCPServer() {
  if (tcpServer.isListening()) {
    tcpServer.close();
  }
}

QTcpServer* HostNetworkHandler::getTCPServer() { return &tcpServer; }

void HostNetworkHandler::onNewTCPConnection() {

  QTcpSocket* tcpSocket =
      tcpServer.nextPendingConnection();  // Pass this tcp socket to the

  tcpSocket->setProxy(QNetworkProxy::NoProxy);

  connect(tcpSocket, &QTcpSocket::connected, this,
          &HostNetworkHandler::onTCPConnected);
  connect(tcpSocket, &QTcpSocket::disconnected, this,
          &HostNetworkHandler::onTCPDisconnected);
  connect(tcpSocket, &QTcpSocket::readyRead, this,
          &HostNetworkHandler::onTCPDataReady);

  connect(tcpSocket, SIGNAL(bytesWritten(qint64)), this,
          SLOT(onTCPBytesWritten(qint64)));
}

void HostNetworkHandler::onTCPConnected() {
  QTcpSocket* tcpSocket = dynamic_cast<QTcpSocket*>(sender());
  tcpSocket->setProxy(QNetworkProxy::NoProxy);
  if (tcpSocket != nullptr) {
    qDebug() << "In onTCPConnected()\n";
  }
}

void HostNetworkHandler::onTCPDisconnected() {
  qDebug() << "In onTCPDisconnected()\n";
  QTcpSocket* tcpSocket = dynamic_cast<QTcpSocket*>(sender());
  emit this->hostHandleGuestTerminated(tcpSocket);
}

void HostNetworkHandler::onTCPDataReady() {
  qDebug() << "In onTCPDataReady()";
  QTcpSocket* tcpSocket = dynamic_cast<QTcpSocket*>(sender());
  while (tcpSocket->bytesAvailable()) {
    qDebug() << "In LOOP onTCPDataReady()";
    tcpSocket->setProxy(QNetworkProxy::NoProxy);
    // Read from socket here
    PacketType pType;
    BlockReader(tcpSocket).stream() >> pType;
    if (pType == PacketType::PROVIDEROOMCODE) {

      qDebug() << "pType == PROVIDEROOMCODE";
      NPProvideRoomCode provideRoomCodePacket;

      QString roomcode;
      int uid;
      QString name;
      BlockReader(tcpSocket).stream() >> uid >> roomcode >> name;
      provideRoomCodePacket.setRoomCode(roomcode);
      provideRoomCodePacket.setUID(uid);
      provideRoomCodePacket.setName(name);
      qDebug() << "Room code received" << uid << " " << roomcode;
      emit this->provideRoomCode(provideRoomCodePacket, tcpSocket);

    } else if (pType == PacketType::SPACEPRESSED) {
      qDebug() << "pType == SPACEPRESSED";
      NPSpacePressed spacePressedPacket;

      int uid;
      BlockReader(tcpSocket).stream() >> uid;
      spacePressedPacket.setUID(uid);
      emit this->spacePressed(spacePressedPacket, tcpSocket);
    } else if (pType == PacketType::NULLPACKETTYPE) {
      qDebug() << "pType == NULLPACKETTYPE";
      // Throw an error
      error* throwError = new error;
      throwError->throwErrorMsg("ERROR: Received a NULL packet type");
      throwError->exec();
      delete throwError;
    } else {
      qDebug() << "Unknown packet type";
    }

    qDebug() << "In LOOP onTCPDataReady()";
  }
  qDebug() << "out of onTCPDataReady()";
}

void HostNetworkHandler::onTCPBytesWritten(qint64 bytes) {
  qDebug() << "In onTCPBytesWritten()\n";
}

int HostNetworkHandler::getPort() { return port; }

void HostNetworkHandler::sendRoomCodeStatus(NPRoomCodeStatus roomCodeStatus,
                                            QTcpSocket* socket) {
  // BlockWriter(socket).stream() << roomCodeStatus;
  qDebug() << "sent room code status\n";
  bool status = roomCodeStatus.getRoomCodeStatus();
  BlockWriter(socket).stream() << PacketType::ROOMCODESTATUS;
  BlockWriter(socket).stream() << status;
}

void HostNetworkHandler::sendWelcomeToRoom(NPWelcomeToRoom welcomeToRoom,
                                           QTcpSocket* socket) {
  BlockWriter(socket).stream() << PacketType::WELCOMETOROOM;
}

void HostNetworkHandler::sendInGameInfo(NPInGameInfo inGameInfo,
                                        QHostAddress destinationAddress) {
  QByteArray datagram;
  QDataStream out(&datagram, QIODevice::WriteOnly);
  out << inGameInfo;
  udpServer.writeDatagram(datagram, destinationAddress, port);
}

void HostNetworkHandler::sendEndGameInfo(NPEndGameInfo endGameInfo,
                                         QTcpSocket* socket) {
  // BlockWriter(socket).stream() << endGameInfo;
  BlockWriter(socket).stream() << PacketType::ENDGAMEINFO;
}
