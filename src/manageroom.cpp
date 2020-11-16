#include "manageroom.h"
#include "ui_manageroom.h"

#include <QtDebug>

ManageRoom::ManageRoom(QWidget* parent)
    : QDialog(parent), ui(new Ui::ManageRoom) {
  ui->setupUi(this);

  ui->players->setModel(&model);

  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &ManageRoom::startGame);
  connect(ui->buttonBox, &QDialogButtonBox::rejected, this,
          &ManageRoom::closeLobby);
}

ManageRoom::~ManageRoom() { delete ui; }

void ManageRoom::MRPassHostInfo(QString ip, QString port, QString roomCode) {
  ui->ipLabel->setText(ip);
  ui->portLabel->setText(port);
  ui->codeLabel->setText(roomCode);
}

void ManageRoom::startGame() { emit this->MRStartGameForAll(); }

void ManageRoom::closeLobby() { emit this->MRQuitGame(); }

void ManageRoom::MRUpdatePlayerList(QStringList usernameListIn) {
  this->model.setStringList(usernameListIn);
}