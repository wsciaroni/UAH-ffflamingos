#ifndef MANAGEROOM_H
#define MANAGEROOM_H

#include <QDialog>

namespace Ui {
class ManageRoom;
}

/**
 * Used to have the host see who has joined the game, and allows the host to start the game.
 */
class ManageRoom : public QDialog
{
    Q_OBJECT

public:
    explicit ManageRoom(QWidget *parent = nullptr);
    ~ManageRoom();

private:
    Ui::ManageRoom *ui;
};

#endif // MANAGEROOM_H
