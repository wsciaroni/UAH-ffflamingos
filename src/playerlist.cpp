#include "playerlist.h"



PlayerList::PlayerList() {

}

PlayerList::~PlayerList() {

}

bool PlayerList::addPlayer(PlayerModel *playerModel) {
    if(playerList.contains(playerModel)) {
        // Return false, because we don't want to add a player twice
        return false;
    } else {
        playerList.insert(playerModel, playerModel->getUID());
        return true; // Successful insertion
    }
}

bool PlayerList::removePlayer(PlayerModel *playerModel) {
    if(playerList.contains(playerModel)) {
        playerList.remove(playerModel);
        return true; // Successful removal
    } else {
        return false; // Unsuccessful removal
    }
}

bool PlayerList::removePlayer(int uid) {
    if(playerList.key(uid) && playerList.contains(playerList.key(uid))) {
        playerList.remove(playerList.key(uid)); // Remove the key
        return true; // Successfully found and removed
    } else {
        return false; // If unsuccessful (not found) return false
    }
}

PlayerModel* PlayerList::getPlayer(int uid) {
    return playerList.key(uid); // Return the player model with uid
}

PlayerModel* PlayerList::getPlayerByPosition(PlayerPosition position) {
    // Iterate through the map, and if we find a position return it.

    for(PlayerModel* temp : playerList.keys()) {
        if(temp->getPositionId() == position) {
            return temp; // Return the player at the given position
        }
    }

    return nullptr; // If no player at the given position, return null
}

int PlayerList::getPlayerCount() {
    return playerList.keys().length(); // Return the current number of keys
}

