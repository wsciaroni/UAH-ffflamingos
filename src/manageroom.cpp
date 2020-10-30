#include "manageroom.h"
#include "ui_manageroom.h"

ManageRoom::ManageRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageRoom)
{
    ui->setupUi(this);
}

ManageRoom::~ManageRoom()
{
    delete ui;
}
