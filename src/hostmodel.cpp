#include "hostmodel.h"

HostModel::HostModel(int uid, QTcpServer* server)
    : PlayerModel::PlayerModel(uid) {
  tcpServer = server;
}

HostModel::~HostModel() {}

QTcpServer* HostModel::getTcpServer() { return tcpServer; }