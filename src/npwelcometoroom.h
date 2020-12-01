#ifndef NPWELCOMETOROOM_H
#define NPWELCOMETOROOM_H

#include "nphosttoguest.h"

/**
 * Used to signal the start of the game.
 */
class NPWelcomeToRoom : public NPHostToGuest {
 private:
  /**
   * @copydoc NPHostToGuest::packetType
   */
  PacketType packetType = PacketType::WELCOMETOROOM;

  /**
   * The position of the user
   */
  int position = 0;

  /**
   * Holds the player names
   */
  QString playerNames[6];

 public:
  NPWelcomeToRoom(/* args */);
  ~NPWelcomeToRoom();

  /**
   * Sets the position in the packet
   * @param position the position of the player as relates to PlayerPosition
   */
  void setPositionId(int positionIn);

  /**
   * Gets the position from the packet
   * @return the position of the player as realtes to PlayerPosition
   */
  int getPositionId();

  /**
   * Sets the names of each player.
   * @param names An array of the player names with the high score holder as p0.
   */
  void setNames(QString names[6]);

  /**
   * Gets the names of each player.
   * @return An array of the player names with the high score holder as p0.
   */
  QString* getNames();
};

#endif  // NPWELCOMETOROOM_H