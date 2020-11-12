#include "guestnetworkhandler.h"
#include "error.h"

GuestNetworkHandler::GuestNetworkHandler(QObject* parent) : QObject(parent)
{
    listenOnUDP();
    connect(&udpSocket,
            SIGNAL(readyRead()),
            this,
            SLOT(onUDPReadPendingDatagrams()));

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
        qDebug() << "pType == ROOMCODESTATUS\n";
        NPRoomCodeStatus roomCodeStatus;
        bool status;
        BlockReader(tcpSocket).stream() >> status;
        roomCodeStatus.setRoomCodeStatus(status);
        emit this->recvRoomCodeStatus(roomCodeStatus);
    }
    else if (pType == PacketType::ENDGAMEINFO)
    {
        qDebug() << "pType == ENDGAMEINFO\n";
        NPEndGameInfo endGameInfo;
        //BlockReader(tcpSocket).stream() >> spacePressedPacket;
        emit this->recvEndGameInfo(endGameInfo);
    }
    else if (pType == PacketType::WELCOMETOROOM)
    {
        qDebug() << "pType == WELCOMETOROOM\n";
        NPWelcomeToRoom welcomeToRoom;
        //BlockReader(tcpSocket).stream() >> spacePressedPacket;
        emit this->recvWelcomeToRoom(welcomeToRoom);
    }
    else if (pType == PacketType::NULLPACKETTYPE)
    {
        qDebug() << "pType == NULLPACKETTYPE\n";
        // Throw an error
        error* throwError = new error;
        throwError->throwErrorMsg("ERROR: Received a NULL packet type");
        throwError->exec();
        delete throwError;
    }
    else
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

        NPInGameInfo inGameInfo;
        QDataStream in(&datagram, QIODevice::ReadOnly);

        in >> inGameInfo;
        emit this->recvInGameInfo(inGameInfo);
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

    QString roomcode = provideRoomCodePacket.getRoomCode();

    int uid = provideRoomCodePacket.getUID();
    BlockWriter(&tcpSocket).stream() << PacketType::PROVIDEROOMCODE;
    BlockWriter(&tcpSocket).stream() << uid << roomcode;

}

void GuestNetworkHandler::terminateMe(NPTerminateMe terminateMePacket) {

    int uid = terminateMePacket.getUID();
    BlockWriter(&tcpSocket).stream() << PacketType::TERMINATEME;
    BlockWriter(&tcpSocket).stream() << uid;
}

void GuestNetworkHandler::spacePressed(NPSpacePressed spacePressedPacket) {

    int uid = spacePressedPacket.getUID();
    BlockWriter(&tcpSocket).stream() << PacketType::SPACEPRESSED;
    BlockWriter(&tcpSocket).stream() << uid;
}
