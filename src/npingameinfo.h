#ifndef NPINGAMEINFO_H
#define NPINGAMEINFO_H

#include "nphosttoguest.h"

/**
 * Used to provide Mid-Game communication.
 * @details These will include the
 * - location of every ball
 * - Animation status of each player
 * - Score of each player
 * - Current High Score
 * etc
 */
class NPInGameInfo : public NPHostToGuest {
 private:
  /**
   * @copydoc NPHostToGuest::packetType
   */
  PacketType packetType = PacketType::INGAMEINFO;

  /// Holds animation status of player1.
  bool playerExtended[6];
  /// Holds the X Coordinates of each ball
  qint32 ballsX[25];
  /// Holds the Y COordinates of each abll
  qint32 ballsY[25];

  /// Holds the Score for each player
  qint32 scores[6];

  /**
   * Checks to see if the ball number is within range.
   * @param ballNum The number of the ball to check to see if it is valid.
   * @return True if the number is within range.
   */
  bool isBallPosValid(qint32 ballNum);

  /**
   * Checks to see if the player number is within range.
   * @param playerNum The number of the player to check to see if it is valid.
   * @return True if the number is within range.
   */
  bool isPlayerNumValid(qint32 playerNum);

  /// Holds the number of seconds remaining
  qint32 timeRemaining;

 public:
  NPInGameInfo(/* args */);
  ~NPInGameInfo();

  /**
   * Used to set the position of each ball individually.
   * @param ballNum Holds the number 0-24 for which ball you want to set the
   * position for
   * @param xCoord Holds the X Coordinate of the ball
   * @param yCoord Holds the Y Coordinate of the ball
   */
  void setBallPosition(qint32 ballNum, qint32 xCoord, qint32 yCoord);

  /**
   * Used to return the positions of all the balls as a 2D array.
   * @param ballNum Holds the number 0-24 for which ball you want to get the
   * position from.
   * @return A 2D array with the positions of all the ball requested. {x, y}
   */
  qint32* getBallPos(qint32 ballNum);

  /**
   * Used to return only the X Coordinate of the ball as a 2D array
   * @param ballNum Holds the number 0-24 for which ball you want to get the
   * position from.
   */
  qint32 getBallPosX(qint32 ballNum);

  /**
   * Used to return only the Y Coordinate of the ball as a 2D array
   * @param ballNum Holds the number 0-24 for which ball you want to get the
   * position from.
   */
  qint32 getBallPosY(qint32 ballNum);

  /**
   * Sets the score of the specific player.
   * @param playerNum The number (1-5) of the player you want.
   * @param score The score you want to set.
   */
  void setPlayerScore(qint32 playerNum, qint32 score);

  /**
   * Gets the score of the specific player.
   * @param playerNum The number (1-5) of the player you want.
   * @return The score of the player specified.
   */
  qint32 getPlayerScore(qint32 playerNum);

  /**
   * Gets the position of the player Extended or Retracted.
   * @param playerNum The number (1-5) of the player you want.
   */
  bool isPlayerExtended(qint32 playerNum);

  /**
   * Sets the animation position of the player or Retracted.
   * @param playerNum The number (1-5) of the player you want.
   * @param isExtended True if the player is extended.
   */
  void setPlayerExtension(qint32 playerNum, bool isExtended);

  /**
   * Used to set the amount of time remaining in Seconds.
   *
   */
  void setTimeRemaining(qint32 secondsRemaining);

  /**
   * Used to determine how much time is reamining in Seconds.
   * @return Seconds remaining.
   */
  qint32 getTimeRemaining();
};

#endif  // NPINGAMEINFO_H