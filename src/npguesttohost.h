#ifndef NPGUESTTOHOST_H
#define NPGUESTTOHOST_H

#include "npgeneric.h"

/**
 * Used for network traffic passed from a Guest to the Host
 */
class NPGuestToHost : public NPGeneric {
 private:
  /**
   * @copydoc NPGeneric::packetType
   */
  PacketType packetType = PacketType::NULLPACKETTYPE;

 public:
  NPGuestToHost();
  ~NPGuestToHost();
};

#endif  // NPGUESTTOHOST_H