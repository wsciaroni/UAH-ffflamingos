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
    /**
     * Constructor used to dynamically allocate memory
     * @param parent
     */
    explicit Connecting(QWidget *parent = nullptr);

    /**
     * Destructor used to deallocate memory
     */
    ~Connecting();

    /**
     * Used to Pass the name from the previous window.
     * @param name The user's name
     */
    void passName(QString name);

    /**
     * Used to pass the IP, Port, and RoomCode from the previous window.
     * @param ipIn The IP input by the user.
     * @param portIn The Port input by the user.
     * @param roomCodeIn The RoomCode input by the user.
     */
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
    
    /// Used to throw an error if there is an error connecting
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

    /**
     * Slot that is called when a roomCodeStatus packet is received.
     * @param roomCodeStatus Holds the user's uid and whether the room code was valid or invalid.
     */
    void handleRoomCodeStatus(NPRoomCodeStatus roomCodeStatus);
};

#endif // CONNECTING_H
