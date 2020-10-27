#ifndef JOINEXISTINGGAME_H
#define JOINEXISTINGGAME_H

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
};

#endif // JOINEXISTINGGAME_H
