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

  connect(handlerIn, &HostNetworkHandler::provideRoomCode, this,
          &ManageRoom::handleProvideRoomCode);
  connect(this, &ManageRoom::sendRoomCodeStatusToClient, handlerIn,
          &HostNetworkHandler::sendRoomCodeStatus);
  connect(this, &ManageRoom::sendWelcomeToRoomToClient, handlerIn,
          &HostNetworkHandler::sendWelcomeToRoom);
}

void ManageRoom::passRoomCode(QString roomCode) { hostRoomCode = roomCode; }

void ManageRoom::addPlayer(PlayerModel* player) {
  playerList->addPlayer(player);

  QString name = player->getName();
  list.append(name);
  model.setStringList(list);
}

void ManageRoom::removePlayer(PlayerModel* player) {
  playerList->removePlayer(player);
  list.removeOne(player->getName());
  model.setStringList(list);
}

void ManageRoom::startGame() {
  this->hide();
  gameWindow->passHandler(handler);
  gameWindow->exec();

  // Tell all lobby players to go to game

  // Set all player positions
    NPWelcomeToRoom sendToRoom;

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
