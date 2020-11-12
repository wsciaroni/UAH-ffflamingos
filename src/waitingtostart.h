#ifndef WAITINGTOSTART_H
#define WAITINGTOSTART_H

#include "gamedialog.h"

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
  explicit WaitingToStart(QWidget *parent = nullptr);
  /**
   *Destructor
   */
  ~WaitingToStart();

 private:
  Ui::WaitingToStart *ui;

  /**
   * Holds the address of the game window
   */
  GameDialog *gameWindow;

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
