#include "creategame.h"

CreateGame::CreateGame(QWidget* parent)
    : QDialog(parent), ui(new Ui::CreateGame) {
  ui->setupUi(this);

  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &CreateGame::goToWaitingRoom);
  connect(ui->buttonBox, &QDialogButtonBox::rejected, this,
          &CreateGame::cancel);

  QIntValidator* portValidator = new QIntValidator(1024, 65535, ui->port);
  ui->port->setValidator(portValidator);

  QIntValidator* roomCodeValidator = new QIntValidator(0, 999999, ui->roomCode);
  ui->roomCode->setValidator(roomCodeValidator);

  // gets list of all network interfaces
  QList<QHostAddress> addressList = QNetworkInterface::allAddresses();
  // adds list of addresses to dropdown menu
  for (int i = 0; i < addressList.size(); i++) {
    if (QAbstractSocket::IPv4Protocol == addressList[i].protocol())
      ui->ipDropdown->addItem(addressList[i].toString());
  }
}

CreateGame::~CreateGame() { delete ui; }

void CreateGame::goToWaitingRoom() {
  emit this->CGGoToManageRoom(QHostAddress(ui->ipDropdown->currentText()),
                              ui->port->text(), ui->roomCode->text());
}

void CreateGame::cancel() { emit this->CGQuitGame(); }