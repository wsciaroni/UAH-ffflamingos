#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QDialog>

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
};

#endif // CREATEGAME_H
