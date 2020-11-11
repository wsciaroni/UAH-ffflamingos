#ifndef DATASTREAMENUM_H
#define DATASTREAMENUM_H

#include <type_traits>
#include <QDataStream>

//a function that can serialize any enum into QDataStream
//it stores the enum in a qint64
template<typename Enum,
         typename = typename std::enable_if<std::is_enum<Enum>::value>::type>
QDataStream& operator<<(QDataStream& stream, const Enum& e) {
    stream << static_cast<qint64>(e);
    return stream;
}

//a function that can deserialize any enum from QDataStream
//it reads the enum as if it was stored in qint64
template<typename Enum,
         typename = typename std::enable_if<std::is_enum<Enum>::value>::type>
QDataStream& operator>>(QDataStream& stream, Enum& e) {
    qint64 v;
    stream >> v;
    e = static_cast<Enum>(v);
    return stream;
}


#endif // DATASTREAM_ENUM_H