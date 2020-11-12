#ifndef JOINEXISTINGGAME_H
#define JOINEXISTINGGAME_H

#include "connecting.h"
#include "error.h"

#include <QDialog>
#include <QString>

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

    void passName(QString name);

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

    /**
     * This should hold the player name passed in by the DetermineRole Dialog
     */
    QString playerName = "";

private slots:
    /**
     * slot that attempts to join game if IP and port are valid
     */
    void attemptToJoin();


};

#endif // JOINEXISTINGGAME_H
