#include "nphosttoguest.h"

NPHostToGuest::NPHostToGuest(/* args */)
{
}

NPHostToGuest::~NPHostToGuest()
{
}

QDataStream& operator<<(QDataStream& ds, NPHostToGuest& packet) {
    ds << packet.getPacketType();

    return ds;
}

QDataStream& operator>>(QDataStream& ds, NPHostToGuest& packet) {
    
    return ds;
}