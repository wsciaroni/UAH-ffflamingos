#include "joinexistinggame.h"
#include "ui_joinexistinggame.h"

JoinExistingGame::JoinExistingGame(QWidget* parent)
    : QDialog(parent), ui(new Ui::JoinExistingGame) {
  ui->setupUi(this);

  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &JoinExistingGame::attemptToJoin);
  connect(ui->buttonBox, &QDialogButtonBox::rejected, this,
          &JoinExistingGame::cancel);

  QRegularExpression ipExpression(
      "(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})");
  QRegularExpressionValidator* ipValidator =
      new QRegularExpressionValidator(ipExpression, ui->ip);
  ui->ip->setValidator(ipValidator);

  QIntValidator* portValidator = new QIntValidator(1024, 65535, ui->port);
  ui->port->setValidator(portValidator);

  QIntValidator* roomCodeValidator = new QIntValidator(0, 999999, ui->roomCode);
  ui->roomCode->setValidator(roomCodeValidator);
}

JoinExistingGame::~JoinExistingGame() { delete ui; }

void JoinExistingGame::attemptToJoin() {
  if (!((ui->ip->text().isEmpty()) || (ui->port->text().isEmpty()) ||
        (ui->roomCode->text().isEmpty()))) {
    emit this->JGGoToWaitingToStart(QHostAddress(ui->ip->text()),
                                    ui->port->text(), ui->roomCode->text());
  }
}

void JoinExistingGame::cancel() { emit this->JGQuitGame(); }