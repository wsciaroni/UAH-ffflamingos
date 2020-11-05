#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include <QMap>
#include "hostmodel.h"
#include "playermodel.h"

class PlayerList
{
private:
    QMap<PlayerModel*, int> playerList;

public:
    PlayerList();
    ~PlayerList();

    /*
     * Add a player model to the QMap
     * returns true if successful
     */
    bool addPlayer(PlayerModel* playerModel);

    /*
     * Remove a player model from the QMap
     * returns true if successful
     */
    bool removePlayer(PlayerModel* playerModel);

    /*
     * Remove a player model from the QMap based on uid
     * Returns true if successful
     */
    bool removePlayer(int uid);

    /*
     * Return the player model based on uid
     */
    PlayerModel* getPlayer(int uid);

    /*
     * Return a player model based on the given position
     */
    PlayerModel* getPlayerByPosition(PlayerPosition position);

    /*
     * Returns the current player count
     */
    int getPlayerCount();

};

#endif // PLAYERLIST_H
