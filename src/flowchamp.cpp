#include "flowchamp.h"

FlowChamp::FlowChamp(int& argc, char** argv) : QApplication(argc, argv) {
  connect(dialogDR, &DetermineRoleDialog::DRPlayAsHost, this,
          &FlowChamp::DRPlayAsHost);
  connect(dialogDR, &DetermineRoleDialog::DRPlayAsGuest, this,
          &FlowChamp::DRPlayAsGuest);
  connect(dialogDR, &DetermineRoleDialog::DRQuitGame, this,
          &FlowChamp::DRQuitGame);
  dialogDR->show();

  connect(dialogCG, &CreateGame::CGGoToManageRoom, this,
          &FlowChamp::CGGoToManageRoom);
  connect(dialogCG, &CreateGame::CGQuitGame, this, &FlowChamp::CGQuitGame);

  connect(dialogMR, &ManageRoom::MRStartGameForAll, this,
          &FlowChamp::MRStartGameForAll);
  connect(dialogMR, &ManageRoom::MRQuitGame, this, &FlowChamp::MRQuitGame);
  connect(this, &FlowChamp::MRUpdatePlayerList, dialogMR,
          &ManageRoom::MRUpdatePlayerList);
  connect(this, &FlowChamp::MRPassHostInfo, dialogMR,
          &ManageRoom::MRPassHostInfo);

  connect(dialogJG, &JoinExistingGame::JGGoToWaitingToStart, this,
          &FlowChamp::JGGoToWaitingToStart);
  connect(dialogJG, &JoinExistingGame::JGQuitGame, this,
          &FlowChamp::JGQuitGame);

  connect(dialogWS, &WaitingToStart::WSQuitGame, this, &FlowChamp::WSQuitGame);

  connect(dialogGD, &GameDialog::GDSpacePressed, this,
          &FlowChamp::GDSpacePressed);
  connect(dialogGD, &GameDialog::GDEscPressed, this, &FlowChamp::GDEscPressed);
  connect(dialogGD, &GameDialog::GDQuitGame, this, &FlowChamp::GDQuitGame);

  // Networking Connects
  // Guest Connections
  connect(guestHandler, &GuestNetworkHandler::recvRoomCodeStatus, this,
          &FlowChamp::guestHandleRoomCodeStatus);
  connect(guestHandler, &GuestNetworkHandler::recvWelcomeToRoom, this,
          &FlowChamp::guestHandleWelcomeToRoom);
  connect(guestHandler, &GuestNetworkHandler::recvInGameInfo, this,
          &FlowChamp::guestHandleInGameInfo);
  connect(guestHandler, &GuestNetworkHandler::recvEndGameInfo, this,
          &FlowChamp::guestHandleEndGameInfo);
  connect(guestHandler, &GuestNetworkHandler::tcpConnectionDropped, this,
          &FlowChamp::guestHandleTCPDropOut);
  connect(this, &FlowChamp::guestSendRoomCode, guestHandler,
          &GuestNetworkHandler::provideRoomCode);
  connect(this, &FlowChamp::guestSendTerminateMe, guestHandler,
          &GuestNetworkHandler::terminateMe);
  connect(this, &FlowChamp::guestSendSpacePressed, guestHandler,
          &GuestNetworkHandler::spacePressed);
  // Host Connections
  connect(hostHandler, &HostNetworkHandler::provideRoomCode, this,
          &FlowChamp::hostHandleRoomCode);
  connect(hostHandler, &HostNetworkHandler::terminateMe, this,
          &FlowChamp::hostHandleTerminateMe);
  connect(hostHandler, &HostNetworkHandler::spacePressed, this,
          &FlowChamp::hostHandleSpacePressed);
  connect(hostHandler, &HostNetworkHandler::hostHandleGuestTerminated, this,
          &FlowChamp::hostHandleGuestTerminated);
  connect(this, &FlowChamp::hostSendRoomCodeStatus, hostHandler,
          &HostNetworkHandler::sendRoomCodeStatus);
  connect(this, &FlowChamp::hostSendWelcomeToRoom, hostHandler,
          &HostNetworkHandler::sendWelcomeToRoom);
  connect(this, &FlowChamp::hostSendInGameInfo, hostHandler,
          &HostNetworkHandler::sendInGameInfo);
  connect(this, &FlowChamp::hostSendEndGameInfo, hostHandler,
          &HostNetworkHandler::sendEndGameInfo);

  connect(sendInGameInfoTimer, &QTimer::timeout, this,
          QOverload<>::of(&FlowChamp::prepareAndSendInGameInfo));
}

FlowChamp::~FlowChamp() {
  delete dialogCG;
  delete dialogDR;
  delete dialogGD;
  delete dialogJG;
  delete dialogMR;
  delete dialogWS;

  delete hostHandler;
  delete guestHandler;
}

bool FlowChamp::isHost() { return isHostPlayer; }

void FlowChamp::setRole(bool isPlayerHost) { isHostPlayer = isPlayerHost; }

void FlowChamp::addPlayer(PlayerModel* player) {
  if (!player) {
    return;
  }
  playerList.addPlayer(player);
  playerNames.append(player->getName());
  emit this->MRUpdatePlayerList(playerNames);
}
void FlowChamp::removePlayer(PlayerModel* player) {
  if (!player) {
    return;
  }
  playerNames.removeOne(player->getName());
  playerList.removePlayer(player);
  emit this->MRUpdatePlayerList(playerNames);
}

void FlowChamp::makePlayerLunge(PlayerModel* player) {
  if (!player) {
    return;
  }

  if (player->spacePressed()) {
    /// @todo Then space was allowed to be pressed so make the animation happen
    /// and check to see if they got any points
  }
}

void FlowChamp::startSendInGameInfo() {
  if (!sendInGameInfoTimer) {
    return;
  }
  sendInGameInfoTimer->start(10);
}

void FlowChamp::stopSendInGameInfo() {
  if (!sendInGameInfoTimer) {
    return;
  }
  sendInGameInfoTimer->stop();
}

void FlowChamp::DRPlayAsHost(QString playerNameIn) {
  qDebug() << "In DRPlayAsHost()";
  playerName = playerNameIn;
  setRole(true);
  HostModel* hostPlayer = new HostModel(1, hostHandler->getTCPServer());
  hostPlayer->setPositionId(static_cast<PlayerPosition>(1));
  playerList.addPlayer(hostPlayer);
  dialogDR->hide();
  dialogCG->show();
}

void FlowChamp::DRPlayAsGuest(QString playerNameIn) {
  setRole(false);
  qDebug() << "In DRPlayAsGuest()";
  playerName = playerNameIn;
  dialogDR->hide();
  dialogJG->show();
}

void FlowChamp::DRQuitGame() {
  qDebug() << "In DRQuitGame()";
  dialogDR->accept();
}

void FlowChamp::CGGoToManageRoom(QHostAddress addressIn, QString portIn,
                                 QString roomCodeIn) {
  qDebug() << "In CGGoToManageRoom()";
  if (!hostHandler) {
    return;
  }

  if (hostHandler->startTCPServer(addressIn, portIn.toUShort())) {
    // Success
    QStringList newList;
    newList.append(playerName);
    hostRoomCode = roomCodeIn;
    playerNames = newList;
    emit this->MRUpdatePlayerList(newList);
    emit this->MRPassHostInfo(addressIn.toString(), portIn, roomCodeIn);
    dialogCG->hide();
    dialogMR->show();
  } else {
    error networkError;
    QString errorMessage = "Error setting up QTcpServer: " +
                           hostHandler->getTCPServer()->errorString();
    networkError.throwErrorMsg(errorMessage);
    dialogCG->hide();
    networkError.exec();
    dialogDR->show();
  }
}

void FlowChamp::CGQuitGame() {
  qDebug() << "In CGQuitGame()";
  dialogCG->hide();
  dialogDR->show();
}

void FlowChamp::MRStartGameForAll() {
  qDebug() << "In MRStartGameForAll()";
  NPWelcomeToRoom packet;
  // for (PlayerModel* temp : playerList.keys()) {
  playerList.getPlayer(1)->enableTimers();
  for (int i = 1; i <= playerList.getMaxUID(); i++) {
    PlayerModel* temp = playerList.getPlayer(i);
    if (temp && temp->getUID() > 0 && temp->getTCPSocket()) {
      temp->enableTimers();
      emit this->hostSendWelcomeToRoom(packet, temp->getTCPSocket());
    }
  }
  dialogMR->hide();
  dialogGD->drawBoard();

  // Spawn each player
  for (int i = 1; i <= playerList.getMaxUID(); i++) {
    dialogGD->spawnPlayer(i);
  }
  dialogGD->show();
  startSendInGameInfo();
}

void FlowChamp::MRQuitGame() {
  qDebug() << "In MRQuitGame()";
  stopSendInGameInfo();
  hostHandler->stopTCPServer();
  dialogMR->hide();
  dialogDR->show();
}

void FlowChamp::JGGoToWaitingToStart(QHostAddress addressIn, QString portIn,
                                     QString roomCodeIn) {
  qDebug() << "In JGGoToWaitingToStart()";
  if (!guestHandler) {
    return;
  }

  if (guestHandler->connectToHost(addressIn, portIn)) {
    NPProvideRoomCode packet;
    packet.setRoomCode(roomCodeIn);
    packet.setName(playerName);
    emit this->guestSendRoomCode(packet);
    dialogJG->hide();
  } else {
    /// @todo say what went wrong when joining game
    error networkError;
    QString errorMessage = "Error connecting to Host: " +
                           guestHandler->getTcpSocket()->errorString();
    networkError.throwErrorMsg(errorMessage);
    dialogJG->hide();
    networkError.exec();
    dialogDR->show();
  }
}

void FlowChamp::JGQuitGame() {
  qDebug() << "In JGQuitGame()";
  dialogJG->hide();
  dialogDR->show();
}

void FlowChamp::WSStartClientGame() {
  qDebug() << "In WSStartClientGame()";
  dialogWS->hide();
  dialogGD->show();
  if (!guestHandler->listenOnUDP()) {
    error networkError;
    QString errorMessage =
        "Error Listening for QUdpSocket on Multicast Port: " +
        guestHandler->getUdpSocket()->errorString();
    networkError.throwErrorMsg(errorMessage);
    dialogCG->hide();
    networkError.exec();
    dialogDR->show();
  }
}

void FlowChamp::WSQuitGame() {
  qDebug() << "In WSQuitGame()";
  if (!guestHandler) {
    return;
  }

  guestHandler->disconnectFromHost();
  dialogWS->hide();
  dialogDR->show();
}

void FlowChamp::GDSpacePressed() {
  qDebug() << "In GDSpacePressed()";
  if (this->isHost()) {
    qDebug() << "GDSpacePressedLocal is Host";
    makePlayerLunge(
        playerList.getPlayer(1));  // Call this on the host player with UID == 1
  } else {
    qDebug() << "GDSpacePressedLocal is Guest";
    NPSpacePressed packet;
    packet.setUID(0);
    emit this->guestSendSpacePressed(packet);
  }
}

void FlowChamp::GDEscPressed() {
  qDebug() << "In GDEscPressed()";
  emit GDQuitGame();
}

void FlowChamp::GDQuitGame() {
  qDebug() << "In GDQuitGame()";
  if (isHost()) {
    hostHandler->stopTCPServer();
  } else {
    guestHandler->stopListeningOnUDP();
    guestHandler->disconnectFromHost();
  }
  dialogGD->hide();
  dialogDR->show();
}

// Guest to Host
void FlowChamp::hostHandleRoomCode(NPProvideRoomCode packet,
                                   QTcpSocket* socket) {
  NPRoomCodeStatus statusPacket;
  int newPlayerID = playerList.getNewPlayerID();
  if (packet.getRoomCode() == hostRoomCode && newPlayerID != -1) {
    statusPacket.setRoomCodeStatus(true);
    PlayerModel* newPlayer = new PlayerModel(newPlayerID, socket);
    newPlayer->setName(packet.getName());
    newPlayer->setPositionId(static_cast<PlayerPosition>(newPlayerID));
    addPlayer(newPlayer);
  } else {
    statusPacket.setRoomCodeStatus(false);
  }
  emit this->hostSendRoomCodeStatus(statusPacket, socket);
}

void FlowChamp::hostHandleTerminateMe(NPTerminateMe packet,
                                      QTcpSocket* socket) {
  removePlayer(playerList.getPlayer(socket));
}
void FlowChamp::hostHandleSpacePressed(NPSpacePressed packet,
                                       QTcpSocket* socket) {
  qDebug() << "Host: Space Pressed by "
           << playerList.getPlayer(socket)->getName();
  makePlayerLunge(playerList.getPlayer(socket));
}

void FlowChamp::hostHandleGuestTerminated(QTcpSocket* socket) {
  PlayerModel* tmpPlayer = playerList.getPlayer(socket);
  removePlayer(tmpPlayer);
}

// Host To Guest
void FlowChamp::guestHandleRoomCodeStatus(NPRoomCodeStatus packet) {
  if (packet.getRoomCodeStatus() == true) {
    PlayerModel* player = new PlayerModel(packet.getUID());
    playerList.addPlayer(player);
    dialogWS->show();
  } else {
    /// @todo throw an error if the room code is invalid
    error* throwError = new error;
    throwError->throwErrorMsg("ERROR: Invalid Room Code or the Room is Full");
    throwError->exec();
    delete throwError;
    JGQuitGame();
  }
}

void FlowChamp::guestHandleWelcomeToRoom(NPWelcomeToRoom packet) {
  WSStartClientGame();
}

void FlowChamp::guestHandleInGameInfo(NPInGameInfo packet) {
  /// @note ball ranges from 0-24 while player ranges from 1-5 in UID.
  /// 0 Represents the High Score.
  qint32 xPos[25];
  qint32 yPos[25];

  for (int i = 0; i < 25; i++) {
    xPos[i] = packet.getBallPosX(i);
    yPos[i] = packet.getBallPosY(i);
  }

  bool playerExtensions[6];
  playerExtensions[0] =
      0;  // There is no player 0, that is the high score slot.
  qint32 scores[6];
  for (int i = 0; i < 6; i++) {
    playerExtensions[i] = packet.isPlayerExtended(i);
    scores[i] = packet.getPlayerScore(i);
  }
  /// @todo make animation of players based off the playerExtensions array.
  /// @todo make the current scores based off the scores array.
  /// @todo make the balls appear at the place of the xPos and yPos arrays.
}

void FlowChamp::guestHandleEndGameInfo(NPEndGameInfo packet) {
  /// @todo Handle all the end of game info stuff
}
void FlowChamp::guestHandleTCPDropOut() {
  dialogCG->hide();
  dialogDR->hide();
  dialogGD->hide();
  dialogJG->hide();
  dialogMR->hide();
  dialogWS->hide();

  dialogDR->show();
}

void FlowChamp::prepareAndSendInGameInfo() {
  NPInGameInfo packet;
  for (int i = 0; i < 25; i++) {
    packet.setBallPosition(i, 0, 0);
  }

  for (int i = 0; i < 6; i++) {
    packet.setPlayerExtension(i, false);
    packet.setPlayerScore(i, qint32(1000));
  }

  emit this->hostSendInGameInfo(packet, multicastAddress);
}
