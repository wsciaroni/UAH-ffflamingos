#ifndef HostTCPHandler_H
#define HostTCPHandler_H

#include "npgeneric.h"

// Guest -> Host
#include "npprovideroomcode.h"
#include "npterminateme.h"
#include "npspacepressed.h"

// Host -> Guest
#include "nproomcodestatus.h"
#include "npwelcometoroom.h"

#include <QTcpServer>
#include <QTcpSocket>

/**
 * @brief Handles incoming TCP connections on the Host
 * @details Throws signals for specific types of message handling when certain messages are received
 */
class HostTCPHandler
{
private:
    /**
     * Holds the TCP server to use to communicate
     */
    QTcpServer* server;

    /**
     * Holds the TCP Socket to use to communicate
     */
    QTcpSocket* socket;

public:
    HostTCPHandler(QTcpServer* tcpServer);
    ~HostTCPHandler();

private slots:
    /**
     * Handles all incoming network connections on the QTcpServer
     */
    void handleIncomingPacket();

signals:
    /**
     * @brief emitted when a room code is provided
     * @param provideRoomCodePacket A Network Packet of type NPProvideRoomCode
     */
    void provideRoomCode(NPProvideRoomCode provideRoomCodePacket);

    /**
     * @brief emitted when a request to leave is received
     * @param terminateMePacket A Network Packet of type NPTerminateMe
     * @param uid The uid of the player who sent the packet
     */
    void terminateMe(NPTerminateMe terminateMePacket, int uid);

    /**
     * @brief emitted when a space bar is pressed
     * @param spacePressedPacket A Network Packet of type NPSpacePressed
     * @param uid The uid of the player who sent the packet
     */
    void spacePressed(NPSpacePressed spacePressedPacket, int uid);

public slots:
    /**
     * @brief Used to send the room code status to a specific client
     * @param roomCodeStatus A Network Pacet of type NPRoomCodeStatus
     * @param socket The socket to send the roomCodeStatus
     */
    void sendRoomCodeStatus(NPRoomCodeStatus roomCodeStatus, QTcpSocket* socket);

    /**
     * @brief Used to send the beginning of game information to a client
     * @param welcomeToRoom A Network Packet of type NPWeclomeToRoom
     * @param socket The socket to send the begin game packet on
     */
    void sendWelcomeToRoom(NPWelcomeToRoom welcomeToRoom, QTcpSocket* socket);
};



#endif // HostTCPHandler_H