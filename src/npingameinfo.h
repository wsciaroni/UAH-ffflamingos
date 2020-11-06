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
};

#endif // NPINGAMEINFO_H