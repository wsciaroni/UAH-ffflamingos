#include "joinexistinggame.h"
#include "ui_joinexistinggame.h"
#include <QIntValidator>
#include <QRegularExpressionValidator>

JoinExistingGame::JoinExistingGame(QWidget* parent)
    : QDialog(parent), ui(new Ui::JoinExistingGame) {
  ui->setupUi(this);

  // missingField = new error;

  this->connectingScreen = new Connecting;
  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &JoinExistingGame::attemptToJoin);

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

JoinExistingGame::~JoinExistingGame() {
  delete ui;
  delete connectingScreen;
}

void JoinExistingGame::passName(QString name) { playerName = name; }

void JoinExistingGame::goToConnecting() {
  this->hide();
  connectingScreen->passName(playerName);
  bool connected = connectingScreen->passInfo(ui->ip->text(), ui->port->text(),
                                              ui->roomCode->text());
  if (connected) {
    connectingScreen->exec();
  }
  this->accept();
}

void JoinExistingGame::missingFieldError() {
  this->hide();
  missingField = new error;
  missingField->throwErrorMsg("ERROR: Missing required field");
  missingField->exec();
  delete missingField;
  this->accept();
}

void JoinExistingGame::attemptToJoin() {
  if ((ui->ip->text().isEmpty()) || (ui->port->text().isEmpty()) ||
      (ui->roomCode->text().isEmpty())) {
    missingFieldError();
  } else {
    goToConnecting();
  }
}
