#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include "playermodel.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QtGui>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include "ball.h"

namespace Ui {
class GameDialog;
}

/**
 * Window that houses the game play.
 * Used on both the Host and the Guest to display the map, info, and such in the
 * game.
 */
class GameDialog : public QDialog {
  Q_OBJECT

 public:
  /**
   * Constructor used to dynamically allocate memory
   * @param parent
   */
  explicit GameDialog(QWidget *parent = nullptr);

  /**
   * Destructor used to deallocate memory
   */
  ~GameDialog();

  /**
   * Draws the board onto the dialog
   */
  void drawBoard();

  /**
   * Extends the given players head
   * @param PlayerPosition to retract
   */
  void extendHead(int playerPos);

  /**
   * Retracts the given players head
   * @param PlayerPosition to retract
   */
  void retractHead(int playerPos);

  /**
  * Place the given player on the board
  * @param PlayerPosition to place
  */
  void spawnPlayer(int playerPos);

  /**
   * Calls spawn player for each player
   */
  void spawnAllPlayers();

  /**
   * Used to draw the balls in the appropriate places on the GameDialog
   * @param xPos Array of X coordinates of each ball
   * @param yPos Array of Y coordinates of each ball
   */
  void setBallPos(qint32 xPos[25], qint32 yPos[25]);

  /**
   * Determines what balls are in collision with the specific player
   */
  bool *determineCapturedBalls(PlayerPosition pos);

 private:
  Ui::GameDialog *ui;
  QGraphicsScene *scene;
  QGraphicsEllipseItem *gameBoard;

  QGraphicsItem *player1Body;
  QGraphicsItem *player1Head;
  QGraphicsItem *player2Body;
  QGraphicsItem *player2Head;
  QGraphicsItem *player3Body;
  QGraphicsItem *player3Head;
  QGraphicsItem *player4Body;
  QGraphicsItem *player4Head;
  QGraphicsItem *player5Body;
  QGraphicsItem *player5Head;
  ball *gameBalls[25];

 protected:
  /**
   * @brief A Key Press Event handler (will be used for escape)
   * @param key
   */
  void keyPressEvent(QKeyEvent *key);

/*
 * Repaint the scene
 */
// void paintEvent(QPaintEvent* e);

signals:
  /**
   * Informs FlowChamp that the user has pressed the space bar
   */
  void GDSpacePressed();

  /**
   * Informs FlowChamp that the user has pressed the escape key
   */
  void GDEscPressed();

  /**
   * Informs FlowChamp that the user desires to leave the game
   * @deprecated
   */
  void GDQuitGame();

 public
slots:
  /**
   * Slot to be triggered when
   */
  void HandleInfoIn(/*TBD*/);
};

#endif  // GAMEDIALOG_H
