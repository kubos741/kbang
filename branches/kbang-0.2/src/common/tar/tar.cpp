/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
 *   echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil"                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "tar.h"

#include <cstdlib>
#include <QtDebug>

TarStream::TarStream():
        QObject(0),
        mp_device(0),
        m_mode(InvalidMode),
        m_fileSizeLeft(0)
{
    m_block.resize(BLOCK_SIZE);
}

/* virtual */
TarStream::~TarStream()
{
}

void TarStream::open(QDir dir, QIODevice* device, Mode mode)
{
    m_dir = dir;
    mp_device = device;
    m_mode = mode;
    m_nextBlockType = FileHeaderBlock;
    if (mode == UntarMode) {
        connect(mp_device, SIGNAL(readyRead()),
                this, SLOT(readBlock()));
        readBlock();
    }
}


/* private slot */
void TarStream::readBlock()
{
    while (mp_device->bytesAvailable() >= BLOCK_SIZE) {
        m_block = mp_device->read(BLOCK_SIZE);
        switch (m_nextBlockType) {
        case FileHeaderBlock:
            if (isNullBlock()) {
                m_nextBlockType = TrailingBlock;
            } else {
                writeNextFile();
            }
            break;
        case DataBlock:
            writeFileData();
            break;
        case TrailingBlock:
            if (isNullBlock()) {
                mp_device->close();
                return;
            } else {
                writeNextFile();
            }
            break;
        default:
            break;
        }
    }
}


void TarStream::writeNextFile()
{
    QString file_name = readFieldS(0, 100);
    quint64 file_size = readFieldN(124, 12);
    quint64 checksum = readFieldN(148, 8);
    writeFieldS(148, 8, "        ");
    calculateChecksum();
    qDebug() << file_name << file_size << checksum;

    bool is_dir = file_name.endsWith('/');
    if (!is_dir && file_size > 0) {
        m_fileSizeLeft = file_size;
        m_nextBlockType = DataBlock;
    }

    // Sanity checks:
    // 1) No .. path segments
    if (file_name.contains("../")) {
        qDebug() << "[tar] skipping path with .. entry:" << file_name;
        return;
    }

    if (file_name.contains(':')) {
        qDebug() << "[tar] skipping path with drive letter:" << file_name;
        return;
    }

    if (file_name.startsWith('/')) {
        qDebug() << "[tar] skipping absolute path:" << file_name;
        return;
    }

    if (is_dir) {
        m_dir.mkdir(file_name);
    } else {
        m_currentFile.setFileName(m_dir.absoluteFilePath(file_name));
        m_currentFile.open(QIODevice::WriteOnly);
        if (file_size == 0) {
            m_currentFile.close();
        }
    }
}


void TarStream::writeFileData()
{
    if (m_fileSizeLeft < BLOCK_SIZE) {
        m_block.mid(0, m_fileSizeLeft);
        m_fileSizeLeft = 0;
    } else {
        m_fileSizeLeft -= BLOCK_SIZE;
    }
    m_currentFile.write(m_block);
    if (m_fileSizeLeft == 0) {
        qDebug() << "LAST DATA BLOCK";
        m_currentFile.close();
        m_nextBlockType = FileHeaderBlock;
    }
}

QString TarStream::readFieldS(int offset, int size)
{
    return m_block.mid(offset, size);
}

quint64 TarStream::readFieldN(int offset, int size)
{
    return m_block.mid(offset, size).toULongLong(0, 8);
}

void TarStream::writeFieldS(int offset, int size, QString field)
{
    field.truncate(size);
    m_block.replace(offset, field.size(), field.toAscii());
}

void TarStream::writeFieldN(int offset, int size, quint64 number)
{
    QByteArray field = QByteArray::number(number, 8);
    field.truncate(size - 1);
    field.append('\0');
    if (field.size() < size) {
        field.prepend(QByteArray(size - field.size(), '0'));
    }
    Q_ASSERT(field.size() == size);
    m_block.replace(offset, size, field);
}


bool TarStream::isNullBlock() const
{
    return (m_block.count('\0') == BLOCK_SIZE);
}

void TarStream::calculateChecksum()
{
    m_checksumUnsigned = m_checksumSigned = 0;
    for (int i = 0; i < m_block.size(); ++i) {
        m_checksumUnsigned += (unsigned char)m_block.at(i);
        m_checksumSigned   += m_block.at(i);
    }
}
