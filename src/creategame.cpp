#include "creategame.h"
#include "ui_creategame.h"

CreateGame::CreateGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGame)
{
    ui->setupUi(this);
    waitingRoom = new ManageRoom;
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&CreateGame::goToWaitingRoom);
}

CreateGame::~CreateGame()
{
    delete ui;
    delete waitingRoom;
}

void CreateGame::goToWaitingRoom() {
    this->hide();
    waitingRoom->exec();
    this->accept();
}
