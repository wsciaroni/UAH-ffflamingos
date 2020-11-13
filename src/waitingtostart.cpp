#include "waitingtostart.h"
#include "ui_waitingtostart.h"

WaitingToStart::WaitingToStart(QWidget* parent)
    : QDialog(parent), ui(new Ui::WaitingToStart) {
  ui->setupUi(this);
  gameWindow = new GameDialog;
  connect(ui->disconnect, &QPushButton::clicked, this,
          &WaitingToStart::disconnect);
}

WaitingToStart::~WaitingToStart() {
  delete ui;
  delete gameWindow;
}

void WaitingToStart::passPlayerModel(PlayerModel* playerIn) {
  player = playerIn;
}

void WaitingToStart::disconnect() {
  NPTerminateMe npTerminate;
  npTerminate.setUID(player->getUID());
  emit this->terminateMe(npTerminate);
  handler->disconnectFromHost();
  this->accept();
}

void WaitingToStart::playGame() {
  this->hide();
  gameWindow->passHandler(handler);
  gameWindow->exec();
  this->accept();
}

void WaitingToStart::passHandler(GuestNetworkHandler* handlerIn) {
  handler = handlerIn;
  connect(this, &WaitingToStart::terminateMe, handler,
          &GuestNetworkHandler::terminateMe);
}
