#include "mocksocket.h"
#include <qdebug.h>

MockSocket::MockSocket(QObject* parent):
    QIODevice(parent)
{
    open(QIODevice::ReadWrite | QIODevice::Unbuffered);
}


qint64 MockSocket::readData(char* data, qint64 maxSize)
{
    qDebug() << "readData";
    int size = (m_buffer.size() > maxSize) ? maxSize : m_buffer.size();
    QByteArray d = m_buffer.remove(0, size);
    qstrncpy(data, d.data(), size);
    return size;
}

qint64 MockSocket::writeData(const char* data, qint64 maxSize)
{
    QByteArray d(data);
//    qDebug("writeData: %s\n", data);
    emit networkOut(data);
    return 1;
}

void MockSocket::networkIn(QByteArray data)
{
    qDebug() << "Incoming data:" << data;
    m_buffer.append(data);
//    emit readyRead();
}





