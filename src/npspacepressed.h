#ifndef NPSPACEPRESSED_H
#define NPSPACEPRESSED_H

#include "npguesttohost.h"

/**
 * Used to let the host know that the space was pressed on a client
 */
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
};

#endif // NPSPACEPRESSED_H