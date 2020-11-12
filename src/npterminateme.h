#ifndef NPTERMINATEME_H
#define NPTERMINATEME_H

#include "npguesttohost.h"

/**
 * Used to request a graceful exit from the game
 */
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
};

#endif // NPTERMINATEME_H