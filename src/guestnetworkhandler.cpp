#include "guestnetworkhandler.h"

GuestNetworkHandler::GuestNetworkHandler(QObject* parent) : QObject(parent)
{
}

GuestNetworkHandler::~GuestNetworkHandler()
{
}

bool GuestNetworkHandler::connectToHost(QHostAddress hostAddress, QString portIn) {
    if (!tcpSocket.isOpen())
    {
        port = portIn.toInt();
        tcpSocket.connectToHost(hostAddress, port);
        tcpSocket.waitForConnected();
        return true;
    }
    return false;
}

void GuestNetworkHandler::disconnectFromHost() {
    if (tcpSocket.isOpen())
    {
        tcpSocket.close();
    }
}

bool GuestNetworkHandler::listenOnUDP() {
    if (udpSocket.isOpen())
    {
        udpSocket.close();
    }
    
    return udpSocket.bind(QHostAddress::AnyIPv4, port);
}

void GuestNetworkHandler::stopListeningOnUDP() {
    if (udpSocket.isOpen())
    {
        udpSocket.close();
    }
}

void GuestNetworkHandler::onTCPConnected() {

}

void GuestNetworkHandler::onTCPDisconnected() {

}

void GuestNetworkHandler::onTCPDataReady() {
    qDebug() << "In onTCPDataReady()\n";
    QTcpSocket* tcpSocket = dynamic_cast<QTcpSocket*>(sender());

    // Read from socket here
    PacketType pType;
    BlockReader(tcpSocket).stream() >> pType;
    if (pType == PacketType::ROOMCODESTATUS)
    {
        qDebug() << "pType == PROVIDEROOMCODE\n";
        NPProvideRoomCode provideRoomCodePacket;
        BlockReader(tcpSocket).stream() >> provideRoomCodePacket;
        emit this->provideRoomCode(provideRoomCodePacket);
    } else if (pType == PacketType::ENDGAMEINFO)
    {
        qDebug() << "pType == SPACEPRESSED\n";
        NPSpacePressed spacePressedPacket;
        BlockReader(tcpSocket).stream() >> spacePressedPacket;
        emit this->spacePressed(spacePressedPacket);
    } else if (pType == PacketType::NULLPACKETTYPE)
    {
        qDebug() << "pType == NULLPACKETTYPE\n";
        // Throw an error
    } else 
    {
        qDebug() << "Unknown packet type\n";
    }
}

void GuestNetworkHandler::onTCPBytesWritten() {

}

void GuestNetworkHandler::onUDPReadPendingDatagrams() {
    QByteArray datagram;

    while (udpSocket.hasPendingDatagrams())
    {
        datagram.resize(int(udpSocket.pendingDatagramSize()));
        udpSocket.readDatagram(datagram.data(), datagram.size());
        
        // Process the incoming datagram
    }
}

void GuestNetworkHandler::recvRoomCodeStatus(NPRoomCodeStatus roomCodeStatus) {

}

void GuestNetworkHandler::recvWelcomeToRoom(NPWelcomeToRoom welcomeToRoom) {

}

void GuestNetworkHandler::recvInGameInfo(NPInGameInfo inGameInfo) {

}

void GuestNetworkHandler::recvEndGameInfo(NPEndGameInfo endGameInfo) {

}

void GuestNetworkHandler::provideRoomCode(NPProvideRoomCode provideRoomCodePacket) {
   BlockWriter(&tcpSocket).stream() << provideRoomCodePacket;
}

void GuestNetworkHandler::terminateMe(NPTerminateMe terminateMePacket) {
    BlockWriter(&tcpSocket).stream() << terminateMePacket;
}

void GuestNetworkHandler::spacePressed(NPSpacePressed spacePressedPacket) {
    BlockWriter(&tcpSocket).stream() << spacePressedPacket;
}