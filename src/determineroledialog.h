#ifndef DETERMINEROLEDIALOG_H
#define DETERMINEROLEDIALOG_H

#include <QDialog>
#include <QRegularExpressionValidator>

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
 private
slots:
  /**
   * Used to handle the input on this form and emit the appropriate signals
   */
  void moveForward();

  /**
   * Triggered by the Cancel button and emits the DRQuitGame signal
   */
  void cancel();

signals:
  /**
   * Used to let the FlowChamp know that the user is requesting to be the Host
   * Ties to FlowChamp::DRPlayAsHost()
   */
  void DRPlayAsHost(QString playerNameIn);

  /**
   * Used to let the FlowChamp know that the user is requesting to be a Guests
   */
  void DRPlayAsGuest(QString playerNameIn);

  /**
   * Used to let the FlowChamp know that the user is attempting to quit
   */
  void DRQuitGame();
};

#endif  // DETERMINEROLEDIALOG_H
