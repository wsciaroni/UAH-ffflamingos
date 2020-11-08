#ifndef GUESTTCPSERVER_H
#define GUESTTCPSERVER_H

#include "npgeneric.h"

class GuestTCPHandler
{
private:
    /* data */
public:
    GuestTCPHandler(/* args */);
    ~GuestTCPHandler();

private slots:
    void handleIncomingPacket();
};

GuestTCPHandler::GuestTCPHandler(/* args */)
{
}

GuestTCPHandler::~GuestTCPHandler()
{
}

void GuestTCPHandler::handleIncomingPacket() {
    PacketType type;
    // Handle incoming packets on a Guest
    switch (type)
    {
    case ROOMCODESTATUS:
        /// @todo Handle incoming room code status
        break;
    case WELCOMETOROOM:
        /// @todo Handle incoming welcome to room packet
        break;
    case INGAMEINFO:
        /// @todo Handle incoming in game info
        break;
    case ENDGAMEINFO:
        /// @todo handle incoming end of game info
        break;
    case NULLPACKETTYPE:
    default:
        /// @todo Throw an error if the incoming packet is of unknown type
        break;
    }

}
#endif // GUESTTCPSERVER_H