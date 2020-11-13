#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include <QMap>
#include "hostmodel.h"
#include "playermodel.h"

#include "npgeneric.h"

/**
 * @brief The PlayerList class
 * @details Contains a map of players to UIDs, with supporting methods
 */
class PlayerList {
 private:
  /// Map containing the PlayerModel that have joined, with dynamically updated
  /// UIDs
  QMap<PlayerModel*, int> playerList;

  /**
   * Handle Incoming Connections on TCPServer
   */
  void processNetworkPackets();

 public:
  /// Contructor methods for PlayerList (created on room creation)
  PlayerList();
  /// Destructor (after game ends)
  ~PlayerList();

  /**
   * Add a player model to the QMap
   * @param playerModel Reference to the player model to add
   * @return true if successful
   */
  bool addPlayer(PlayerModel* playerModel);

  /**
   * Remove a player model from the QMap
   * @param playerModel reference to the player model to remove
   * @return true if successful
   */
  bool removePlayer(PlayerModel* playerModel);

  /**
   * Remove a player model from the QMap based on uid
   * @param uid UID of the player to remove
   * @return true if successful
   */
  bool removePlayer(int uid);

  /**
   * Return the player model based on uid
   * @param uid UID of the player to get the Player Model of
   * @return The Player Model if found, otherwise nullptr
   */
  PlayerModel* getPlayer(int uid);

  /**
   * Return the player model based on QTcpSocket
   * @param socket the QTcpSocket of the player to get the Player Model of
   * @return The Player Model if found, otherwise nullptr
   */
  PlayerModel* getPlayer(QTcpSocket* socket);

  /**
   * Return a player model based on the given position
   * @param position The PlayerPosition of the player modoel to get
   * @return the Player Model if found, otherwise nullptr
   */
  PlayerModel* getPlayerByPosition(PlayerPosition position);

  /**
   * Returns the current player count
   * @return returns the current number of players in the game
   */
  int getPlayerCount();
};

#endif  // PLAYERLIST_H
