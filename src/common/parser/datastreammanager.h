/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
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

#ifndef DATASTREAMMANAGER_H
#define DATASTREAMMANAGER_H

#include <QObject>
#include "parser/datastreamsender.h"
#include "parser/datastreamreceiver.h"


class Parser;

/**
 * The DataStreamManager class provides a manager that manages sending raw
 * data over XML-based KBang protocol. This concept of sending data was
 * introduced in KBang protocol version 2.
 *
 *
 */
class DataStreamManager: public QObject
{
public:
    /**
     * Constructs a DataStreamManager that operates on #parser.
     */
    DataStreamManager(Parser* parser);

    quint32 initDataStream(DataStreamSender*);

    /**
     * Opens data stream to the peer.
     * @param dataStreamId The id of data stream.
     * @param dataSize The size of data. Use -1 if the size is not known.
     */
    quint32 openDataStream(quint32 dataStreamId, qint64 dataSize);

    /**
     *
     */
    void sendChunk(quint32 dataStreamId, const QByteArray& chunkData);
    void closeDataStream(quint32 dataStreamId);

    void registerDataStreamReceiver(quint32 dataStreamId, DataStreamReceiver*);


};

#endif // DATASTREAMMANAGER_H
