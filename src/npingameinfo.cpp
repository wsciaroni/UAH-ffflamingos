#include "npingameinfo.h"

NPInGameInfo::NPInGameInfo(/* args */)
{
}

NPInGameInfo::~NPInGameInfo()
{
}

QDataStream& operator<<(QDataStream& ds, NPInGameInfo& packet) {
    ds << packet.getPacketType();

    return ds;
}

QDataStream& operator>>(QDataStream& ds, NPInGameInfo& packet) {
    
    return ds;
}