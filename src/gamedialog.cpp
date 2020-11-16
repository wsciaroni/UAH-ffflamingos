#include "gamedialog.h"
#include "ui_gamedialog.h"

GameDialog::GameDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::GameDialog) {
  ui->setupUi(this);
}

GameDialog::~GameDialog() { delete ui; }

void GameDialog::keyPressEvent(QKeyEvent* key) {
  if (key->key() == Qt::Key_Escape) {
    emit this->GDEscPressed();
  } else if (key->key() == Qt::Key_Space) {
    emit this->GDSpacePressed();
  }
}

void GameDialog::HandleInfoIn(/*TBD*/) {}