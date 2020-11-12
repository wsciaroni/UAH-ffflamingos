#include "determineroledialog.h"
#include "ui_determineroledialog.h"

DetermineRoleDialog::DetermineRoleDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::DetermineRoleDialog) {
  ui->setupUi(this);

  createGameDialog = new CreateGame;
  joinGameDialog = new JoinExistingGame;
  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &DetermineRoleDialog::moveForward);
}

DetermineRoleDialog::~DetermineRoleDialog() {
  delete ui;
  delete createGameDialog;
  delete joinGameDialog;
}

void DetermineRoleDialog::createGame() {
  this->hide();
  createGameDialog->passName(ui->userName->text());
  createGameDialog->exec();
  this->show();
}

void DetermineRoleDialog::joinGame() {
  this->hide();
  joinGameDialog->passName(ui->userName->text());
  joinGameDialog->exec();
  this->show();
}

void DetermineRoleDialog::moveForward() {
  if (!(ui->userName->text().isEmpty())) {
    if (ui->createGame->isChecked()) {
      createGame();
    } else {
      joinGame();
    }
  }
}
