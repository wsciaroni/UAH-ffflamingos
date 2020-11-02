#ifndef MANAGEROOM_H
#define MANAGEROOM_H

#include <QDialog>
#include <QStringList>
#include <QStringListModel>

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

    /**
    Constructor
    */
    explicit ManageRoom(QWidget *parent = nullptr);

    /**
    Destructor
    */
    ~ManageRoom();

private:
    ///ui pointer
    Ui::ManageRoom *ui;

    ///Holds the list of playernames to be displayed
    QStringList list;

    ///Model for list
    QStringListModel model;

private slots:
   /**
   @todo Transfers players from wait room to game state.
   */
   void startGame();

   /**
   @todo will forcibly close the lobby, disconnecting all players
   */
   void closeLobby();

public slots:

   /**
   addPlayer should be called when a player has successfully connected
   @param
   */
   void addPlayer(QString name);

   /**
   removePlayer should be called when a player disconnects either via connection drop or self disconnect.
   @param name Pass the username of the player
   */
   void removePlayer(QString name);
};

#endif // MANAGEROOM_H
