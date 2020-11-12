#ifndef NPHOSTTOGUEST_H
#define NPHOSTTOGUEST_H

#include "npgeneric.h"

/**
 * Used to provide Communication from Host to Guest
 */
class NPHostToGuest : public NPGeneric {
 private:
  /**
   * @copydoc NPGeneric::packetType
   */
  PacketType packetType = PacketType::NULLPACKETTYPE;

 public:
  NPHostToGuest(/* args */);
  ~NPHostToGuest();
};

#endif  // NPHOSTTOGUEST_H