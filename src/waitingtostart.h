#ifndef WAITINGTOSTART_H
#define WAITINGTOSTART_H

#include "gamedialog.h"
#include "playermodel.h"

#include <QDialog>

namespace Ui {
class WaitingToStart;
}

/**
 * Dialog that appears once a user is connected and in the waiting room
 */
class WaitingToStart : public QDialog {
  Q_OBJECT

 public:
  /**
   * @brief WaitingToStart
   * @param parent
   */
  explicit WaitingToStart(QWidget* parent = nullptr);
  /**
   *Destructor
   */
  ~WaitingToStart();

  /**
   * Used to pass a GuestNetworkHandler from the previous dialog.
   * @param handlerIn The address of the GuestNetworkHandler
   */
  void passHandler(GuestNetworkHandler* handlerIn);

  /**
  Used to pass the Client's individual player model onward
  @param playerIn The pointer to the player's individual model
  */
  void passPlayerModel(PlayerModel* playerIn);

 private:
  Ui::WaitingToStart* ui;

  /**
   * Holds the address of the game window
   */
  GameDialog* gameWindow;

  /// Holds the address of the guest network handler
  GuestNetworkHandler* handler;

  /// Holds the player model of this client
  PlayerModel* player;

 private
slots:

  /**
  @todo Needs to run the MannageRoom::removePlayer(username) function for host's
  instance of the window
  as well as disconnect the player.
  */
  void disconnect();

  /**
   * @todo Needs to launch gameplay window and handle other things appropriately
   */
  void playGame();
};

#endif  // WAITINGTOSTART_H
