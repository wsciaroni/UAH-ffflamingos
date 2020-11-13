#include "determineroledialog.h"
#include "ui_determineroledialog.h"

DetermineRoleDialog::DetermineRoleDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::DetermineRoleDialog) {
  ui->setupUi(this);

  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &DetermineRoleDialog::moveForward);
}

DetermineRoleDialog::~DetermineRoleDialog() { delete ui; }

void DetermineRoleDialog::createGame() {
  createGameDialog = new CreateGame;
  this->hide();
  createGameDialog->passName(ui->userName->text());
  createGameDialog->exec();
  delete createGameDialog;
  this->show();
}

void DetermineRoleDialog::joinGame() {
  joinGameDialog = new JoinExistingGame;
  this->hide();
  joinGameDialog->passName(ui->userName->text());
  joinGameDialog->exec();
  delete joinGameDialog;
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
