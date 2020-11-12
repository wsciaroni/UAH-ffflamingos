#ifndef DETERMINEROLEDIALOG_H
#define DETERMINEROLEDIALOG_H

#include "creategame.h"
#include "joinexistinggame.h"

#include <QDialog>

namespace Ui {
class DetermineRoleDialog;
}

/**
 * Dialog to determine the user's Name and the user's Role
 */
class DetermineRoleDialog : public QDialog {
  Q_OBJECT

 public:
  /**
   * Constructor used to dynamically allocate memory
   * @param parent
   */
  explicit DetermineRoleDialog(QWidget* parent = nullptr);

  /**
   * Destructor used to deallocate memory
   */
  ~DetermineRoleDialog();

 private:
  Ui::DetermineRoleDialog* ui;

  /**
   * Holds the address of the next dialog
   */
  CreateGame* createGameDialog;

  /**
   * Holds the address of the next dialog
   */
  JoinExistingGame* joinGameDialog;

  /**
   * Navigates the user to the CreateGame dialog.
   * This causes this dialog to be hidden until the new dialog returns.
   */
  void createGame();

  /**
   * Navigates the user to the JoinGame dialog.
   * This causes this dialog to be hidden until the new dialog returns.
   */
  void joinGame();

 public
slots:
  /**
   * Slot that calls out to the next dialog and accepts this QDialog
   */
  void moveForward();
};

#endif  // DETERMINEROLEDIALOG_H
