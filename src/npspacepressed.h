#ifndef NPSPACEPRESSED_H
#define NPSPACEPRESSED_H

#include "npguesttohost.h"

class NPSpacePressed : public NPGuestToHost
{
private:
    /**
     * @copydoc NPGuestToHost::packetType
     */
    PacketType packetType = PacketType::SPACEPRESSED;

public:
    NPSpacePressed(/* args */);
    ~NPSpacePressed();

    /**
     * Reimplements the `<<` operator for QDataStream.
     * This is used to send the data in a specific order
     */
    friend QDataStream& operator<<(QDataStream& ds, NPSpacePressed& packet);

    /**
     * Reimplements the `>>` operator for QDataStream.
     * This is used to receive the data in a specific order.
     * @warning Do not attempt to read in the Packet type as that will be done externally to determine what type of packet to read in for the remaining data.
     */
    friend QDataStream& operator>>(QDataStream& ds, NPSpacePressed& packet);
};

#endif // NPSPACEPRESSED_H