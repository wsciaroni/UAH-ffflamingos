#include "npendgameinfo.h"

NPEndGameInfo::NPEndGameInfo(/* args */) {}

NPEndGameInfo::~NPEndGameInfo() {}

void NPEndGameInfo::setWinnerInfo(QString winnerNameIn, qint32 winnerScoreIn) {
  winnerName = winnerNameIn;
  winnerScore = winnerScoreIn;
}

QString NPEndGameInfo::getWinnerName() { return winnerName; }

qint32 NPEndGameInfo::getWinnerScore() { return winnerScore; }

void NPEndGameInfo::setHighScoreInfo(QString highScoreHolderIn,
                                     qint32 highScoreIn) {
  highScoreHolder = highScoreHolderIn;
  highScore = highScoreIn;
}

QString NPEndGameInfo::getHighScoreName() { return highScoreHolder; }

qint32 NPEndGameInfo::getHighScore() { return highScore; }