#include "creategame.h"

CreateGame::CreateGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGame)
{
    ui->setupUi(this);
    waitingRoom = new ManageRoom;

    handler = new HostNetworkHandler;

    connect(ui->buttonBox,&QDialogButtonBox::accepted, this,&CreateGame::bindIP_Port);

    QIntValidator* portValidator = new QIntValidator(1024, 65535, ui->port);
    ui->port->setValidator(portValidator);

    QIntValidator* roomCodeValidator = new QIntValidator(0, 999999, ui->roomCode);
    ui->roomCode->setValidator(roomCodeValidator);

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
    delete hostPlayer;
    delete handler;
}

void CreateGame::passName(QString name) {
    playerName = name;
}

void CreateGame::goToWaitingRoom() {
    this->hide();
    this->createHost();
    hostPlayer->setName(playerName);
    waitingRoom->passHost(hostPlayer);
    waitingRoom->exec();
    
    this->accept();
}

void CreateGame::throwBindError(){
    this->hide();
    bindError = new error;
    bindError->throwErrorMsg("ERROR: Could not bind IP and Port");
    bindError->exec();
    delete bindError;
    this->accept();
}

void CreateGame::createHost() {
    hostPlayer = new HostModel(0, handler->getTCPServer());
}

void CreateGame::bindIP_Port(){
    QHostAddress IP(ui->ipDropdown->currentText());
    
    if(handler->startTCPServer(IP,(ui->port->text()).toUShort()))
    {
        if(!(ui->port->text().isEmpty()) && !(ui->roomCode->text().isEmpty())) {
            goToWaitingRoom();
        }
        else
        {
            handler->stopTCPServer();
        }
    }
    else
        throwBindError();
}
