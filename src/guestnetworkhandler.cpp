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

}

void GuestNetworkHandler::stopListeningOnUDP() {

}

void GuestNetworkHandler::onTCPConnected() {

}

void GuestNetworkHandler::onTCPDisconnected() {

}

void GuestNetworkHandler::onTCPDataReady() {

}

void GuestNetworkHandler::onTCPBytesWritten() {

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

}

void GuestNetworkHandler::terminateMe(NPTerminateMe terminateMe) {

}

void GuestNetworkHandler::spacePressed(NPSpacePressed spacePressedPacket) {

}