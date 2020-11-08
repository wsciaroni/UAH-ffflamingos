#ifndef HOSTMODEL_H
#define HOSTMODEL_H

#include <QString>
#include <QTcpSocket>
#include <QTimer>
#include <QTcpServer>
#include "playermodel.h"


/**
 * Host-specific version of the PlayerModel Class
 */
class HostModel : public PlayerModel
{
private:
    QTcpServer* tcpServer;

public:
// Constructors / Destructors

    /**
     * Constructor to instantiate a host player
     * @param uid Unique User ID
     * @param server tcpsocket to communicate with players' machines
     */
    HostModel(int uid, QTcpServer* server);

    /**
     * Destructor
     */
    ~HostModel();

    /**
     * @brief getTcpServer
     * @return QTcpServer
     */
    QTcpServer* getTcpServer();

};

#endif // HOSTMODEL_H
