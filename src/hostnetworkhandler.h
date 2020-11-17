#ifndef HOSTNETWORKHANDLER_H
#define HOSTNETWORKHANDLER_H

// Guest -> Host
#include "npprovideroomcode.h"
#include "npterminateme.h"
#include "npspacepressed.h"

// Host -> Guest
#include "nproomcodestatus.h"
#include "npwelcometoroom.h"
#include "npingameinfo.h"
#include "npendgameinfo.h"

#include "playerlist.h"

#include "blockreader.h"
#include "blockwriter.h"
#include "datastreamenum.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QDataStream>
#include <QNetworkDatagram>
#include <QHostAddress>

/**
 * @brief Handles incoming TCP connections on the Host
 * @details Throws signals for specific types of message handling when certain
 * messages are received
 */
class HostNetworkHandler : public QObject {

  Q_OBJECT

 private:
  /**
   * Holds the TCP server to use to communicate
   */
  QTcpServer tcpServer;

  /**
   * Holds the QUDPSocket to connect to each of the hosts
   */
  QUdpSocket udpServer;

  /**
   * Holds the port that the TCP server is listening on
   */
  int port;

  /**
   * Multicast address to send from host and recieve on guests for UDP
   */
  QHostAddress multicastAddress = QHostAddress("239.255.43.21");

 public:
  /**
   * Constructor used to dynamically allocate memory
   * @param parent
   */
  HostNetworkHandler(QObject* parent = nullptr);

  /**
   * Destructor used to deallocate memory
   */
  ~HostNetworkHandler();

  /**
   * @brief Used to get the port that Host is listening on.
   * @return Returns the port that the TCP server is listening on.
   */
  int getPort();

  /**
   * Starts the TCP Server
   * @param hostAddress the address to listen for incomming connections on
   * @param portIn the port to listen on
   * @return 1 if the TCPServer is actively listening on the port
   */
  bool startTCPServer(QHostAddress hostAddress, int portIn);

  /**
   * Stops the TCP Server
   */
  void stopTCPServer();

  /**
   * Used to work with the QTcpServer of the host
   * @return Returns the address of the TCPServer
   */
  QTcpServer* getTCPServer();

 protected
slots:
  /**
   * @brief Handles new TCP Connections to the Host
   */
  void onNewTCPConnection();

  /**
   * @brief Handles what to do when a connection is made
   */
  void onTCPConnected();

  /**
   * @brief handles what to do when a connection is disconnected
   * This should set the player in question to innactive
   */
  void onTCPDisconnected();

  /**
   * Handles all incoming network connections on the QTcpServer.
   */
  void onTCPDataReady();

  /**
   * Handles incoming bytes when data is written to the TCPSocket.
   */
  void onTCPBytesWritten(qint64 bytes);

signals:
  /**
   * @brief emitted when a room code is provided
   * @param provideRoomCodePacket A Network Packet of type NPProvideRoomCode
   * @param socket The QTcpSocket to communicate with that specific client on
   */
  void provideRoomCode(NPProvideRoomCode provideRoomCodePacket,
                       QTcpSocket* socket);

  /**
   * @brief emitted when a request to leave is received
   * @param terminateMePacket A Network Packet of type NPTerminateMe
   * @param socket The QTcpSocket to communicate with that specific client on
   */
  void terminateMe(NPTerminateMe terminateMePacket, QTcpSocket* socket);

  /**
   * @brief emitted when a space bar is pressed
   * @param spacePressedPacket A Network Packet of type NPSpacePressed
   * @param socket The QTcpSocket to communicate with that specific client on
   */
  void spacePressed(NPSpacePressed spacePressedPacket, QTcpSocket* socket);

  /**
   *
   */
  void hostHandleGuestTerminated(QTcpSocket* socket);

 public
slots:
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

  /**
   * @brief Used to send the in game information to a client
   * @details Sends the positions of the balls and players, high score, and
   * current scores
   * @param inGameInfo A Network Packet of type NPInGameInfo
   * @param destinationAddress The address to send the in game info to
   */
  void sendInGameInfo(NPInGameInfo inGameInfo, QHostAddress destinationAddress);

  /**
   * @brief Used to send the end of game statistics
   * @details Sends the value of the final scores, the winner, and the overall
   * high score
   * @param endGameInfo A Network Packet of type NPInGameInfo
   * @param socket The socket to send the end of game info
   */
  void sendEndGameInfo(NPEndGameInfo endGameInfo, QTcpSocket* socket);
};

#endif  // HOSTNETWORKHANDLER_H