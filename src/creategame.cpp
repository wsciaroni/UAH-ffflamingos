#include "creategame.h"
#include "ui_creategame.h"

CreateGame::CreateGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGame)
{
    ui->setupUi(this);
}

CreateGame::~CreateGame()
{
    delete ui;
}
