#include "creategame.h"
#include "ui_creategame.h"
#include <QIntValidator>
#include <QNetworkInterface>
#include <QAbstractSocket>
//#include <QUdpSocket>

CreateGame::CreateGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGame)
{
    ui->setupUi(this);
    waitingRoom = new ManageRoom;
    bindError = new error;
    //connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&CreateGame::goToWaitingRoom);
    connect(ui->buttonBox,&QDialogButtonBox::accepted, this,&CreateGame::bindIP_Port);

    QIntValidator* intValidator1 = new QIntValidator(ui->port);
    ui->port->setValidator(intValidator1);

    // gets list of all network interfaces
    QList <QHostAddress> addressList = QNetworkInterface::allAddresses();
    // adds list of addresses to dropdown menu
    for(int i = 0; i < addressList.size();i++)
    {
        if(QAbstractSocket::IPv4Protocol == addressList[i].protocol())
            ui->ipDropdown->addItem(addressList[i].toString());
    }
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

void CreateGame::throwBindError(){
    this->hide();
    bindError->exec();
    this->accept();
}

void CreateGame::bindIP_Port(){
    QHostAddress IP(ui->ipDropdown->currentText());
    myUDPSocket = new QUdpSocket(this);
    if(myUDPSocket->bind(IP,(ui->port->text()).toUShort()))
    {
        if(ui->port->text().length() > 0 || ui->roomCode->text().length() > 0)
            goToWaitingRoom();
    }
    else{
        throwBindError();
    }

}
