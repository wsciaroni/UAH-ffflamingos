#include "npwelcometoroom.h"


NPWelcomeToRoom::NPWelcomeToRoom(/* args */)
{
}

NPWelcomeToRoom::~NPWelcomeToRoom()
{
}

QDataStream& operator<<(QDataStream& ds, NPWelcomeToRoom& packet) {
    ds << packet.getPacketType();

    return ds;
}

QDataStream& operator>>(QDataStream& ds, NPWelcomeToRoom& packet) {
    
    return ds;
}