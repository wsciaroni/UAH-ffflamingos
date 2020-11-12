#ifndef CONNECTING_H
#define CONNECTING_H

#include "waitingtostart.h"
#include "ui_connecting.h"
#include "guestnetworkhandler.h"
#include "error.h"

#include <QDialog>

namespace Ui {
class Connecting;
}

/**
 * Used to indicate to a guest that his machine is attempting to connect
 */
class Connecting : public QDialog
{
    Q_OBJECT

public:
    explicit Connecting(QWidget *parent = nullptr);
    ~Connecting();

    void passName(QString name);
    void passInfo(QString ipIn, QString portIn, QString roomCodeIn);

private:
    Ui::Connecting *ui;

    /// QDialog for waiting screen
    WaitingToStart* waitingScreen;

    /// Holds the name of the current user
    QString playerName = "";

    /// Holds the IP of the host
    QString ip;

    /// Holds the port to attempt to connect to and to listen on
    QString port;

    /// Holds the value of the user entered room code
    QString roomCode;

    /// Handles all networking on the Guest
    GuestNetworkHandler* handler;
    
    error* throwError;

private slots:
    /**
     * Slot that calls out to the next dialog and accepts this QDialog
     */
    void goToWaitingScreen();

    /**
     * Slot to cancel a network connection in process
     */
    void cancel();
};

#endif // CONNECTING_H
