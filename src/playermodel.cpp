#include "playermodel.h"

void PlayerModel::setUID(int uid) {
    this->uid = uid;
}

bool PlayerModel::allowedToLunge() {
    // This is what happens when grading occurs based on SLOC
    if (!timersEnabled)
    {
        return false;
    }
    else if (animationLocked)
    {
        return false;
    }
    else if (numPressesSinceTimeReset > numAllowedInTime)
    {
        return false;
    }
    return true;
}

PlayerModel::PlayerModel(int uid, QTcpSocket* socket) {
    setUID(uid);
    setTCPSocket(socket);
}

PlayerModel::~PlayerModel() {

}

int PlayerModel::getUID() {
    return uid;
}

void PlayerModel::setName(QString name) {
    this->userName = name;
}

QString PlayerModel::getName() {
    return userName;
}

void PlayerModel::setTCPSocket(QTcpSocket* socket) {
    this->tcpsockt = socket;
}

QTcpSocket* PlayerModel::getTCPSocket() {
    return tcpsockt;
}

void PlayerModel::setScore(int score) {
    this->score = score;
}

void PlayerModel::increaseScore(int delta) {
    score += delta;
}

int PlayerModel::getScore() {
    return score;
}

void PlayerModel::setPositionId(PlayerPosition position) {
    this->positionID = position;
}

PlayerPosition PlayerModel::getPositionId() {
    return this->positionID;
}

void PlayerModel::enableTimers() {
    timersEnabled = true;
    coolDownTimer.start(cooldownPeriod);
}

void PlayerModel::disableTimers() {
    
}

bool PlayerModel::spacePressed() {
    numPressesSinceTimeReset++;
    if (allowedToLunge())
    {
        animationTimer.start(animationPeriod);
        return true;
    }
    return false;
}

void PlayerModel::animationDone() {
    animationLocked = false;
}

void PlayerModel::resetCooldownPeriod() {
    numPressesSinceTimeReset = 0;
}