#ifndef NPGUESTTOHOST_H
#define NPGUESTTOHOST_H

#include "npgeneric.h"

/**
 * Used for network traffic passed from a Guest to the Host
 */
class NPGuestToHost : public NPGeneric
{
private:
    /**
     * @copydoc NPGeneric::packetType
     */
    PacketType packetType = PacketType::NULLPACKETTYPE;

    /// User Id of Sender
    int uid = -1;

public:
    NPGuestToHost();
    ~NPGuestToHost();

    /**
     * Used to set the user id of the player sending this message
     */
    void setUID(int uid);

    /**
     * Used to get the user id of the player sending this message
     */
    int getUID();
    
    /**
     * Reimplements the `<<` operator for QDataStream.
     * This is used to send the data in a specific order
     */
    friend QDataStream& operator<<(QDataStream& ds, NPGuestToHost& packet);

    /**
     * Reimplements the `>>` operator for QDataStream.
     * This is used to receive the data in a specific order.
     * @warning Do not attempt to read in the Packet type as that will be done externally to determine what type of packet to read in for the remaining data.
     */
    friend QDataStream& operator>>(QDataStream& ds, NPGuestToHost& packet);
};

#endif // NPGUESTTOHOST_H