#include "npingameinfo.h"

NPInGameInfo::NPInGameInfo(/* args */) {}

NPInGameInfo::~NPInGameInfo() {}

QDataStream& operator<<(QDataStream& ds, NPInGameInfo& packet) {
  for (int i = 0; i < 25; i++) {
    ds << packet.getBallPosX(i) << packet.getBallPosY(i);
  }
  for (int i = 0; i < 6; i++) {
    ds << packet.getPlayerScore(i) << packet.isPlayerExtended(i);
  }
  return ds;
}

QDataStream& operator>>(QDataStream& ds, NPInGameInfo& packet) {
  for (int i = 0; i < 25; i++) {
    qint32 xPos, yPos;
    ds >> xPos >> yPos;
    packet.setBallPosition(i, xPos, yPos);
  }
  for (int i = 0; i < 6; i++) {
    qint32 score;
    bool isExtended;
    ds >> score >> isExtended;
    packet.setPlayerScore(i, score);
    packet.setPlayerExtension(i, isExtended);
  }
  packet.setPlayerExtension(0, false);
  return ds;
}

void NPInGameInfo::setBallPosition(qint32 ballNum, qint32 xCoord,
                                   qint32 yCoord) {
  // Invalid ball number
  if (!isBallPosValid(ballNum)) {
    return;
  }

  ballsX[ballNum] = xCoord;
  ballsY[ballNum] = yCoord;
}

qint32* NPInGameInfo::getBallPos(qint32 ballNum) {
  if (!isBallPosValid(ballNum)) {
    return NULL;
  }
  qint32 xCoord = ballsX[ballNum];
  qint32 yCoord = ballsY[ballNum];
  qint32 returnVal[] = {xCoord, yCoord};
  return returnVal;
}

bool NPInGameInfo::isBallPosValid(qint32 ballNum) {
  return (ballNum <= 24 && ballNum >= 0);
}

qint32 NPInGameInfo::getBallPosY(qint32 ballNum) {
  if (!isBallPosValid(ballNum)) {
    return NULL;
  }
  return ballsY[ballNum];
}

qint32 NPInGameInfo::getBallPosX(qint32 ballNum) {
  if (!isBallPosValid(ballNum)) {
    return NULL;
  }
  return ballsX[ballNum];
}

void NPInGameInfo::setPlayerScore(qint32 playerNum, qint32 score) {
  if (!isPlayerNumValid(playerNum)) {
    return;
  }
  scores[playerNum] = score;
}

qint32 NPInGameInfo::getPlayerScore(qint32 playerNum) {
  if (!isPlayerNumValid(playerNum)) {
    return NULL;
  }
  return scores[playerNum];
}

bool NPInGameInfo::isPlayerNumValid(qint32 playerNum) {
  return (playerNum >= 0 && playerNum <= 5);
}

bool NPInGameInfo::isPlayerExtended(qint32 playerNum) {
  if (!isPlayerNumValid(playerNum)) {
    return NULL;
  }
  return playerExtended[playerNum];
}
void NPInGameInfo::setPlayerExtension(qint32 playerNum, bool isExtended) {
  if (!isPlayerNumValid(playerNum)) {
    return;
  }
  playerExtended[playerNum] = isExtended;
}

void NPInGameInfo::setTimeRemaining(qint32 secondsRemaining) {
  if (secondsRemaining >= 0) {
    timeRemaining = secondsRemaining;
  } else {
    timeRemaining = 0;
  }
}

qint32 NPInGameInfo::getTimeRemaining() { return timeRemaining; }