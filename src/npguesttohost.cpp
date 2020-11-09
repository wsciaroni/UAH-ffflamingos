#include "npguesttohost.h"

NPGuestToHost::NPGuestToHost()
{
}

NPGuestToHost::~NPGuestToHost()
{
}

void NPGuestToHost::setUID(int uidIN) {
    uid = uidIN;
}

int NPGuestToHost::getUID() {
    return uid;
}

QDataStream& operator<<(QDataStream& ds, NPGuestToHost& packet) {
    ds << packet.getPacketType();

    return ds;
}

QDataStream& operator>>(QDataStream& ds, NPGuestToHost& packet) {
    
    return ds;
}