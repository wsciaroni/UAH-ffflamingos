#include "connecting.h"

Connecting::Connecting(QWidget* parent)
    : QDialog(parent), ui(new Ui::Connecting) {
  ui->setupUi(this);
  waitingScreen = new WaitingToStart;
  connect(ui->pushButton, &QPushButton::clicked, this, &Connecting::cancel);

  handler = new GuestNetworkHandler;

  connect(handler, &GuestNetworkHandler::recvRoomCodeStatus, this,
          &Connecting::handleRoomCodeStatus);
}

Connecting::~Connecting() {
  delete ui;
  delete waitingScreen;
  delete handler;
  delete player;
}

void Connecting::passName(QString name) { playerName = name; }

bool Connecting::passInfo(QString ipIn, QString portIn, QString roomCodeIn) {
  ip = ipIn;
  port = portIn;
  roomCode = roomCodeIn;

  handler->disconnectFromHost();

  if (handler->connectToHost(QHostAddress(ipIn), portIn)) {
    // Send a provideRoomCodePacket
    qDebug() << "Connection successful on Client\n";
    NPProvideRoomCode npProvideRoomCode;
    npProvideRoomCode.setRoomCode(roomCode);
    npProvideRoomCode.setName(playerName);
    handler->provideRoomCode(npProvideRoomCode);
    return 1;
  } else {
    throwError = new error;
    throwError->throwErrorMsg("ERROR: Unable to connect");
    throwError->exec();
    delete throwError;
    this->cancel();
    return 0;
  }
}

void Connecting::goToWaitingScreen() {
  this->hide();
  waitingScreen->passHandler(handler);
  waitingScreen->passPlayerModel(player);
  waitingScreen->exec();
  this->accept();
}

void Connecting::cancel() {
  ///@todo disconnect the network here, maybe even send a message saying that
  /// you want to disconnect
  this->accept();
}

void Connecting::handleRoomCodeStatus(NPRoomCodeStatus roomCodeStatus) {
  if (roomCodeStatus.getRoomCodeStatus() == true) {
    player = new PlayerModel(roomCodeStatus.getUID());
    goToWaitingScreen();
  } else {
    error* throwError = new error;
    throwError->throwErrorMsg("ERROR: Invalid Room Code");
    throwError->exec();
    delete throwError;
    this->cancel();
  }
}
