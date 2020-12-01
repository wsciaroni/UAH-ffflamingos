#ifndef NPENDGAMEINFO_H
#define NPENDGAMEINFO_H

#include "nphosttoguest.h"

/**
 * Used to provide End of Game Information.
 */
class NPEndGameInfo : public NPHostToGuest {
 private:
  /// Used to hold the winner of this game's name.
  QString winnerName;

  /// Used to hold the winner's score
  qint32 winnerScore;

  /// Used to hold the high score holder's name on the Host's machine
  QString highScoreHolder;

  /// Used to hold the high score on the Host's machine
  qint32 highScore;

 public:
  NPEndGameInfo();
  ~NPEndGameInfo();

  /**
   * Used to set the winner's name and score
   * @param winnerNameIn The username of the winner
   * @param winnerScoreIn The final score of the winner
   */
  void setWinnerInfo(QString winnerNameIn, qint32 winnerScoreIn);

  /**
   * Used to return the winner's name
   * @return The winner of the current game's username
   */
  QString getWinnerName();

  /**
   * Used to return the winner's score
   * @return The winner of the current game's score
   */
  qint32 getWinnerScore();

  /**
   * Used to set the high score holder's name and score
   * @param highScoreHolderIn The Name of the high score holder on the Host's
   * machine.
   * @param highScoreIn The high score from the Host's machine.
   */
  void setHighScoreInf(QString highScoreHolderIn, qint32 highScoreIn);

  /**
   * Used to return the Name of the high score holder.
   * @return The name of the high score holder
   */
  QString getHighScoreName();

  /**
   * Used to return the high score
   * @return The high score on the Host's machine.
   */
  qint32 getHighScore();
};

#endif  // NPENDGAMEINFO_H