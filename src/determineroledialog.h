#ifndef DETERMINEROLEDIALOG_H
#define DETERMINEROLEDIALOG_H

#include "creategame.h"
#include "joinexistinggame.h"

#include <QDialog>

namespace Ui {
class DetermineRoleDialog;
}

class DetermineRoleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetermineRoleDialog(QWidget *parent = nullptr);
    ~DetermineRoleDialog();

private:
    Ui::DetermineRoleDialog *ui;
    
    CreateGame* createGameDialog;
    JoinExistingGame* joinGameDialog;

    void createGame();
    void joinGame();

public slots:
    /**
     * Slot that calls out to the next dialog and accepts this QDialog
     */
    void moveForward();
};

#endif // DETERMINEROLEDIALOG_H
