#include "HostTCPHandler.h"

HostTCPHandler::HostTCPHandler(QTcpServer* tcpServer, QtcpSocket* tcpSocket)
{
    server = tcpServer;
    socket = tcpSocket;
    connect(
        socket,
        &QTcpSocket::readyRead,
        this,
        &HostTCPHandler::handleIncomingPacket
    );
}

HostTCPHandler::~HostTCPHandler()
{
}

void HostTCPHandler::handleIncomingPacket() {
    QByteArray data = tcpSocket->readAll();
    
    NPGeneric genericPacket = dynamic_cast<NPGeneric>(data);
    PacketType type = genericPacket->getPacketType();
    
    // Handle incoming packets on the Host
    switch (type)
    {
    case PROVIDEROOMCODE:
        NPProvideRoomCode roomCode = dynamic_cast<NPProvideRoomCode>(data);
        emit provideRoomCode()
        break;
    case TERMINATEME:
        NPTerminateMe termMe = dynamic_cast<NPTerminateMe>(data);
        emit terminateMe(termMe,termMe.getUID());
        break;
    case SPACEPRESSED:
        NPSpacePressed spcPrsd = dynamic_cast<NPSpacePressed>(data);
        emit spacePressed(spcPrsd, spcPrsd.getUID());
        break;
    case NULLPACKETTYPE:
    default:
        /// @todo Throw an error if the incoming packet is of unknown type
        break;
    }
}

/// @todo Setup the TCP Server to send these packets back to the guest
void HostTCPHandler::sendRoomCodeStatus(NPRoomCodeStatus roomCodeStatus, QTcpSocket* socket) {
    
}

/// @todo setup the TCP Server to send these packets back to the guest
void HostTCPHandler::sendWelcomeToRoom(NPWelcomeToRoom welcomeToRoom, QTcpSocket* socket) {

}