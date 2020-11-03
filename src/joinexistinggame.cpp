#include "joinexistinggame.h"
#include "ui_joinexistinggame.h"

JoinExistingGame::JoinExistingGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinExistingGame)
{
    ui->setupUi(this);

    this->connectingScreen = new Connecting;
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&JoinExistingGame::goToConnecting);
}

JoinExistingGame::~JoinExistingGame()
{
    delete ui;
    delete connectingScreen;
}

void JoinExistingGame::goToConnecting() {
    this->hide();
    connectingScreen->exec();
    this->accept();
}