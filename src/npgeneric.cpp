#include "npgeneric.h"

NPGeneric::NPGeneric() {

}

NPGeneric::~NPGeneric() {

}

PacketType NPGeneric::getPacketType() const {
    return packetType;
}

QDataStream& operator<<(QDataStream& ds, NPGeneric& packet) {
    ds << packet.getPacketType();

    return ds;
}

QDataStream& operator>>(QDataStream& ds, NPGeneric& packet) {
    
    return ds;
}