#ifndef BLOCKWRITER_H
#define BLOCKWRITER_H

#include <QDataStream>
#include <QBuffer>

/**
 * @brief Used to provide a stream for io over a QTcpSocket
 */
class BlockWriter {
 public:
  /**
   * @brief Initializes a BlockWriter on the specified IO device. In our case,
   * we are using a QTcpSocket as our IO device.
   * @param io The QTcpSocket to Write to
   */
  BlockWriter(QIODevice *io) {
    buffer.open(QIODevice::WriteOnly);
    this->io = io;
    _stream.setVersion(QDataStream::Qt_4_8);
    _stream.setDevice(&buffer);

    // Placeholder for the size. We will get the value
    // at the end.
    _stream << quint64(0);
  }

  /**
   * Destructor.
   * Writes the buffer back to the io Device.
   */
  ~BlockWriter() {
    // Write the real size.
    _stream.device()->seek(0);
    _stream << (quint64)buffer.size();

    // Flush to the device.
    io->write(buffer.buffer());
  }

  /**
   * Used to operate with the stream.
   * @return The QDataStream to work with
   */
  QDataStream &stream() { return _stream; }

 private:
  /// Used to hold the info while the writing is taking place
  QBuffer buffer;

  /// The QDataStream that is operated with and returned by BlockReader::stream.
  QDataStream _stream;

  /// The io device that is operated with
  QIODevice *io;
};

#endif  // BLOCKWRITER_H