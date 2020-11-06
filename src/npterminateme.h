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
};

#endif // NPTERMINATEME_H