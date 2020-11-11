#include "connecting.h"

Connecting::Connecting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connecting)
{
    ui->setupUi(this);
    waitingScreen = new WaitingToStart;
    connect(ui->pushButton,&QPushButton::clicked,this,&Connecting::cancel);

    handler = new GuestNetworkHandler;
}

Connecting::~Connecting()
{
    delete ui;
    delete waitingScreen;
    delete handler;
}

void Connecting::passName(QString name) {
    playerName = name;
}

void Connecting::passInfo(QString ipIn, QString portIn, QString roomCodeIn) {
    ip = ipIn;
    port = portIn;
    roomCode = roomCodeIn;
    
    handler->disconnectFromHost();
    
    if (handler->connectToHost(QHostAddress(ipIn), portIn))
    {
        // Send a provideRoomCodePacket
        qDebug() << "Connection successful on Client\n";
        NPProvideRoomCode npProvideRoomCode;
        npProvideRoomCode.setRoomCode(roomCode);
        handler->provideRoomCode(npProvideRoomCode);
    } else
    {
        qDebug() << "Unable to connect\n";
        // Throw an error
        
    }
    
    
}

void Connecting::goToWaitingScreen() {
    this->hide();
    waitingScreen->exec();
    this->accept();
}

void Connecting::cancel() {
    ///@todo disconnect the network here, maybe even send a message saying that you want to disconnect
    this->accept();
}
