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
#include <QDataStream>
#include <QNetworkDatagram>

/**
 * @brief Handles all the networking needs of the guest.
 * @details Throws signals for specific types of message handling when certain
 * messages are received.
 */
class GuestNetworkHandler : public QObject {

  Q_OBJECT

 private:
  /**
   * QTcpSocket to communicate with Host through
   */
  QTcpSocket tcpSocket;

  /**
   * Holds the port that the TCP server is listening on on the Host
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
  GuestNetworkHandler(QObject* parent = nullptr);

  /**
   * Destructor used to deallocate memory
   */
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
   * Used to interact directly with the QTcpSocket.
   * @return The QTcpSocket used by the guest.
   */
  QTcpSocket* getTcpSocket();

 protected
slots:

  /**
   * @brief Handles what to do when a connection is made witht the Host
   */
  void onTCPConnected();

  /**
   * @brief handles what to do when a connection is disconnected
   * This exits out of the game if the connection is terminated
   */
  void onTCPDisconnected();

  /**
   * Handles all incoming network information from the Host to this player
   */
  void onTCPDataReady();

signals:
  /**
   * This is emitted when the status of the room code is receieved
   * @param roomCodeStatus Holds the incoming packet of type NPRoomCodeStatus
   */
  void recvRoomCodeStatus(NPRoomCodeStatus roomCodeStatus);

  /**
   * This is the signal to start the game on the client machine
   * @param welcomeToRoom Holds the incoming packet of type NPWelcomeToRoom
   * @details This is used to signal that the game is beginning.
   */
  void recvWelcomeToRoom(NPWelcomeToRoom welcomeToRoom);

  /**
   * This is emitted when in game information is received
   * @param inGameInfo Holds the incoming packet of type NPInGameInfo
   * @details These are received regularly over UDP to show the location of
   * balls and the current scores.
   */
  void recvInGameInfo(NPInGameInfo inGameInfo);

  /**
   * This is emitted when the end of game information is received
   * @param endGameInfo Holds the incoming packet of type NPEndGameInfo
   * @details This signals the end of the game and includes the winner info and
   * such.
   */
  void recvEndGameInfo(NPEndGameInfo endGameInfo);

  /**
   * @brief Signal emitted when guest connection is dropped
   */
  void tcpConnectionDropped();

 public
slots:
  /**
   * Execute this to send a room code to the host
   * @param provideRoomCodePacket Holds the outgoing packet of type
   * NPProvideRoomCode
   */
  void provideRoomCode(NPProvideRoomCode provideRoomCodePacket);

  /**
   * Execute this to request to be disconnected
   * @param terminateMe Holds the outgoing packet of type NPTerminateMe
   * @details This is a request to exit the game gracefully.  If this is not
   * called, the Host should still be able to drop the player appropriately.
   */
  void terminateMe(NPTerminateMe terminateMe);

  /**
   * Execute this to send a space notification to the Host
   * @param spacePressedPacket Holds the outgoing packet of type NPSpacePressed
   */
  void spacePressed(NPSpacePressed spacePressedPacket);
};

#endif  // GUESTNETWORKHANDLER_H
