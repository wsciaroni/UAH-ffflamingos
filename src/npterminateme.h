#ifndef NPTERMINATEME_H
#define NPTERMINATEME_H

#include "npguesttohost.h"

class NPTerminateMe : public NPGuestToHost
{
private:
    /**
     * @copydoc NPGuestToHost::packetType
     */
    PacketType packetType = PacketType::TERMINATEME;

public:
    NPTerminateMe(/* args */);
    ~NPTerminateMe();

    /**
     * Reimplements the `<<` operator for QDataStream.
     * This is used to send the data in a specific order
     */
    friend QDataStream& operator<<(QDataStream& ds, NPTerminateMe& packet);

    /**
     * Reimplements the `>>` operator for QDataStream.
     * This is used to receive the data in a specific order.
     * @warning Do not attempt to read in the Packet type as that will be done externally to determine what type of packet to read in for the remaining data.
     */
    friend QDataStream& operator>>(QDataStream& ds, NPTerminateMe& packet);
};

#endif // NPTERMINATEME_H