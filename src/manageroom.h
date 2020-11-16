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

 private:
  /// ui pointer
  Ui::ManageRoom* ui;

  /// Model for list
  QStringListModel model;

 private
slots:
  /**
   * Slot to send user to game play
   */
  void startGame();

  /**
   * Closes the lobby for all
   */
  void closeLobby();

 public
slots:

  /**
   * Used to let the ManageRoom know that there was a change in PlayerList from
   * the FlowChamp
   */
  void MRUpdatePlayerList(QStringList usernameListIn);

  /**
   * Used to pass the roomCode entered in the previous dialog to this class.
   * @param ip The IP that the user entered
   * @param port The Port that the user entered
   * @param roomCode The RoomCode that the user entered
   */
  void MRPassHostInfo(QString ip, QString port, QString roomCode);

signals:

  /**
   * Informs FlowChamp that the user is ready to start the game for all players
   */
  void MRStartGameForAll();

  /**
   * Informs FlowChamp that the user wishes to end the game for all players
   */
  void MRQuitGame();
};

#endif  // MANAGEROOM_H
