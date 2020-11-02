#include "manageroom.h"
#include "ui_manageroom.h"

ManageRoom::ManageRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageRoom)
{
    ui->setupUi(this);

    ui->players->setModel(&model);

    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&ManageRoom::startGame);
    connect(ui->buttonBox,&QDialogButtonBox::rejected,this,&ManageRoom::closeLobby);
}

ManageRoom::~ManageRoom()
{
    delete ui;
}

void ManageRoom::addPlayer(QString name)
{
    list.append(name);
    model.setStringList(list);
}

void ManageRoom::removePlayer(QString name)
{
    list.removeOne(name);
    model.setStringList(list);
}

void ManageRoom::startGame()
{

}

void ManageRoom::closeLobby()
{

}
