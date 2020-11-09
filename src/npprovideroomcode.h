#ifndef NPPROVIDEROOMCODE_H
#define NPPROVIDEROOMCODE_H

#include "npguesttohost.h"

#include <QString>

class NPProvideRoomCode : public NPGuestToHost
{
private:
    /**
     * @copydoc NPGuestToHost::packetType
     */
    PacketType packetType = PacketType::PROVIDEROOMCODE;

    QString roomCode;

public:
    NPProvideRoomCode(/* args */);
    ~NPProvideRoomCode();

    /**
     * Used to put the room code into the packet
     * @param roomcode Holds the new value of the room code to be checked with the host
     */
    void setRoomCode(QString roomcode);

    /**
     * Used to get the room code from the packet
     * @return RoomCode from the packet
     */
    QString getRoomCode();

    /**
     * Reimplements the `<<` operator for QDataStream.
     * This is used to send the data in a specific order
     */
    friend QDataStream& operator<<(QDataStream& ds, NPProvideRoomCode& packet);

    /**
     * Reimplements the `>>` operator for QDataStream.
     * This is used to receive the data in a specific order.
     * @warning Do not attempt to read in the Packet type as that will be done externally to determine what type of packet to read in for the remaining data.
     */
    friend QDataStream& operator>>(QDataStream& ds, NPProvideRoomCode& packet);
};

#endif