#include "npgeneric.h"

NPGeneric::NPGeneric() {}

NPGeneric::~NPGeneric() {}

PacketType NPGeneric::getPacketType() const { return packetType; }

void NPGeneric::setUID(int uidIn) { clientUID = uidIn; }

int NPGeneric::getUID() { return clientUID; }