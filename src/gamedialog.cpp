#include "gamedialog.h"
#include "ui_gamedialog.h"

GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDialog)
{
    ui->setupUi(this);
}

GameDialog::~GameDialog()
{
    delete ui;
}

void GameDialog::passHandler(HostNetworkHandler* hostHandlerIn) {
    hostHandler = hostHandlerIn;
}

void GameDialog::passHandler(GuestNetworkHandler* guestHandlerIn) {
    guestHandler = guestHandlerIn;
}

void GameDialog::setRole(bool isHost) {
    isHostRole = isHost;
}

bool GameDialog::isHost() {
    return isHostRole;
}
