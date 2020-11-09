#ifndef NPHOSTTOGUEST_H
#define NPHOSTTOGUEST_H

#include "npgeneric.h"

class NPHostToGuest : public NPGeneric
{
private:
    /**
     * @copydoc NPGeneric::packetType
     */
    PacketType packetType = PacketType::NULLPACKETTYPE;

public:
    NPHostToGuest(/* args */);
    ~NPHostToGuest();

    /**
     * Reimplements the `<<` operator for QDataStream.
     * This is used to send the data in a specific order
     */
    friend QDataStream& operator<<(QDataStream& ds, NPHostToGuest& packet);
    
    /**
     * Reimplements the `>>` operator for QDataStream.
     * This is used to receive the data in a specific order.
     * @warning Do not attempt to read in the Packet type as that will be done externally to determine what type of packet to read in for the remaining data.
     */
    friend QDataStream& operator>>(QDataStream& ds, NPHostToGuest& packet);
};

#endif // NPHOSTTOGUEST_H