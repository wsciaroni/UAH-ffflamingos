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