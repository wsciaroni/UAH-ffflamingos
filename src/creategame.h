#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "hostmodel.h"
#include "manageroom.h"
#include "error.h"

#include "hostnetworkhandler.h"

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
class CreateGame : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGame(QWidget *parent = nullptr);
    ~CreateGame();

    void passName(QString name);

private:
    Ui::CreateGame *ui;

    ManageRoom* waitingRoom;
    error* bindError;

    HostNetworkHandler* handler;

    /**
     * Function creates a dialog with an error
     */
    void throwBindError();

    /**
     * Used to move to the next window
     */
    void goToWaitingRoom();

    /**
     * This should hold the player name passed in by the DetermineRole Dialog
     */
    QString playerName = "";

    /**
     * Stores the PlayerModel for the host
     */
    HostModel* hostPlayer = nullptr;

    /**
     * Instantiates a PlayerModel for the Host with the information from the DetermineRole dialog and network connection
     */
    void createHost();

private slots:
    /**
     * Slot that attempts to bind IP and port
     */
    void bindIP_Port();
};

#endif // CREATEGAME_H
