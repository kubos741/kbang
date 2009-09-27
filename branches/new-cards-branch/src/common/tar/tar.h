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

#ifndef TARSTREAM_H
#define TARSTREAM_H

#include <QObject>
#include <QIODevice>
#include <QFile>
#include <QDir>

class TarStream: public QObject {
Q_OBJECT;
public:
    enum Mode {
        InvalidMode = 0,
        TarMode,    /**< Data from filesystem are tared and written to device. */
        UntarMode   /**< Data from device are read and untared to filesystem. */
    };
    TarStream();
    virtual ~TarStream();

    void open(QDir dir, QIODevice* device, Mode mode);


private slots:
    void readBlock();


private:
    void writeNextFile();
    void writeFileData();

    QString readFieldS(int offset, int size);
    quint64 readFieldN(int offset, int size);

    void writeFieldS(int offset, int size, QString field);
    void writeFieldN(int offset, int size, quint64 number);

    bool isNullBlock() const;
    void calculateChecksum();

private:
    enum BlockType {
        InvalidBlock = 0,
        FileHeaderBlock,
        DataBlock,
        TrailingBlock
    };
    enum { BLOCK_SIZE = 512 };

    QDir        m_dir;
    QIODevice*  mp_device;
    Mode        m_mode;
    BlockType   m_nextBlockType;
    QByteArray  m_block;
    int         m_checksumUnsigned;
    int         m_checksumSigned;
    QFile       m_currentFile;
    ulong       m_fileSizeLeft;
};

#endif // TARSTREAM_H
