#include "waitingtostart.h"
#include "ui_waitingtostart.h"

WaitingToStart::WaitingToStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingToStart)
{
    ui->setupUi(this);
    gameWindow = new GameDialog;
    connect(ui->disconnect,&QPushButton::clicked,this,&WaitingToStart::disconnect);
}

WaitingToStart::~WaitingToStart()
{
    delete ui;
    delete gameWindow;
}


void WaitingToStart::disconnect()
{
    /// @todo Handle a graceful disconnect here
    this->accept();
}

void WaitingToStart::playGame() {
    this->hide();
    gameWindow->exec();
    this->accept();
}
