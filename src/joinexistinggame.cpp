#include "joinexistinggame.h"
#include "ui_joinexistinggame.h"
#include <QIntValidator>

JoinExistingGame::JoinExistingGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinExistingGame)
{
    ui->setupUi(this);

    //missingField = new error;

    this->connectingScreen = new Connecting;
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&JoinExistingGame::attemptToJoin);

    QIntValidator* portValidator = new QIntValidator(1024, 65535, ui->port);
    ui->port->setValidator(portValidator);

    QIntValidator* roomCodeValidator = new QIntValidator(0, 999999, ui->roomCode);
    ui->roomCode->setValidator(roomCodeValidator);
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

void JoinExistingGame::missingFieldError(){
    this->hide();
    missingField = new error;
    missingField->throwErrorMsg("ERROR: Missing required field");
    missingField->exec();
    this->accept();
}

void JoinExistingGame::attemptToJoin(){
    if((ui->ip->text().isEmpty()) || (ui->port->text().isEmpty()) || (ui->roomCode->text().isEmpty())){
        missingFieldError();
    }
    else {
       goToConnecting();
    }
}
