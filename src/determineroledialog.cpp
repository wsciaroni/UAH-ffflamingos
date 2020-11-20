#include "determineroledialog.h"
#include "ui_determineroledialog.h"

DetermineRoleDialog::DetermineRoleDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::DetermineRoleDialog) {
  ui->setupUi(this);

  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &DetermineRoleDialog::moveForward);
  connect(ui->buttonBox, &QDialogButtonBox::rejected, this,
          &DetermineRoleDialog::cancel);

  QRegularExpression userName("[a-zA-Z0-9]{1,10}");
  QRegularExpressionValidator* userNameValidator =
          new QRegularExpressionValidator(userName, ui->userName);
  ui->userName->setValidator(userNameValidator);
}

DetermineRoleDialog::~DetermineRoleDialog() { delete ui; }

void DetermineRoleDialog::moveForward() {
  if (!(ui->userName->text().isEmpty())) {
    if (ui->createGame->isChecked()) {   
      emit this->DRPlayAsHost(ui->userName->text());
    } else {
      emit this->DRPlayAsGuest(ui->userName->text());
    }
  }
}

void DetermineRoleDialog::cancel() {
  // emit this->DRQuitGame();
  this->reject();
}
