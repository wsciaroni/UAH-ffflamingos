#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QDialog>
#include <QString>
#include <QTcpServer>

#include "ui_creategame.h"
#include <QIntValidator>
#include <QNetworkInterface>
#include <QAbstractSocket>

namespace Ui {
class CreateGame;
}

/**
 * Used to have the host enter the details to bind to an ip and port
 */
class CreateGame : public QDialog {
  Q_OBJECT

 public:
  /**
   * Constructor used to dynamically allocate memory
   * @param parent
   */
  explicit CreateGame(QWidget* parent = nullptr);

  /**
   * Destructor used to deallocate memory
   */
  ~CreateGame();

 private:
  Ui::CreateGame* ui;

 private
slots:
  /**
   * Used to move to the next window
   */
  void goToWaitingRoom();

  /**
   * Triggered by the Cancel button and emits the CGQuitGame signal
   */
  void cancel();

signals:
  /**
   * Informs FlowChamp of the information input by the user
   */
  void CGGoToManageRoom(QHostAddress addressIn, QString portIn,
                        QString roomCodeIn);

  /**
   * Informs FlowChamp the user wants to quit back to the DetermineDialog
   */
  void CGQuitGame();
};

#endif  // CREATEGAME_H
