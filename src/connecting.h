#ifndef CONNECTING_H
#define CONNECTING_H

#include "waitingtostart.h"

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

private:
    Ui::Connecting *ui;

    /// QDialog for waiting screen
    WaitingToStart* waitingScreen;

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
