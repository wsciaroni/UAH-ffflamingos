#include "joinexistinggame.h"
#include "ui_joinexistinggame.h"

JoinExistingGame::JoinExistingGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinExistingGame)
{
    ui->setupUi(this);
}

JoinExistingGame::~JoinExistingGame()
{
    delete ui;
}
