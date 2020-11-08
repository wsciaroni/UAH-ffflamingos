#include "networkconfigurator.h"

NetworkConfigurator::NetworkConfigurator()
{

}

NetworkConfigurator::~NetworkConfigurator() {

}

void NetworkConfigurator::processNetworkPackets() {
    /* HostModel* host = 
    QByteArray data = host->getTcpServer()->readAll();
    
    NPGeneric genericPacket(data);
    PacketType type = genericPacket->getPacketType();
    
    // Handle incoming packets on the Host
    switch (type)
    {
    case PROVIDEROOMCODE:
        /// @todo Handle incoming room code
        break;
    case TERMINATEME:
        /// @todo Handle incoming request to leave
        break;
    case SPACEPRESSED:
        /// @todo Handle incoming space bar information
        break;
    case NULLPACKETTYPE:
    default:
        /// @todo Throw an error if the incoming packet is of unknown type
        break;
    }

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
    } */
}
