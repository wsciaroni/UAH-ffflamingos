#ifndef NPWELCOMETOROOM_H
#define NPWELCOMETOROOM_H

#include "nphosttoguest.h"

class NPWelcomeToRoom : public NPHostToGuest
{
private:
    /**
     * @copydoc NPHostToGuest::packetType
     */
    PacketType packetType = PacketType::WELCOMETOROOM;

public:
    NPWelcomeToRoom(/* args */);
    ~NPWelcomeToRoom();
};

#endif // NPWELCOMETOROOM_H