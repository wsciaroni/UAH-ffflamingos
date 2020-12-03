#include "playermodel.h"

void PlayerModel::setUID(int uid) { this->uid = uid; }

bool PlayerModel::allowedToLunge() {
  if (!timersEnabled) {
    return false;
  }
  if (animationLocked) {
    return false;
  } else if (numPressesSinceTimeReset > numAllowedInTime) {
    return false;
  }
  numPressesSinceTimeReset++;
  return true;
}

PlayerModel::PlayerModel(int uid, QTcpSocket* socket) {
  setUID(uid);
  setTCPSocket(socket);
}

PlayerModel::PlayerModel(int uid) {
  setUID(uid);
  timersEnabled = false;
}

PlayerModel::~PlayerModel() {}

int PlayerModel::getUID() { return uid; }

void PlayerModel::setName(QString name) { this->userName = name; }

QString PlayerModel::getName() { return userName; }

void PlayerModel::setTCPSocket(QTcpSocket* socket) { this->tcpsockt = socket; }

QTcpSocket* PlayerModel::getTCPSocket() { return tcpsockt; }

void PlayerModel::setScore(int score) { this->score = score; }

void PlayerModel::increaseScore(int delta) { score += delta; }

int PlayerModel::getScore() { return score; }

void PlayerModel::setPositionId(PlayerPosition position) {
  this->positionID = position;
}

PlayerPosition PlayerModel::getPositionId() { return this->positionID; }

void PlayerModel::enableTimers() {
  timersEnabled = true;
  coolDownTimer.start(cooldownPeriod);
  connect(&coolDownTimer, &QTimer::timeout, this,
          &PlayerModel::resetCooldownPeriod);
}

void PlayerModel::disableTimers() {
  timersEnabled = false;
  coolDownTimer.stop();
}

bool PlayerModel::spacePressed() {
  if (allowedToLunge()) {
    QTimer::singleShot(animationPeriod, this, &PlayerModel::animationDone);
    animationLocked = true;
    return true;
  }
  return false;
}

bool PlayerModel::isExtended() { return animationLocked; }

void PlayerModel::animationDone() { animationLocked = false; }

void PlayerModel::resetCooldownPeriod() { numPressesSinceTimeReset = 0; }