#include "waitingtostart.h"
#include "ui_waitingtostart.h"

WaitingToStart::WaitingToStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingToStart)
{
    ui->setupUi(this);

    connect(ui->disconnect,SIGNAL(clicked(bool)),this,SLOT(disconnect()));
}

WaitingToStart::~WaitingToStart()
{
    delete ui;
}


void WaitingToStart::disconnect()
{

}
