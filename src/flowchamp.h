#ifndef FLOWCHAMP_H
#define FLOWCHAMP_H

// Dialogs
#include "creategame.h"           // CG - Creage Game
#include "determineroledialog.h"  // DR - Determine Role
#include "error.h"
#include "gamedialog.h"        // GD - Game Dialog
#include "joinexistinggame.h"  // JG - Join Game
#include "manageroom.h"        // MR - Manage Room
#include "waitingtostart.h"    // WS - Waiting To Start

// Networking
#include "guestnetworkhandler.h"
#include "hostnetworkhandler.h"
#include "ball.h"

// Player Abstraction
#include "playerlist.h"
#include "hostmodel.h"

#include <QApplication>
#include <QTimer>

class FlowChamp : public QApplication {
  Q_OBJECT
 private:
  /// Holds the name of the player as input in the DetermineRoleDialog
  QString playerName;

  QString hostRoomCode;

  /// True if the player is the host
  bool isHostPlayer = false;

  /// Holds the PlayerModel for each player (including the Host as uid 0)
  PlayerList* playerList = new PlayerList();

  /// Holds a list of currently attached players.
  QStringList playerNames;

  /// Holds the balls in order to calculate the positions
  ball* hostBallInfo[25];

  /// Set to true when host has started game
  bool gameStarted = false;

  // Dialogs

  /// Dialog to be displayed when need be
  CreateGame* dialogCG = new CreateGame();
  /// @copydoc FlowChamp::dialogCG
  DetermineRoleDialog* dialogDR = new DetermineRoleDialog();
  /// @copydoc FlowChamp::dialogCG
  GameDialog* dialogGD = new GameDialog();
  /// @copydoc FlowChamp::dialogCG
  JoinExistingGame* dialogJG = new JoinExistingGame();
  /// @copydoc FlowChamp::dialogCG
  ManageRoom* dialogMR = new ManageRoom();
  /// @copydoc FlowChamp::dialogCG
  WaitingToStart* dialogWS = new WaitingToStart();

  // Network Handlers
  /**
   * Instantiation of HostNetworkHandler to take care of all networking needs
   */
  HostNetworkHandler* hostHandler = new HostNetworkHandler();
  /**
   * Instantiation of GuestNetworkHandler to take care of all networking needs
   */
  GuestNetworkHandler* guestHandler = new GuestNetworkHandler();

  /**
   * Used to know if the player is the host.
   * @return True if the player is the host.
   */
  bool isHost();

  /**
   * Used to set whether the player is the host or not.
   * @param isPlayerHost True if the player is the host.
   */
  void setRole(bool isPlayerHost);

  // Player handling
  /**
   * Used by the Host to remove players while in the ManageRoom dialog.
   * @param player The PlayerModel of the player to be added
   */
  void addPlayer(PlayerModel* player);

  /**
   * Used by the Host to remove players while in the ManageRoom dialog.
   * @param player The PlayerModel of the player to be removed
   */
  void removePlayer(PlayerModel* player);

  /**
   * Used to trigger the correct actions on the Host when a player presses
   * space.
   * @param player The PlayerModel of the player to lunge
   */
  void makePlayerLunge(PlayerModel* player);

  /**
   * Used to clean up any memory leaks when the host goes to quit the game
   */
  void hostTerminateGame();

  /**
   * Used to reallocate all the memory for the necesary areas.
   */
  void reinitialize();

  /// For sending the UDP packets on interval from the Host to the Guests
  QTimer* sendInGameInfoTimer = new QTimer(this);

  /**
   * Used to start sending NPInGameInfo packets
   */
  void startSendInGameInfo();

  /**
   * Used to stop sending NPInGameInfo packets
   */
  void stopSendInGameInfo();

  /**
   * Multicast address to send from host and recieve on guests for UDP
   */
  QHostAddress multicastAddress = QHostAddress("239.255.43.21");

  /**
   * For keeping the clock remaining in the game
   */
  QTimer* gameTimer = new QTimer(this);

  /**
   * Used to start the timer which will signal the end of the game
   */
  void startGameTimer();

  /**
   * Used to stop the game timer
   */
  void stopGameTimer();

  /**
   * Function to initialize all the balls
   */
  void initializeBalls();

  /**
   * Holds the high score read from the database.
   */
  qint32 globalHighScore;

  /**
   * Holds the Name of the high score holder.
   */
  QString globalHighScoreName;

  /**
   * Used to get the high score from the database.
   * @return High Score from the database.
   */
  qint32 readHighScoreFromDatabase();

  /**
   * Used to get the name of the high score holder from the database.
   * @return Name of the high score holder.
   */
  QString readHighScoreHolderFromDatabase();

  /**
   * Used to set a new High Score in the database.
   * @param name The name of the new high score holder.
   * @param score The Score that player received.
   */
  void setNewHighScore(QString name, qint32 score);

  /**
   * Make all the QT connections necesary for the Guest Network Handler to
   * function
   */
  void connectGuestHandler();

  /**
   * Make all the Qt Connections necessary for the Host Network Handler to
   * function
   */
  void connectHostHandler();

  /**
   * Make a connect for each dialog.
   * @details Make each QT style connection necessary in the code pertaining to
   * that item
   */
  void connectDialogDR();
  /// @copydoc connectDialogDR
  void connectDialogCG();
  /// @copydoc connectDialogDR
  void connectDialogMR();
  /// @copydoc connectDialogDR
  void connectDialogJG();
  /// @copydoc connectDialogDR
  void connectDialogWS();
  /// @copydoc connectDialogDR
  void connectDialogGD();
  /// @copydoc connectDialogDR
  void connectGameInfoTimer();

 public:
  FlowChamp(int& argc, char** argv);
  ~FlowChamp();

 private
slots:
  // Move to the NetworkHandler classes
  // displayNetworkError(QAbstractSocket::SocketError socketError);

  //######################### Determine Role Dialog Slots
  /**
   * Handles moving the user to the CreateGame dialog
   * @param playerNameIn The player's name as entered on the DetermineRoleDialog
   */
  void DRPlayAsHost(QString playerNameIn);

  /**
   * Handles moving the user to the JoinGame dialg
   * @param playerNameIn The player's name as entered on the DetermineRoleDialog
   */
  void DRPlayAsGuest(QString playerNameIn);

  /**
   * Handles the user wanting to exit the application.
   */
  void DRQuitGame();
  //######################### Create Game Dialog Slots
  /**
   * Handles moving the user from the CreateGame dialog to the ManageRoom
   * dialog.
   * @param addressIn The QHostAddress as selected by the user
   * @param portIn The Port that the user wants to listen for incoming
   * connections on.
   * @param roomCodeIn The Room Code that the user expects clients to enter.
   */
  void CGGoToManageRoom(QHostAddress addressIn, QString portIn,
                        QString roomCodeIn);
  /**
   * Handles moving the user from the CreateGame dialog to the Determine Role
   * Dialog.
   */
  void CGQuitGame();

  //######################### Manage Room Dialog Slots
  /**
   * Handles moving the Host and Clients into the GameDialog Dialog
   */
  void MRStartGameForAll();

  /**
   * Handles moving the user from the ManageRoom to the DetermineRoleDialog
   */
  void MRQuitGame();

  //######################### Join Game Dialog Slots
  /**
   * Handles moving the user from the JoinGame dialog to the WaitingToStart
   * dialog
   * @param addressIn The QHostAddress that the user wants to connect to
   * @param portIn The port that the user wants to connect to
   * @param roomCodeIn The room code that will be validated with the Host
   */
  void JGGoToWaitingToStart(QHostAddress addressIn, QString portIn,
                            QString roomCodeIn);

  /**
   * Handles moving the user from the JoinGame dialog to the DetermineRoleDialog
   */
  void JGQuitGame();

  //######################### Waiting To Start Slots
  /**
   * Handles moving the user from the WaitingToStart dialog to the GameDialog
   * Dialog.
   * Should be called by an incoming Network Packet through GuestNetworkHandler
   */
  void WSStartClientGame();

  /**
   * Handles moving the user from the WaitingToStart dialog to the
   * DetermineRoleDialog
   */
  void WSQuitGame();

  //######################### GameDialog Dialog Slots
  /**
   * Handles what occurs when the user presses Space
   */
  void GDSpacePressed();

  /**
   * Handles what occurs when the user presses Escape
   */
  void GDEscPressed();

  /**
   * Handles moving the user from the GameDialog to the DetermineRoleDialog
   */
  void GDQuitGame();

  //######################### Workers
  // Guest to Host
  /**
   * Used to handle a Client's initial connection.
   * @param packet The NPPRovideRoomCode information from the connection.
   * @param socket The QTcpSocket on which is being communicated.
   */
  void hostHandleRoomCode(NPProvideRoomCode packet, QTcpSocket* socket);

  /**
   * Used to handle a Client's Request to terminate the connection.
   * @param socket The QTcpSocket on which is being communicated.
   */
  void hostHandleTerminateMe(QTcpSocket* socket);

  /**
   * Used to handle a Client's Space Bar signal.
   * @param packet The NPSpacePressed information from the connection.
   * @param socket The QTcpSocket on which is being communicated.
   */
  void hostHandleSpacePressed(NPSpacePressed packet, QTcpSocket* socket);

  /**
   * Remove any player whose Socket is disconnected
   */
  void hostHandleGuestTerminated(QTcpSocket* socket);

  // Host To Guest
  /**
   * Used to handle a Host's Response to the Room Code.
   * @param packet The NPRoomCodeStatus information from the connection.
   */
  void guestHandleRoomCodeStatus(NPRoomCodeStatus packet);

  /**
   * Used to handle a Host's Command to move the GameDialog.
   * @param packet The NPWelcomeToRoom information from the connection.
   */
  void guestHandleWelcomeToRoom(NPWelcomeToRoom packet);

  /**
   * Used to handle a Host's In Game information packet.
   * @param packet The NPInGameInfo information from the connection.
   */
  void guestHandleInGameInfo(NPInGameInfo packet);

  /**
   * Used to handle a Host's End of Game information packet.
   * @param packet The NPEndGameInfo information from the connection.
   */
  void guestHandleEndGameInfo(NPEndGameInfo packet);

  /**
   * Used to handle when the QTcpSocket is dropped
   */
  void guestHandleTCPDropOut();

  /**
   * Used to build and send the inGameInfoPackets
   */
  void prepareAndSendInGameInfo();

  /**
   * Used to build and send the endGameInfo packet
   */
  void prepareAndSendEndGameInfo();

signals:
  // Guest To Host
  /**
   * Used to signal a Guest's desire to send the room code.
   * @param packet The NPProvideRoomCode information from the connection.
   */
  void guestSendRoomCode(NPProvideRoomCode packet);
  /**
   * Used to signal a Guest's desire to be terminated.
   * @param packet The NPTerminateMe information from the connection.
   */
  void guestSendTerminateMe(NPTerminateMe packet);
  /**
   * Used to signal a Guest's Action of pressing Space.
   * @param packet The NPSpacePressed information from the connection.
   */
  void guestSendSpacePressed(NPSpacePressed packet);

  // Host To Guest
  /**
   * Used to signal a Host's response to a user's room code.
   * @param packet The NPSpacePressed information from the connection.
   * @param socket The QTcpSocket to send the information to.
   */
  void hostSendRoomCodeStatus(NPRoomCodeStatus packet, QTcpSocket* socket);

  /**
   * Used to signal a Host's Desire to start the game.
   * @param packet The NPSpacePressed information from the connection.
   * @param socket The QTcpSocket to send the information to.
   */
  void hostSendWelcomeToRoom(NPWelcomeToRoom packet, QTcpSocket* socket);

  /**
   * Used to signal a Host's desire to send out InGame information.
   * @param packet The inGameInfo information from the connection.
   * @param destinationAddress The Address(s) to send the UDP NPInGameInfo
   * packets to.
   */
  void hostSendInGameInfo(NPInGameInfo inGameInfo, QTcpSocket* socket);

  /**
   * Used to signal a Host's desire to send out End of Game Information.
   * @param packet The NPSpacePressed information from the connection.
   * @param socket The QTcpSocket to send the information to.
   */
  void hostSendEndGameInfo(NPEndGameInfo packet, QTcpSocket* socket);
  /**
  * @copydoc ManageRoom::MRUpdatePlayerList
  */
  void MRUpdatePlayerList(QStringList usernameListIn);

  /**
   * @copydoc ManageRoom::MRPassHostInfo
   */
  void MRPassHostInfo(QString ip, QString port, QString roomCode);
};

#endif
