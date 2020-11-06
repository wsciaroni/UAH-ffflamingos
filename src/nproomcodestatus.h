#ifndef NPROOMCODESTATUS_H
#define NPROOMCODESTATUS_H

#include "nphosttoguest.h"

class NPRoomCodeStatus : public NPHostToGuest
{
private:
    /**
     * @copydoc NPHostToGuest::packetType
     */
    PacketType packetType = PacketType::ROOMCODESTATUS;

    /**
     * Holds True if the room code provided by the client matched the room code on the host
     */
    bool roomCodeStatus;

public:
    NPRoomCodeStatus(/* args */);
    ~NPRoomCodeStatus();

    /**
     * Set True when the room codes match
     */
    void setRoomCodeStatus(bool newStatus);

    /**
     * Used to determine the status of the room codes
     * @return true when the room codes match
     */
    bool getRoomCodeStatus();
};

#endif // NPROOMCODESTATUS_H