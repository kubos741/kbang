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


#include "parser.h"
#include "queryget.h"
#include "util.h"
#include <QtDebug>

#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#define PROTOCOL_VERSION "1.0"
#define ASSERT_SOCKET if (!mp_socket) return

Parser::Parser(QObject* parent):
QObject(parent), mp_socket(0), m_streamInitialized(0), m_readerState(S_Start), m_readerDepth(0)
{

}

Parser::Parser(QObject* parent, QIODevice* socket):
QObject(parent), mp_socket(0),  m_streamInitialized(0), m_readerState(S_Start), m_readerDepth(0)
{
    attachSocket(socket);
}

Parser::~Parser()
{

}

void Parser::attachSocket(QIODevice* socket)
{
    Q_ASSERT(socket);
    if (mp_socket) detachSocket();
    mp_socket = socket;
//    connect(mp_socket, SIGNAL(disconnected()),
//            this, SLOT(detachSocket()));

    mp_streamReader = new QXmlStreamReader(mp_socket);
    mp_streamWriter = new QXmlStreamWriter(mp_socket);
    connect(mp_socket, SIGNAL(readyRead()),
            this, SLOT(readData()));


}

void Parser::detachSocket()
{
    if (!mp_socket) return;
    disconnect(mp_socket, SIGNAL(disconnected()),
               this, SLOT(detachSocket()));
    delete mp_streamWriter;
    delete mp_streamReader;
}


void Parser::initializeStream()
{
    ASSERT_SOCKET;
    sendInitialization();
}


QString Parser::protocolVersion()
{
    return QString(PROTOCOL_VERSION);
}

void Parser::readData()
{
    while (!mp_streamReader->atEnd())
    {
        mp_streamReader->readNext();
        if (!(mp_streamReader->isStartElement() ||
              mp_streamReader->isEndElement() ||
              (mp_streamReader->isCharacters() && !mp_streamReader->isWhitespace()))) continue;
        qDebug() << this << "token: " << mp_streamReader->tokenType() <<
                            "name: " << mp_streamReader->name().toString() <<
                            "text: " << mp_streamReader->text().toString();


        if (mp_streamReader->isEndElement()) m_depth--;

        switch(m_readerState)
        {
        case S_Start:
            stateStart();
            break;
        case S_Ready:
            stateReady();
            break;
        case S_QueryGet:
            stateQueryGet();
            break;
        case S_QeuryResult:
            stateQueryResult();
            break;
        case S_QueryError:
            break;
        case S_Action:
            break;
        case S_Event:
            break;
        case S_UnknownStanza:
            break;
        }

        if (mp_streamReader->isStartElement()) m_depth++;


        if (mp_streamReader->isEndElement()) m_depth--;
        switch(m_depth)
        {
            case 0:
                parseInitialization();
                break;
            case 1:
                if (mp_streamReader->name() == "query")
                {
                    m_stanzaType = TypeQuery;
                    QString type = mp_streamReader->attributes().value("type").toString();
                    QString id = mp_streamReader->attributes().value("id").toString();
                    if (type == "get")
                    {

                    }
                    else if (type == "result")
                    {
                        if (!m_getQueries.contains(id))
                        {
                            m_ignoreStanza = 1;
                            break;
                        }
                        mp_queryGet = m_getQueries[id];
                    }

                } else if (mp_streamReader->name() == "action")
                {
                    m_stanzaType = TypeQuery;
                }
                break;
            case 2:
                if (m_ignoreStanza) break;
                if (!mp_streamReader->isStartElement()) break;
                if (m_stanzaType == TypeQuery)
                {
                    if (mp_streamReader->name() == "serverinfo")
                    {
                        emit sigQueryServerInfo();
                    }
                }
                break;
//            default:
//                qDebug() << "Depth: " << m_depth << " not reached";
//                break;

        }

    }
}

void Parser::stateStart()
{
    Q_ASSERT(m_readerDepth == 0);
    if (mp_streamReader->isStartElement() &&
        mp_streamReader->name() == "stream")
    {
        QString version = mp_streamReader->attributes().value("version").toString();
        if (version != Parser::protocolVersion())
        {
            qWarning("Protocol version mismatch.");
        }
        sendInitialization();
        emit streamInitialized();
        m_readerState = S_Ready;
    }
    else
    {
        m_readerState = S_Error;
    }
}
void Parser::stateReady()
{
    Q_ASSERT(m_readerDepth == 1);
    if (mp_streamReader->isEndElement())
    {
        m_readerState = S_Terminated;
        return;
    }
    if (!mp_streamReader->isStartElement())
    {
        m_readerState = S_Error;
        return;
    }
    if (mp_streamReader->name() == "query")
    {
        QString type = mp_streamReader->attributes().value("type").toString();
        QString id   = mp_streamReader->attributes().value("id").toString();
        if (type == "get")
        {
            m_readerState = S_QueryGet;
            m_stanzaId = id;
            return;
        }
        if (type == "result")
        {
            if (!m_getQueries.contains(id))
            {
                m_readerState = S_InvalidStanza;
                return;
            }
            m_readerState = S_QueryResult;
            m_stanzaId = id;
            mp_queryGet = m_getQueries[id];
            return;
        }
        if (type == "error")
        {
            m_readerState = S_QueryError;
            m_stanzaId = id;
            return;
        }
        m_readerState = S_InvalidStanza;
        return;
    }
}

void Parser::stateQueryGet()
{
    if (mp_streamReader->isEndElement() && m_readerDepth == 1)
    {
        // Fire the query
        m_readerState = S_Ready;
        return;
    }
    if (mp_streamReader->isStartElement() && m_readerDepth == 2)
    {
        if (mp_streamReader->name() == "serverinfo")
        {

        }

    }
}

void Parser::stateQueryResult()
{
    if (mp_streamReader->isEndElement() && m_readerDepth == 1)
    {
        // Fire the query
        m_readerState = S_Ready;
        return;
    }
    mp_queryGet->parseResult(mp_streamReader);
}

void Parser::sendInitialization()
{
    if (m_streamInitialized) return;
    mp_streamWriter->writeStartDocument();
    mp_streamWriter->writeStartElement("stream");
    mp_streamWriter->writeAttribute("version", Parser::protocolVersion());
    mp_streamWriter->writeCharacters("");
    m_streamInitialized = 1;
}

QueryGet* Parser::queryGet()
{
    QString id;
    do {
        id = randomToken(10, 10);
    } while (m_getQueries.contains(id));
    QueryGet* query = new QueryGet(this, mp_streamWriter, id);
    m_getQueries[id] = query;
    return query;
}
