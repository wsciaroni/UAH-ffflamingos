#ifndef JOINEXISTINGGAME_H
#define JOINEXISTINGGAME_H

#include "connecting.h"
#include "error.h"

#include <QDialog>

namespace Ui {
class JoinExistingGame;
}

/**
 * Used to have the guest enter the details of the game he wishes to join
 */
class JoinExistingGame : public QDialog
{
    Q_OBJECT

public:
    explicit JoinExistingGame(QWidget *parent = nullptr);
    ~JoinExistingGame();

private:
    Ui::JoinExistingGame *ui;

    Connecting* connectingScreen;
    error* missingField;
    /**
     * Go to connecting window
     */
    void goToConnecting();
    /**
     * Throws error for missing required field
     */
    void missingFieldError();

private slots:
    /**
     * Slot that calls out to the next dialog and accepts this QDialog
     */
    void attemptToJoin();


};

#endif // JOINEXISTINGGAME_H
