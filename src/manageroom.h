#ifndef MANAGEROOM_H
#define MANAGEROOM_H

#include "hostmodel.h"
#include "playermodel.h"
#include "gamedialog.h"
#include "hostnetworkhandler.h"

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QStringListModel>

namespace Ui {
class ManageRoom;
}

/**
 * Used to have the host see who has joined the game, and allows the host to
 * start the game.
 */
class ManageRoom : public QDialog {
  Q_OBJECT

 public:
  /**
  Constructor
  */
  explicit ManageRoom(QWidget* parent = nullptr);

  /**
  Destructor
  */
  ~ManageRoom();

  /**
   * Used to pass a Host from the previous dialog.
   * @param hostPlayer The address of the Host's  HostModel.
   */
  void passHost(HostModel* hostPlayer);

  /**
   * Used to pass a HostNetworkHandler from the previous dialog.
   * @param handlerIn The address of the HostNetworkHandler
   */
  void passHandler(HostNetworkHandler* handlerIn);

  /**
   * Used to pass the roomCode entered in the previous dialog to this class.
   * @param roomCode the Room code entered by the user.
   */
  void passRoomCode(QString roomCode);

 private:
  /// ui pointer
  Ui::ManageRoom* ui;

  /// Gameplay Window
  GameDialog* gameWindow;

  /// Holds the list of playernames to be displayed
  QStringList list;

  /// Model for list
  QStringListModel model;

  /// Map to hold user ids of players and their names in the table
  std::list<PlayerModel*> playerList;

  /// Holds the address of the host network handler
  HostNetworkHandler* handler;

  /// Holds the roomCode set by the Host
  QString hostRoomCode;

 private
slots:
  /**
  Slot to send user to game play
  */
  void startGame();

  /**
  @todo will forcibly close the lobby, disconnecting all players
  */
  void closeLobby();

 public
slots:

  /**
  addPlayer should be called when a player has successfully connected
  @param player Pass the player class
  */
  void addPlayer(PlayerModel* player);

  /**
  removePlayer should be called when a player disconnects either via connection
  drop or self disconnect.
  @param player Pass the player class of the player to remove
  */
  void removePlayer(PlayerModel* player);

  /**
   * Handles the receipt of a RoomCode packet
   * @param provideRoomCodePacket
   * @param socket The socket that communicates with that specific player.
   */
  void handleProvideRoomCode(NPProvideRoomCode provideRoomCodePacket,
                             QTcpSocket* socket);

signals:

  /**
   * Used to send out the room code status in reply to the client
   * @param roomCodeStatus
   * @param socket The socket of the client to communicate with
   */
  void sendRoomCodeStatusToClient(NPRoomCodeStatus roomCodeStatus,
                                  QTcpSocket* socket);

  /**
   * Used to send out the start game signal to the client
   * @param welcomeToRoom
   * @param socket The socket of the client to communicate with
   */
  void sendWelcomeToRoomToClient(NPWelcomeToRoom welcomeToRoom,
                                 QTcpSocket* socket);
};

#endif  // MANAGEROOM_H
