#ifndef NPWELCOMETOROOM_H
#define NPWELCOMETOROOM_H

#include "nphosttoguest.h"

/**
 * Used to signal the start of the game.
 */
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