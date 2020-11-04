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

public:
// Constructors / Destructors

    /**
     * Constructor to instantiate a host player
     * @param uid Unique User ID
     * @param socket tcpsocket to communicate with player's machine
     */
    HostModel(int uid, QTcpSocket* socket);

    /**
     * Destructor
     */
    ~HostModel();

    /**
     * @brief getTcpServer
     * @return QTcpServer
     */
    QTcpServer* getTcpServer();

private:
    QTcpServer* tcpServer;

};

#endif // HOSTMODEL_H
