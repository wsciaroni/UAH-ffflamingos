#include "nproomcodestatus.h"

NPRoomCodeStatus::NPRoomCodeStatus(/* args */)
{
}

NPRoomCodeStatus::~NPRoomCodeStatus()
{
}

void NPRoomCodeStatus::setRoomCodeStatus(bool newStatus) {
    roomCodeStatus = newStatus;
}

bool NPRoomCodeStatus::getRoomCodeStatus() {
    return roomCodeStatus;
}

QDataStream& operator<<(QDataStream& ds, NPRoomCodeStatus& packet) {
    ds << packet.getPacketType();

    return ds;
}

QDataStream& operator>>(QDataStream& ds, NPRoomCodeStatus& packet) {
    
    return ds;
}