#include "npendgameinfo.h"

NPEndGameInfo::NPEndGameInfo(/* args */)
{
}

NPEndGameInfo::~NPEndGameInfo()
{
}

QDataStream& operator<<(QDataStream& ds, const NPEndGameInfo &packet) {
    PacketType pType = packet.getPacketType();
    ds << pType;

    return ds;
}

QDataStream& operator>>(QDataStream& ds, NPEndGameInfo &packet) {
    
    return ds;
}