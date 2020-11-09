#include "npprovideroomcode.h"


NPProvideRoomCode::NPProvideRoomCode(/* args */)
{
}

NPProvideRoomCode::~NPProvideRoomCode()
{
}

void NPProvideRoomCode::setRoomCode(QString roomcode) {
    roomCode = roomcode;
}

QString NPProvideRoomCode::getRoomCode() {
    return roomCode;
}

QDataStream& operator<<(QDataStream& ds, NPProvideRoomCode& packet) {
    ds << packet.getPacketType();

    return ds;
}

QDataStream& operator>>(QDataStream& ds, NPProvideRoomCode& packet) {
    
    return ds;
}