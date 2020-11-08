#ifndef NETWORKCONFIGURATOR_H
#define NETWORKCONFIGURATOR_H

#include "hostmodel.h"
#include "playermodel.h"
#include "npgeneric.h"

#include  <QNetworkConfiguration>

/**
 * Used to make the network connections and handle any network related errors
 */
class NetworkConfigurator
{
public:
    NetworkConfigurator();
    ~NetworkConfigurator();
    void processNetworkPackets();

};

#endif // NETWORKCONFIGURATOR_H
