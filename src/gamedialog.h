#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include "hostnetworkhandler.h"
#include "guestnetworkhandler.h"

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class GameDialog;
}

/**
 * Window that houses the game play.
 * Used on both the Host and the Guest to display the map, info, and such in the
 * game.
 */
class GameDialog : public QDialog {
  Q_OBJECT

 public:
  /**
   * Constructor used to dynamically allocate memory
   * @param parent
   */
  explicit GameDialog(QWidget* parent = nullptr);

  /**
   * Destructor used to deallocate memory
   */
  ~GameDialog();

  /**
   * Used to pass a HostNetworkHandler along to the gameDialog to make the
   * appropriate connection
   */
  void passHandler(HostNetworkHandler* hostHandlerIn);

  /**
   * Used to pass a HostNetworkHandler along to the gameDialog to make the
   * appropriate connection
   */
  void passHandler(GuestNetworkHandler* guestHandlerIn);

  /**
   * Used to set the role of the player in the GameDialog.
   * @param isHost True if the player is the host player
   */
  void setRole(bool isHost);

 private:
  Ui::GameDialog* ui;

  /// True if the user is the Host
  bool isHostRole = false;

  /// Holds the address of the HostNetworkHandler
  HostNetworkHandler* hostHandler;

  /// Holds the address of the GuestNetworkHandler
  GuestNetworkHandler* guestHandler;

  /**
   * Used to get the role of the player.
   * @return Returns True if the user is the Host
   */
  bool isHost();

protected:
  /**
   * @brief A Key Press Event handler (will be used for escape)
   * @param key
   */
  void keyPressEvent(QKeyEvent * key);

  /**
   * @brief Called when the escape key is pressed
   */
  void escapePress();
};

#endif  // GAMEDIALOG_H
