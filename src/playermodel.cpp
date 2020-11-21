#include "playermodel.h"

void PlayerModel::setUID(int uid) { this->uid = uid; }

bool PlayerModel::allowedToLunge() {
  // This is what happens when grading occurs based on SLOC
  qDebug() << "Checking for lunge ability";
  if (!timersEnabled) {
    return false;
  }
  qDebug() << "Timers Enabled";
  if (animationLocked) {
    qDebug() << "Animation is locked";
    return false;
  } else if (numPressesSinceTimeReset > numAllowedInTime) {
    qDebug() << "Number of presses too high";
    return false;
  }
  qDebug() << "Allowed to lunge";
  numPressesSinceTimeReset++;
  return true;
}

PlayerModel::PlayerModel(int uid, QTcpSocket* socket) {
  setUID(uid);
  setTCPSocket(socket);
}

PlayerModel::PlayerModel(int uid) { setUID(uid); }

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

void PlayerModel::disableTimers() {}

bool PlayerModel::spacePressed() {
  if (allowedToLunge()) {
    QTimer::singleShot(animationPeriod, this, &PlayerModel::animationDone);
    animationLocked = true;
    return true;
  }
  return false;
}

void PlayerModel::animationDone() { animationLocked = false; }

void PlayerModel::resetCooldownPeriod() { numPressesSinceTimeReset = 0; }