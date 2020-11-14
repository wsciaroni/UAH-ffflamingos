#include "manageroom.h"
#include "ui_manageroom.h"

#include <QtDebug>

ManageRoom::ManageRoom(QWidget* parent)
    : QDialog(parent), ui(new Ui::ManageRoom) {
  ui->setupUi(this);

  ui->players->setModel(&model);

  gameWindow = new GameDialog;
  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &ManageRoom::startGame);

  playerList = new PlayerList();
}

ManageRoom::~ManageRoom() {
  delete ui;
  delete gameWindow;
  delete playerList;
}

void ManageRoom::passHost(HostModel* hostPlayer) {
  addPlayer(hostPlayer);

  qDebug() << "Host added to list with name: " << hostPlayer->getName();
}

void ManageRoom::passHandler(HostNetworkHandler* handlerIn) {
  handler = handlerIn;

  connect(handler, &HostNetworkHandler::provideRoomCode, this,
          &ManageRoom::handleProvideRoomCode);
  connect(handler, &HostNetworkHandler::terminateMe, this,
          &ManageRoom::handleTerminateMe);
  connect(this, &ManageRoom::sendRoomCodeStatusToClient, handler,
          &HostNetworkHandler::sendRoomCodeStatus);
  connect(this, &ManageRoom::sendWelcomeToRoomToClient, handler,
          &HostNetworkHandler::sendWelcomeToRoom);
}

void ManageRoom::passHostInfo(QString ip, QString port, QString roomCode) {
    hostRoomCode = roomCode;
    ui->ipLabel->setText(ip);
    ui->portLabel->setText(port);
    ui->codeLabel->setText(roomCode);
}

void ManageRoom::addPlayer(PlayerModel* player) {
  playerList->addPlayer(player);

  QString name = player->getName();
  list.append(name);
  model.setStringList(list);
}

void ManageRoom::removePlayer(PlayerModel* player) {
  list.removeOne(player->getName());
  playerList->removePlayer(player);
  model.setStringList(list);
}

void ManageRoom::startGame() {
  // Set all player positions and tell them to start the game
  playerList->setPositionsAndStartGame(handler);
  NPWelcomeToRoom sendToRoom;

  gameWindow->passHandler(handler);
  this->hide();
  gameWindow->exec();
  closeLobby();
}

void ManageRoom::closeLobby() {
  ///@todo handle the graceful disconnects when the lobby closes
  this->accept();
}

void ManageRoom::handleProvideRoomCode(NPProvideRoomCode provideRoomCodePacket,
                                       QTcpSocket* socket) {
  /// @todo Logic for handling the incoming room code packet
  NPRoomCodeStatus statusPacket;
  static int uidCount = 1;
  if (provideRoomCodePacket.getRoomCode() == hostRoomCode) {
    statusPacket.setRoomCodeStatus(true);
    PlayerModel* newPlayerModel = new PlayerModel(uidCount++, socket);
    newPlayerModel->setName(provideRoomCodePacket.getName());
    addPlayer(newPlayerModel);

  } else
    statusPacket.setRoomCodeStatus(false);
  qDebug() << "in handling room code";
  emit this->sendRoomCodeStatusToClient(statusPacket, socket);
}

void ManageRoom::handleTerminateMe(NPTerminateMe terminateMePacket,
                                   QTcpSocket* socket) {
  qDebug() << "Player id to be removed: " << playerList->getPlayer(socket)
                                                 ->getUID();
  removePlayer(playerList->getPlayer(socket));
}
