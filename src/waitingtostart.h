#ifndef WAITINGTOSTART_H
#define WAITINGTOSTART_H

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

 private:
  Ui::WaitingToStart* ui;

 private
slots:

  /**
   * Handles what to do when the disconnect button is pressed
  */
  void disconnect();

signals:
  /**
   * Informs FlowChamp that the user no longer wishes to be connected.
   */
  void WSQuitGame();
};

#endif  // WAITINGTOSTART_H
