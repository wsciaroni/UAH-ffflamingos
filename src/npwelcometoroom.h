#ifndef NPWELCOMETOROOM_H
#define NPWELCOMETOROOM_H

#include "nphosttoguest.h"

class NPWelcomeToRoom : public NPHostToGuest
{
private:
    /**
     * @copydoc NPHostToGuest::packetType
     */
    PacketType packetType = PacketType::WELCOMETOROOM;

public:
    NPWelcomeToRoom(/* args */);
    ~NPWelcomeToRoom();

    /**
     * Reimplements the `<<` operator for QDataStream.
     * This is used to send the data in a specific order
     */
    friend QDataStream& operator<<(QDataStream& ds, NPWelcomeToRoom& packet);

    /**
     * Reimplements the `>>` operator for QDataStream.
     * This is used to receive the data in a specific order.
     * @warning Do not attempt to read in the Packet type as that will be done externally to determine what type of packet to read in for the remaining data.
     */
    friend QDataStream& operator>>(QDataStream& ds, NPWelcomeToRoom& packet);
};

#endif // NPWELCOMETOROOM_H