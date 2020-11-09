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

    /**
     * Reimplements the `<<` operator for QDataStream.
     * This is used to send the data in a specific order
     */
    friend QDataStream& operator<<(QDataStream& ds, NPRoomCodeStatus& packet);

    /**
     * Reimplements the `>>` operator for QDataStream.
     * This is used to receive the data in a specific order.
     * @warning Do not attempt to read in the Packet type as that will be done externally to determine what type of packet to read in for the remaining data.
     */
    friend QDataStream& operator>>(QDataStream& ds, NPRoomCodeStatus& packet);
};

#endif // NPROOMCODESTATUS_H