#ifndef NPGENERIC_H
#define NPGENERIC_H

#include <QDataStream>
#include <QString>
#include "datastreamenum.h"

/**
 * @brief Packet Type Enumeration
 * @details Used to determine what type of network packet the info is.  Allows for a packet's role to be determined
 */
enum class PacketType : qint32 {
    NULLPACKETTYPE = 0,               ///< Should never occur
    
    PROVIDEROOMCODE = 1,    ///< Guest->Host Providing Room Code
    ROOMCODESTATUS = 2,     ///< Host->Guest Letting them know if the room code was correct
    WELCOMETOROOM = 3,      ///< Host->Guest Letting them know their UID and Position etc

    TERMINATEME = 666,      ///< Guest->Host Asking to quit out of the lobby or game

    SPACEPRESSED = 1000,    ///< Guest->Host Letting Host Know EVERY time space is pressed
    INGAMEINFO = 1001,      ///< Host->Guest Providing Ball location, all player animation status,

    ENDGAMEINFO = 9999      ///< Host->Guest Providing All player scores, the high score, Winner, etc
};

/**
 * @brief Generic Network Packet
 * @details Used to be passed from host->guest or guest->host providing the necessary information
 */
class NPGeneric
{
private:
    /**
     * Used to determine the role of the packet and how it will be handled (As well as the intended recipients)
     */
    PacketType packetType = PacketType::NULLPACKETTYPE;

    /**
     * User ID of the Client
     */
    int clientUID = -1;

public:
    NPGeneric();
    ~NPGeneric();

    /**
     * Used to get what type of packet you're dealing with
     * @return the PacketType of the packet
     */
    PacketType getPacketType() const;

    /**
     * Used to set the UID of the client
     * @param uidIn The UID of the client
     */
    void setUID(int uidIn);

    /**
     * Used to get the UID of the client
     * @return UID of the client
     */
    int getUID();
};

#endif // NPGENERIC_H
