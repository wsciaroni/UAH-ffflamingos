#include "connecting.h"
#include "ui_connecting.h"

Connecting::Connecting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connecting)
{
    ui->setupUi(this);
    waitingScreen = new WaitingToStart;
    connect(ui->pushButton,&QPushButton::clicked,this,&Connecting::cancel);
}

Connecting::~Connecting()
{
    delete ui;
    delete waitingScreen;
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
