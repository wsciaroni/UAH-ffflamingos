#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "manageroom.h"
#include "error.h"

#include <QDialog>
#include <QTcpServer>

namespace Ui {
class CreateGame;
}

/**
 * Used to have the host enter the details to bind to an ip and port
 */
class CreateGame : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGame(QWidget *parent = nullptr);
    ~CreateGame();

private:
    Ui::CreateGame *ui;

    ManageRoom* waitingRoom;
    error* bindError;
    QTcpServer* TcpServer;

    void throwBindError();
    void goToWaitingRoom();

private slots:
    /**
     * Slot that calls out to the next dialog and accepts this QDialog
     */

    void bindIP_Port();
};

#endif // CREATEGAME_H
