#include "guestnetworkhandler.h"
#include "error.h"
#include <QNetworkProxy>

GuestNetworkHandler::GuestNetworkHandler(QObject* parent) : QObject(parent) {
  tcpSocket.setProxy(QNetworkProxy::NoProxy);
}

GuestNetworkHandler::~GuestNetworkHandler() {}

bool GuestNetworkHandler::connectToHost(QHostAddress hostAddress,
                                        QString portIn) {
  if (!tcpSocket.isOpen()) {
    port = portIn.toInt();
    tcpSocket.setProxy(QNetworkProxy::NoProxy);
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
  tcpSocket.flush();
  tcpSocket.close();
  return false;
}

void GuestNetworkHandler::disconnectFromHost() {
  if (tcpSocket.isOpen()) {
    tcpSocket.close();
  }
}

QTcpSocket* GuestNetworkHandler::getTcpSocket() { return &tcpSocket; }

void GuestNetworkHandler::onTCPConnected() {}

void GuestNetworkHandler::onTCPDisconnected() {
  emit this->tcpConnectionDropped();
}

void GuestNetworkHandler::onTCPDataReady() {
  QTcpSocket* tcpSocket = dynamic_cast<QTcpSocket*>(sender());
  while (tcpSocket->bytesAvailable()) {
    // Read from socket here
    PacketType pType;
    BlockReader(tcpSocket).stream() >> pType;
    if (pType == PacketType::ROOMCODESTATUS) {
      NPRoomCodeStatus roomCodeStatus;
      bool status;
      BlockReader(tcpSocket).stream() >> status;
      roomCodeStatus.setRoomCodeStatus(status);
      emit this->recvRoomCodeStatus(roomCodeStatus);
    } else if (pType == PacketType::ENDGAMEINFO) {
      NPEndGameInfo endGameInfo;
      QString winnerName, highScoreHolderName;
      qint32 winnerScore, highScore;
      BlockReader(tcpSocket).stream() >> highScoreHolderName >> highScore >>
          winnerName >> winnerScore;
      endGameInfo.setHighScoreInfo(highScoreHolderName, highScore);
      endGameInfo.setWinnerInfo(winnerName, winnerScore);
      emit this->recvEndGameInfo(endGameInfo);
    } else if (pType == PacketType::WELCOMETOROOM) {
      NPWelcomeToRoom welcomeToRoom;
      QString names[6];
      for (int i = 0; i < 6; i++) {
        BlockReader(tcpSocket).stream() >> names[i];
      }
      welcomeToRoom.setNames(names);
      emit this->recvWelcomeToRoom(welcomeToRoom);
    } else if (pType == PacketType::INGAMEINFO) {
      NPInGameInfo packet;
      for (int i = 0; i < 25; i++) {
        qint32 xPos, yPos;
        BlockReader(tcpSocket).stream() >> xPos >> yPos;
        packet.setBallPosition(i, xPos, yPos);
      }
      for (int i = 0; i < 6; i++) {
        qint32 score;
        bool isExtended;
        BlockReader(tcpSocket).stream() >> score >> isExtended;
        packet.setPlayerScore(i, score);
        packet.setPlayerExtension(i, isExtended);
      }
      packet.setPlayerExtension(0, false);
      qint32 timeRemaining = -1;
      BlockReader(tcpSocket).stream() >> timeRemaining;
      packet.setTimeRemaining(timeRemaining);
      emit this->recvInGameInfo(packet);
    } else if (pType == PacketType::NULLPACKETTYPE) {
      // Throw an error
      error* throwError = new error;
      throwError->throwErrorMsg("ERROR: Received a NULL packet type");
      throwError->exec();
      delete throwError;
    }
  }
}

void GuestNetworkHandler::provideRoomCode(
    NPProvideRoomCode provideRoomCodePacket) {

  QString roomcode = provideRoomCodePacket.getRoomCode();
  QString name = provideRoomCodePacket.getName();
  int uid = provideRoomCodePacket.getUID();
  BlockWriter(&tcpSocket).stream() << PacketType::PROVIDEROOMCODE;
  BlockWriter(&tcpSocket).stream() << uid << roomcode << name;
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
