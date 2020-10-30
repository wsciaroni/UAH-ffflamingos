#include "waitingtostart.h"
#include "ui_waitingtostart.h"

WaitingToStart::WaitingToStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingToStart)
{
    ui->setupUi(this);
}

WaitingToStart::~WaitingToStart()
{
    delete ui;
}
