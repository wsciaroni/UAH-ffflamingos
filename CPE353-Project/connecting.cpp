#include "connecting.h"
#include "ui_connecting.h"

Connecting::Connecting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connecting)
{
    ui->setupUi(this);
}

Connecting::~Connecting()
{
    delete ui;
}
