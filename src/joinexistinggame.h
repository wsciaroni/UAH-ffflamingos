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
    /**
     * Constructor used to dynamically allocate memory
     * @param parent
     */
    explicit JoinExistingGame(QWidget *parent = nullptr);

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
    Ui::JoinExistingGame *ui;

    /// Holds the address of the next screen.  Used to move forward into the next dialog.
    Connecting* connectingScreen;

    /// Holds the address of an error.  Used to throw that error.
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
