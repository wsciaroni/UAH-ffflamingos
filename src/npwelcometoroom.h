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
};

#endif  // NPWELCOMETOROOM_H