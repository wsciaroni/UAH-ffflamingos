#include "npprovideroomcode.h"
#include <QDebug>

NPProvideRoomCode::NPProvideRoomCode(/* args */) {}

NPProvideRoomCode::~NPProvideRoomCode() {}

void NPProvideRoomCode::setRoomCode(QString roomcode) { roomCode = roomcode; }

void NPProvideRoomCode::setName(QString name) { playerName = name; }

QString NPProvideRoomCode::getRoomCode() { return roomCode; }

QString NPProvideRoomCode::getName() { return playerName; }
