#include "npterminateme.h"


NPTerminateMe::NPTerminateMe(/* args */)
{
}

NPTerminateMe::~NPTerminateMe()
{
}


QDataStream& operator<<(QDataStream& ds, NPTerminateMe& packet) {
    ds << packet.getPacketType();

    return ds;
}

QDataStream& operator>>(QDataStream& ds, NPTerminateMe& packet) {
    
    return ds;
}