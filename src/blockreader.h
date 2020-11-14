#ifndef BLOCKREADER_H
#define BLOCKREADER_H

#include <QDataStream>
#include <QBuffer>

/**
 * @brief Used to provide a stream for io over a QTcpSocket
 * @details Uses a Blocking Read to wait for all the information to arrive over
 * the QTcpSocket and allows that to be accessed as a stream
 */
class BlockReader {
 public:
  /**
   * @brief Initializes a BlockReader on the specified IO device. In our case,
   * we are using a QTcpSocket as our IO device.
   * @param io The QTcpSocket to read from
   */
  BlockReader(QIODevice* io) {
    buffer.open(QIODevice::ReadWrite);
    _stream.setVersion(QDataStream::Qt_4_8);
    _stream.setDevice(&buffer);

    quint64 blockSize;

    // Read the size.
    readMax(io, sizeof(blockSize));
    buffer.seek(0);
    _stream >> blockSize;

    // Read the rest of the data.
    readMax(io, blockSize);
    buffer.seek(sizeof(blockSize));
  }

  /**
   * Used to operate with the stream.
   * @return The QDataStream to work with
   */
  QDataStream& stream() { return _stream; }

 private:
  /**
   * Performs a blocking read on the io device.
   * Blocking reads data from socket until buffer size becomes exactly n. No
   * additional data is read from the socket.
   * @warning This can lock in an infinite loop if you do not read the correct
   * amount of data.
   */
  void readMax(QIODevice* io, int n) {
    while (buffer.size() < n) {
      if (!io->bytesAvailable()) {
        io->waitForReadyRead(30000);
      }
      buffer.write(io->read(n - buffer.size()));
    }
  }

  /// Used to hold the info while the reading is taking place
  QBuffer buffer;

  /// The QDataStream that is operated with and returned by BlockReader::stream.
  QDataStream _stream;
};

#endif  // BLOCKREADER_H