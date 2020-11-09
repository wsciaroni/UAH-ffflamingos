#include "hostnetworkhandler.h"

HostNetworkHandler::HostNetworkHandler(QObject* parent) : QObject(parent)
{
    connect(
        &tcpServer,
        &QTcpServer::newConnection,
        this,
        &HostNetworkHandler::onNewTCPConnection
        );
}

HostNetworkHandler::~HostNetworkHandler()
{
    stopTCPServer();
    
    const QObjectList& list = tcpServer.children();
    for (int i = 0; i < list.length(); i++)
    {
        QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(list[i]);

        if (tcp != nullptr)
        {
            tcp->close();
        }
    }
}

bool HostNetworkHandler::startTCPServer(QHostAddress hostAddress, int portIn) {
    if (tcpServer.isListening())
    {
        stopTCPServer();
    }
    port = portIn;
    return tcpServer.listen(hostAddress, port);
}

void HostNetworkHandler::stopTCPServer() {
    if (tcpServer.isListening())
    {
        tcpServer.close();
    }
}

QTcpServer* HostNetworkHandler::getTCPServer() {
    return &tcpServer;
}

void HostNetworkHandler::onNewTCPConnection() {
    QTcpSocket* tcpSocket = tcpServer.nextPendingConnection();  // Pass this tcp socket to the 

    connect(
        tcpSocket,
        &QTcpSocket::connected,
        this,
        &HostNetworkHandler::onTCPConnected
        );
    connect(
        tcpSocket,
        &QTcpSocket::disconnected,
        this,
        &HostNetworkHandler::onTCPDisconnected
        );
    connect(
        tcpSocket,
        &QTcpSocket::readyRead,
        this,
        &HostNetworkHandler::onTCPDataReady
        );
    connect(
        tcpSocket,
        SIGNAL(bytesWritten(qint64)),
        this,
        SLOT(onTCPDataReady(qint64))
        );
}

void HostNetworkHandler::onTCPConnected() {
    QTcpSocket* tcpSocket = dynamic_cast<QTcpSocket*>(sender());
    if (tcpSocket != nullptr)
    {
        // on connection
        // Add Player to PlayerList
        // Add player to multicast group
        // Handle the incoming ProvideRoomCode Packet
            //  If RoomCode Packet UID != -1, try to readd that player to the game
            // If the RoomCode Packet UID == -1, then create a new player
    }
}

void HostNetworkHandler::onTCPDisconnected() {
    // Disconnected
    // Remove player from player list?
    // Remove player from multicast group
}

void HostNetworkHandler::onTCPDataReady() {
    QTcpSocket* tcpSocket = dynamic_cast<QTcpSocket*>(sender());
    // Read from socket here
}

void HostNetworkHandler::onTCPBytesWritten(qint64 bytes) {
    /// @todo Implement the area that reads in data from the TCPSocket
    // Process the bytes that were written to the 
    // Create a Datastream, then:
    // First read in the Packet type,
    // Read the rest of the data into the specific class that it's supposed to be handled by
    // Then emit a signal for each specific class so someone knows what kind of data needs to be processed

}
int HostNetworkHandler::getPort() {
    return port;
}

/// @todo Setup the TCP Server to send these packets back to the guest
void HostNetworkHandler::sendRoomCodeStatus(NPRoomCodeStatus roomCodeStatus, QTcpSocket* socket) {
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << roomCodeStatus;
    socket->write(datagram);
}

/// @todo setup the TCP Server to send these packets back to the guest
void HostNetworkHandler::sendWelcomeToRoom(NPWelcomeToRoom welcomeToRoom, QTcpSocket* socket) {
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << welcomeToRoom;
    socket->write(datagram);
}

void HostNetworkHandler::sendInGameInfo(NPInGameInfo inGameInfo, QHostAddress destinationAddress) {
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << inGameInfo;
    udpServer.writeDatagram(datagram, destinationAddress, port);
}

void HostNetworkHandler::sendEndGameInfo(NPEndGameInfo endGameInfo, QTcpSocket* socket) {
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << endGameInfo;
    socket->write(datagram);
}