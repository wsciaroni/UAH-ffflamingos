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
};

#endif // NPGUESTTOHOST_H