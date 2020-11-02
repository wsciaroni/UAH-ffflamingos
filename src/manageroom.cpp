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

void ManageRoom::addPlayer(PlayerModel* player)
{
    std::list<PlayerModel*>::iterator it;
    for (it = playerList.begin(); it != playerList.end(); it++) {
        if (*it == player)
        {
            /// @todo Throw an exception if attempting to add a player twice to the UI
            return;
        }
    }
    playerList.insert(it, player);

    QString name = player->getName();
    list.append(name);
    model.setStringList(list);
}

void ManageRoom::removePlayer(PlayerModel* player)
{
    for (std::list<PlayerModel*>::iterator it = playerList.begin(); it != playerList.end(); it++) {
        if (*it == player)
        {
            playerList.erase(it);
            continue;
        }
    }
    list.removeOne(player->getName());
    model.setStringList(list);
}

void ManageRoom::startGame()
{

}

void ManageRoom::closeLobby()
{

}
