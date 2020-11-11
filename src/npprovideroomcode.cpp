#include "npprovideroomcode.h"
#include <QDebug>

NPProvideRoomCode::NPProvideRoomCode(/* args */)
{
}

NPProvideRoomCode::~NPProvideRoomCode()
{
}

void NPProvideRoomCode::setRoomCode(QString roomcode) {
    roomCode = roomcode;
}

QString NPProvideRoomCode::getRoomCode() {
    return roomCode;
}

QDataStream& operator<<(QDataStream& ds, NPProvideRoomCode& packet) {
    ds << PacketType::PROVIDEROOMCODE;
    QString test("Hello my friend");
    ds << test;
    return ds;
}

QDataStream& operator>>(QDataStream& ds, NPProvideRoomCode& packet) {
    QString test;
    ds >> test;
    qDebug() << "Received " << test << "\n";
    return ds;
}