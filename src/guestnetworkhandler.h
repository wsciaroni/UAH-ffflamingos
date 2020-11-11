#ifndef GUESTNETWORKHANDLER_H
#define GUESTNETWORKHANDLER_H

// Guest -> Host
#include "npprovideroomcode.h"
#include "npterminateme.h"
#include "npspacepressed.h"

// Host -> Guest
#include "nproomcodestatus.h"
#include "npwelcometoroom.h"
#include "npingameinfo.h"
#include "npendgameinfo.h"

#include "blockreader.h"
#include "blockwriter.h"
#include "datastreamenum.h"

#include <QTcpSocket>
#include <QUdpSocket>

class GuestNetworkHandler : public QObject
{
private:
    /**
     * QTcpSocket to communicate with Host through
     */
    QTcpSocket tcpSocket;
    
    /**
     * QUdpSocket to listen for incoming packets on
     */
    QUdpSocket udpSocket;

    /**
     * Holds the port that the TCP server is listening on on the Host
     */
    int port;

    int uid = -1;
    
public:
    GuestNetworkHandler(QObject* parent = nullptr);
    ~GuestNetworkHandler();

    /**
     * Connects to the provided QHostAddress and Port combination
     * @param hostAddress the QHostAddress of the host you want to connect to
     * @param portIn the port that the Host is listening on
     */
    bool connectToHost(QHostAddress hostAddress, QString portIn);

    /**
     * Close the TCP Connection with the Host
     */
    void disconnectFromHost();

    /**
     * Makes the QUdpSocket list on the GuestNetworkHandler::port and QHostAddress::anyIPv4
     */
    bool listenOnUDP();

    /**
     * Stop the QUdpSocket from listening on the port
     */
    void stopListeningOnUDP();

protected slots:

    /**
     * @brief Handles what to do when a connection is made witht the Host
     */
    void onTCPConnected();

    /**
     * @brief handles what to do when a connection is disconnected
     * @todo This exit out of the game if the connection is terminated
     */
    void onTCPDisconnected();

    /**
     * Handles all incoming network information from the Host to this player
     */
    void onTCPDataReady();

    /**
     * Handles incoming bytes when data is written to the TCPSocket
     */
    void onTCPBytesWritten();

    /**
     * Handle incoming UDP information
     */
    void onUDPReadPendingDatagrams();

signals:
    /**
     * This is emitted when the status of the room code is receieved
     */
    void recvRoomCodeStatus(NPRoomCodeStatus roomCodeStatus);

    /**
     * This is the signal to start the game on the client machine
     */
    void recvWelcomeToRoom(NPWelcomeToRoom welcomeToRoom);

    /**
     * This is emitted when in game information is received
     */
    void recvInGameInfo(NPInGameInfo inGameInfo);

    /**
     * This is emitted when the end of game information is received
     */
    void recvEndGameInfo(NPEndGameInfo endGameInfo);

public slots:
    /**
     * Execute this to send a room code to the host
     */
    void provideRoomCode(NPProvideRoomCode provideRoomCodePacket);

    /**
     * Execute this to request to be disconnected
     */
    void terminateMe(NPTerminateMe terminateMe);

    /**
     * Execute this to send a space notification to the Host
     */
    void spacePressed(NPSpacePressed spacePressedPacket);
};

#endif // GUESTNETWORKHANDLER_H