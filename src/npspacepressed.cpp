#include "npspacepressed.h"

NPSpacePressed::NPSpacePressed(/* args */)
{
}

NPSpacePressed::~NPSpacePressed()
{
}

QDataStream& operator<<(QDataStream& ds, NPSpacePressed& packet) {
    ds << packet.getPacketType();

    return ds;
}

QDataStream& operator>>(QDataStream& ds, NPSpacePressed& packet) {
    
    return ds;
}