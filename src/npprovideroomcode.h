#ifndef NPPROVIDEROOMCODE_H
#define NPPROVIDEROOMCODE_H

#include "npguesttohost.h"

#include <QString>

/**
 * Used to provide the roomcode from the Guest to the Host.
 */
class NPProvideRoomCode : public NPGuestToHost {
 private:
  /**
   * @copydoc NPGuestToHost::packetType
   */
  PacketType packetType = PacketType::PROVIDEROOMCODE;

  QString roomCode;

  QString playerName;

 public:
  NPProvideRoomCode(/* args */);
  ~NPProvideRoomCode();

  /**
   * Used to put the room code into the packet
   * @param roomcode Holds the new value of the room code to be checked with the
   * host
   */
  void setRoomCode(QString roomcode);

  void setName(QString name);

  /**
   * Used to get the room code from the packet
   * @return RoomCode from the packet
   */
  QString getRoomCode();

  QString getName();
};

#endif
