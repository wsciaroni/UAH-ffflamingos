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
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << provideRoomCodePacket;
    tcpSocket.write(datagram);
}

void GuestNetworkHandler::terminateMe(NPTerminateMe terminateMePacket) {

}

void GuestNetworkHandler::spacePressed(NPSpacePressed spacePressedPacket) {

}