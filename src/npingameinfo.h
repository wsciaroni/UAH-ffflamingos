#ifndef NPINGAMEINFO_H
#define NPINGAMEINFO_H

#include "nphosttoguest.h"

class NPInGameInfo : public NPHostToGuest
{
private:
    /**
     * @copydoc NPHostToGuest::packetType
     */
    PacketType packetType = PacketType::INGAMEINFO;

public:
    NPInGameInfo(/* args */);
    ~NPInGameInfo();

    /**
     * Reimplements the `<<` operator for QDataStream.
     * This is used to send the data in a specific order
     */
    friend QDataStream& operator<<(QDataStream& ds, NPInGameInfo& packet);

    /**
     * Reimplements the `>>` operator for QDataStream.
     * This is used to receive the data in a specific order.
     * @warning Do not attempt to read in the Packet type as that will be done externally to determine what type of packet to read in for the remaining data.
     */
    friend QDataStream& operator>>(QDataStream& ds, NPInGameInfo& packet);
};

#endif // NPINGAMEINFO_H