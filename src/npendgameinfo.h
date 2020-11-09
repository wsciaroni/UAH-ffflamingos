#ifndef NPENDGAMEINFO_H
#define NPENDGAMEINFO_H

#include "nphosttoguest.h"

class NPEndGameInfo : public NPHostToGuest
{
private:
    /* data */
public:
    NPEndGameInfo(/* args */);
    ~NPEndGameInfo();

    /**
     * Reimplements the `<<` operator for QDataStream.
     * This is used to send the data in a specific order
     */
    friend QDataStream& operator >> (QDataStream& ds, const NPEndGameInfo &packet);

    /**
     * Reimplements the `>>` operator for QDataStream.
     * This is used to receive the data in a specific order.
     * @warning Do not attempt to read in the Packet type as that will be done externally to determine what type of packet to read in for the remaining data.
     */
    friend QDataStream& operator << (QDataStream& ds, const NPEndGameInfo &packet);
};

#endif // NPENDGAMEINFO_H