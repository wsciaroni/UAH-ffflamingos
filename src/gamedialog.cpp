#include "gamedialog.h"
#include "ui_gamedialog.h"
#include <QtMath>
#include <QGraphicsTextItem>

GameDialog::GameDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::GameDialog) {
  ui->setupUi(this);

  window()->setFixedSize(800, 800);  // No resizing
}

GameDialog::~GameDialog() { delete ui; }

void GameDialog::keyPressEvent(QKeyEvent* key) {
  if (key->key() == Qt::Key_Escape) {
    emit this->GDEscPressed();
  } else if (key->key() == Qt::Key_Space) {
    emit this->GDSpacePressed();
  }
}

void GameDialog::drawBoard() {

  scene = new QGraphicsScene(this);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  // scene->setSceneRect(0, 0, 400, 400);
  scene->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

  ui->graphicsView->setScene(scene);
  ui->graphicsView->setRenderHint(QPainter::Antialiasing);

  // Create ellipse
  QPen ellipsePen(Qt::red);
  ellipsePen.setWidth(10);

  gameBoard =
      scene->addEllipse(-300, -300, 600, 600, ellipsePen, QBrush(Qt::gray));

  // Lower Left
  player1Body =
      scene->addRect(-10, -290, 20, 150, QPen(Qt::black), QBrush(Qt::magenta));
  player1Head =
      scene->addRect(-25, -190, 50, 50, QPen(Qt::black), QBrush(Qt::magenta));
  player1Body->setRotation(-144);
  player1Head->setRotation(-144);
  player1Body->setVisible(false);
  player1Head->setVisible(false);

  // Upper Left
  player2Body =
      scene->addRect(-10, -290, 20, 150, QPen(Qt::black), QBrush(Qt::cyan));
  player2Head =
      scene->addRect(-25, -190, 50, 50, QPen(Qt::black), QBrush(Qt::cyan));
  player2Body->setRotation(-72);
  player2Head->setRotation(-72);
  player2Body->setVisible(false);
  player2Head->setVisible(false);

  // Center
  player3Body =
      scene->addRect(-10, -290, 20, 150, QPen(Qt::black), QBrush(Qt::yellow));
  player3Head =
      scene->addRect(-25, -190, 50, 50, QPen(Qt::black), QBrush(Qt::yellow));
  player3Body->setVisible(false);
  player3Head->setVisible(false);

  // Upper Right
  player4Body =
      scene->addRect(-10, -290, 20, 150, QPen(Qt::black), QBrush(Qt::green));
  player4Head =
      scene->addRect(-25, -190, 50, 50, QPen(Qt::black), QBrush(Qt::green));
  player4Body->setRotation(72);
  player4Head->setRotation(72);
  player4Body->setVisible(false);
  player4Head->setVisible(false);

  // Lower Right
  player5Body =
      scene->addRect(-10, -290, 20, 150, QPen(Qt::black), QBrush(Qt::blue));
  player5Head =
      scene->addRect(-25, -190, 50, 50, QPen(Qt::black), QBrush(Qt::blue));
  player5Body->setRotation(144);
  player5Head->setRotation(144);
  player5Body->setVisible(false);
  player5Head->setVisible(false);

  head1_retracted = player1Head->pos();
  head2_retracted = player2Head->pos();
  head3_retracted = player3Head->pos();
  head4_retracted = player4Head->pos();
  head5_retracted = player5Head->pos();

  head1_extended.setX(head1_retracted.x() + -50 * qSin(-144 * M_PI / 180));
  head1_extended.setY(head1_retracted.y() + 50 * qCos(-144 * M_PI / 180));

  head2_extended.setX(head1_retracted.x() + -50 * qSin(-72 * M_PI / 180));
  head2_extended.setY(head1_retracted.y() + 50 * qCos(-72 * M_PI / 180));

  head3_extended.setX(head1_retracted.x());
  head3_extended.setY(head1_retracted.y() + 50);

  head4_extended.setX(head1_retracted.x() + -50 * qSin(72 * M_PI / 180));
  head4_extended.setY(head1_retracted.y() + 50 * qCos(72 * M_PI / 180));

  head5_extended.setX(head1_retracted.x() + -50 * qSin(144 * M_PI / 180));
  head5_extended.setY(head1_retracted.y() + 50 * qCos(144 * M_PI / 180));

  // initializing balls
  for (int i = 0; i < 25; i++) {
    gameBalls[i] = new ball;
    gameBalls[i]->setPos(0, 0);
    scene->addItem(gameBalls[i]);
  }

  hiddenSquare =
      scene->addRect(-25, -425, 50, 50, QPen(Qt::black), QBrush(Qt::black));
  hiddenSquare->setZValue(100);

  QFont font1;
  font1.setPixelSize(10);
  font1.setPointSize(17);
  font1.setFamily("Arial");

  QFont font2;
  font2.setPixelSize(10);
  font2.setPointSize(15);
  font2.setFamily("Arial");

  timeRemainingLabel = new QGraphicsTextItem;
  timeRemaining = new QGraphicsTextItem;

  highScore = new QGraphicsTextItem;
  player1Score = new QGraphicsTextItem;
  player2Score = new QGraphicsTextItem;
  player3Score = new QGraphicsTextItem;
  player4Score = new QGraphicsTextItem;
  player5Score = new QGraphicsTextItem;

  highScoreName = new QGraphicsTextItem;
  player1Name = new QGraphicsTextItem;
  player2Name = new QGraphicsTextItem;
  player3Name = new QGraphicsTextItem;
  player4Name = new QGraphicsTextItem;
  player5Name = new QGraphicsTextItem;

  timeRemainingLabel->setPos(-120, -370);
  timeRemainingLabel->setDefaultTextColor("red");
  timeRemainingLabel->setPlainText("TIME REMAINING:");
  timeRemainingLabel->setFont(font1);

  timeRemaining->setPos(90, -370);
  timeRemaining->setDefaultTextColor("red");
  timeRemaining->setPlainText("60");
  timeRemaining->setFont(font1);

  highScoreName->setPos(-350, -425);
  highScoreName->setDefaultTextColor("red");
  highScoreName->setPlainText("HIGH SCORE:");
  highScoreName->setFont(font2);

  player1Name->setPos(-350, -375);
  player1Name->setDefaultTextColor("magenta");
  player1Name->setPlainText("Player 1:");
  player1Name->setFont(font2);

  player2Name->setPos(-350, -325);
  player2Name->setDefaultTextColor("cyan");
  player2Name->setPlainText("Player 2:");
  player2Name->setFont(font2);

  // player3Name->setPos(-325, -350);
  player3Name->setPos(205, -425);
  player3Name->setDefaultTextColor("yellow");
  player3Name->setPlainText("Player 3:");
  player3Name->setFont(font2);

  // player4Name->setPos(-325, -325);
  player4Name->setPos(205, -375);
  player4Name->setDefaultTextColor("green");
  player4Name->setPlainText("Player 4:");
  player4Name->setFont(font2);

  // player5Name->setPos(-325, -300);
  player5Name->setPos(205, -325);
  player5Name->setDefaultTextColor("blue");
  player5Name->setPlainText("Player 5:");
  player5Name->setFont(font2);

  highScore->setPos(-205, -425);
  highScore->setDefaultTextColor("red");
  highScore->setPlainText("0");
  highScore->setFont(font2);

  player1Score->setPos(-205, -375);
  player1Score->setDefaultTextColor("magenta");
  player1Score->setPlainText("0");
  player1Score->setFont(font2);

  player2Score->setPos(-205, -325);
  player2Score->setDefaultTextColor("cyan");
  player2Score->setPlainText("0");
  player2Score->setFont(font2);

  // player3Score->setPos(-240, -350);
  player3Score->setPos(350, -425);
  player3Score->setDefaultTextColor("yellow");
  player3Score->setPlainText("0");
  player3Score->setFont(font2);

  // player4Score->setPos(-240, -325);
  player4Score->setPos(350, -375);
  player4Score->setDefaultTextColor("green");
  player4Score->setPlainText("0");
  player4Score->setFont(font2);

  // player5Score->setPos(-240, -300);
  player5Score->setPos(350, -325);
  player5Score->setDefaultTextColor("blue");
  player5Score->setPlainText("0");
  player5Score->setFont(font2);

  scene->addItem(timeRemainingLabel);
  scene->addItem(timeRemaining);
  scene->addItem(highScore);
  scene->addItem(player1Score);
  scene->addItem(player2Score);
  scene->addItem(player3Score);
  scene->addItem(player4Score);
  scene->addItem(player5Score);
  scene->addItem(highScoreName);
  scene->addItem(player1Name);
  scene->addItem(player2Name);
  scene->addItem(player3Name);
  scene->addItem(player4Name);
  scene->addItem(player5Name);

  qDebug() << "Drawing Board" << endl;
}

void GameDialog::extendHead(int playerPos) {
  // qDebug() << "Extending " << playerPos << endl;
  switch (playerPos) {
    case 0:
      break;
    case 1:
      player1Head->setPos(head1_extended);
      break;
    case 2:
      player2Head->setPos(head2_extended);
      break;
    case 3:
      player3Head->setPos(head3_extended);
      break;
    case 4:
      player4Head->setPos(head4_extended);
      break;
    case 5:
      player5Head->setPos(head5_extended);
      break;
    default:
      break;
  }
}

void GameDialog::retractHead(int playerPos) {
  // qDebug() << "Retracting " << playerPos << endl;
  switch (playerPos) {
    case 0:
      break;
    case 1:
      player1Head->setPos(head1_retracted);
      break;
    case 2:
      player2Head->setPos(head2_retracted);
      break;
    case 3:
      player3Head->setPos(head3_retracted);
      break;
    case 4:
      player4Head->setPos(head4_retracted);
      break;
    case 5:
      player5Head->setPos(head5_retracted);
      break;
    default:
      break;
  }
}

void GameDialog::spawnPlayer(int playerPos) {
  switch (playerPos) {
    case 0:
      break;
    case 1:
      player1Body->setVisible(true);
      player1Head->setVisible(true);
    case 2:
      player2Body->setVisible(true);
      player2Head->setVisible(true);
    case 3:
      player3Body->setVisible(true);
      player3Head->setVisible(true);
    case 4:
      player4Body->setVisible(true);
      player4Head->setVisible(true);
    case 5:
      player5Body->setVisible(true);
      player5Head->setVisible(true);
    default:
      break;
  }
}

void GameDialog::spawnAllPlayers() {
  for (int i = 1; i <= 5; i++) {
    spawnPlayer(i);
  }
}

void GameDialog::setBallPos(qint32 xPos[25], qint32 yPos[25]) {
  /// @todo draw balls at each coordinate pair.
  for (int i = 0; i < 25; i++) {
    gameBalls[i]->setPos(xPos[i], yPos[i]);
  }
}

void GameDialog::updateInfo(qint32 scores[6], qint32 timeRemainingValue) {
  timeRemaining->setPlainText(QString::number(timeRemainingValue, 10));

  for (int i = 0; i < 6; i++) {
    switch (i) {
      case 0:
        highScore->setPlainText(QString::number(scores[i], 10));
        break;
      case 1:
        player1Score->setPlainText(QString::number(scores[i], 10));
        break;
      case 2:
        player2Score->setPlainText(QString::number(scores[i], 10));
        break;
      case 3:
        player3Score->setPlainText(QString::number(scores[i], 10));
        break;
      case 4:
        player4Score->setPlainText(QString::number(scores[i], 10));
        break;
      case 5:
        player5Score->setPlainText(QString::number(scores[i], 10));
        break;
      default:
        break;
    }
  }
}
void GameDialog::setNames(QString names[6]) {
  for (int i = 0; i < 6; i++) {
    if (names[i] == "") {
      continue;
    } else {
      switch (i) {
        case 0:
          highScoreName->setPlainText(names[i] + ':');
          break;
        case 1:
          player1Name->setPlainText(names[i] + ':');
          break;
        case 2:
          player2Name->setPlainText(names[i] + ':');
          break;
        case 3:
          player3Name->setPlainText(names[i] + ':');
          break;
        case 4:
          player4Name->setPlainText(names[i] + ':');
          break;
        case 5:
          player5Name->setPlainText(names[i] + ':');
          break;
        default:
          break;
      }
    }
  }
}

bool* GameDialog::determineCapturedBalls(PlayerPosition pos) {
  static bool isColliding[25];
  for (int i = 0; i < 25; i++) {
    isColliding[i] = false;
  }

  QGraphicsItem* player = NULL;
  switch (pos) {
    case PlayerPosition::LOWER_LEFT:
      player = player1Head;
      break;
    case PlayerPosition::UPPER_LEFT:
      player = player2Head;
      break;
    case PlayerPosition::CENTER:
      player = player3Head;
      break;
    case PlayerPosition::UPPER_RIGHT:
      player = player4Head;
      break;
    case PlayerPosition::LOWER_RIGHT:
      player = player5Head;
      break;
    default:
      return NULL;
  }
  for (int i = 0; i < 25; i++) {
    isColliding[i] =
        player->collidesWithItem(gameBalls[i], Qt::IntersectsItemShape);
  }
  return isColliding;
}

void GameDialog::HandleInfoIn(QString highScoreHolder, qint32 highScore,
                              QString winnerName, qint32 winnerScore) {

  /// @todo display information over game window when this is called (At the end
  /// of the game)
  /// Create 4 QGraphicsTextItems that will display the following theme:
  /// High Score: ##
  /// Held by: ###########
  ///
  /// Game Winner: ########
  /// With a Score of: ######

  // Useful notes: Display the following Really big and bold over the screen
  // "High Score: " + QString::number(highScore,10)
  // "Held By: " + highScoreHolder
  // "Game Winner: " + winnerName;
  // "With a Score of: " + QString::number(winnerScore,10)
  QGraphicsSimpleTextItem* HighScore;
  QGraphicsSimpleTextItem* HighScoreHolder;
  QGraphicsSimpleTextItem* WinnerName;
  QGraphicsSimpleTextItem* WinnerScore;

  HighScore = new QGraphicsSimpleTextItem;
  HighScoreHolder = new QGraphicsSimpleTextItem;
  WinnerName = new QGraphicsSimpleTextItem;
  WinnerScore = new QGraphicsSimpleTextItem;

  QPen pen;
  pen.setColor(QColor("white"));

  QFont font;
  font.setPixelSize(48);

  HighScore->setText("High Score: " + QString::number(highScore, 10));
  HighScoreHolder->setText("Held by: " + highScoreHolder);
  WinnerName->setText("Game Winner: " + winnerName);
  WinnerScore->setText("With a Score of: " + QString::number(winnerScore, 10));

  HighScore->setPos(-200,-150);
  HighScoreHolder->setPos(-200, -100);
  WinnerName->setPos(-200, 0);
  WinnerScore->setPos(-200, 50);

  HighScore->setPen(pen);
  HighScoreHolder->setPen(pen);
  WinnerName->setPen(pen);
  WinnerScore->setPen(pen);

  HighScore->setFont(font);
  HighScoreHolder->setFont(font);
  WinnerName->setFont(font);
  WinnerScore->setFont(font);

  scene->addItem(HighScore);
  scene->addItem(HighScoreHolder);
  scene->addItem(WinnerName);
  scene->addItem(WinnerScore);
}
