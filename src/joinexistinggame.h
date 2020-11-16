#ifndef JOINEXISTINGGAME_H
#define JOINEXISTINGGAME_H

#include <QHostAddress>
#include <QDialog>
#include <QString>
#include <QIntValidator>
#include <QRegularExpressionValidator>

namespace Ui {
class JoinExistingGame;
}

/**
 * Used to have the guest enter the details of the game he wishes to join
 */
class JoinExistingGame : public QDialog {
  Q_OBJECT

 public:
  /**
   * Constructor used to dynamically allocate memory
   * @param parent
   */
  explicit JoinExistingGame(QWidget* parent = nullptr);

  /**
   * Destructor used to deallocate memory
   */
  ~JoinExistingGame();

  /**
   * Used to Pass the name from the previous window.
   * @param name The user's name
   */
  void passName(QString name);

 private:
  Ui::JoinExistingGame* ui;

 private
slots:
  /**
   * slot that attempts to join game if IP and port are valid
   */
  void attemptToJoin();

  /**
   * Exits back to a higher dialog
   */
  void cancel();

signals:
  /**
   * Informs FlowChamp that the user wants to join a specific game
   * @param addressIn The QHostAddress that the user wants to connect to
   * @param portIn The port that the user wants to connect to
   * @param roomCodeIn The room code that will be validated with the Host
   */
  void JGGoToWaitingToStart(QHostAddress addressIn, QString portIn,
                            QString roomCodeIn);

  /**
   * Informs FlowChamp that the user wishes to quit back to the
   * DetermineRoleDialog
   */
  void JGQuitGame();
};

#endif  // JOINEXISTINGGAME_H
