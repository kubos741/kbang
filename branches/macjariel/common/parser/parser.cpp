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
#include "xmlnode.h"
#include "conversions.h"

#include <QtDebug>

#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#define PROTOCOL_VERSION "1.0"
#define ASSERT_SOCKET if (!mp_socket) return

Parser::Parser(QObject* parent):
QObject(parent), mp_socket(0), m_streamInitialized(0), m_readerState(S_Start), m_readerDepth(0), mp_parsedStanza(0)
{

}

Parser::Parser(QObject* parent, QIODevice* socket):
QObject(parent), mp_socket(0),  m_streamInitialized(0), m_readerState(S_Start), m_readerDepth(0), mp_parsedStanza(0)
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
//        qDebug() << this << "token: " << mp_streamReader->tokenType() <<
//                            "name: " << mp_streamReader->name().toString() <<
//                            "text: " << mp_streamReader->text().toString();


        if (mp_streamReader->isEndElement()) m_readerDepth--;

        switch(m_readerState)
        {
        case S_Start:
            stateStart();
            break;
        case S_Ready:
            stateReady();
            break;
        case S_Stanza:
            stateStanza();
            break;
        case S_Terminated:
            break;
        case S_Error: // TODO
            break;
        }
        

        if (mp_streamReader->isStartElement()) m_readerDepth++;
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
        sendTermination();
        return;
    }
    if (!mp_streamReader->isStartElement())
    {
        m_readerState = S_Error;
        return;
    }
    // Starting to read new stanza
    Q_ASSERT(mp_parsedStanza == 0);
    mp_parsedXmlElement = mp_parsedStanza = new XmlNode(0, mp_streamReader->name(), mp_streamReader->attributes());
    m_readerState = S_Stanza;
}

void Parser::stateStanza()
{
    if (mp_streamReader->isEndElement() && m_readerDepth == 1)
    {
        
        processStanza();
        // TODO: Process the stanza
//        mp_parsedStanza->debugPrint();
        delete mp_parsedStanza;
        mp_parsedStanza = mp_parsedXmlElement = 0;
        m_readerState = S_Ready;
        return;
    }
    if (mp_streamReader->isStartElement())
    {
        mp_parsedXmlElement = mp_parsedXmlElement->createChildNode(mp_streamReader->name(), mp_streamReader->attributes());
    }
    if (mp_streamReader->isEndElement())
    {
        mp_parsedXmlElement = mp_parsedXmlElement->parentNode();
    }
}

void Parser::processStanza()
{
    if (mp_parsedStanza->name() == "query")
    {
        const QString& id = mp_parsedStanza->attribute("id");
        if (mp_parsedStanza->attribute("type") == "get")
        {
            XmlNode* query = mp_parsedStanza->getFirstChild();
            if (!query) return;
            if (query->name() == "serverinfo")
            {
                emit sigQueryServerInfo(QueryResult(mp_streamWriter, id));
                return;
            }
            if (query->name() == "game")
            {
                int gameId = query->attribute("id").toInt();
                emit sigQueryGame(gameId, QueryResult(mp_streamWriter, id));
                return;
            }
            if (query->name() == "gamelist")
            {
                emit sigQueryGameList(QueryResult(mp_streamWriter, id));
                return;
            }
        }
        if (mp_parsedStanza->attribute("type") == "result")
        {
            if (m_getQueries.contains(id))
            {
                m_getQueries[id]->parseResult(mp_parsedStanza->getFirstChild());
                m_getQueries[id]->deleteLater();
                m_getQueries.remove(id);
            }
        }
    
    
    }
    if (mp_parsedStanza->name() == "action")
    {
        XmlNode* action = mp_parsedStanza->getFirstChild();
        if (!action) return;
        if (action->name() == "create-game")
        {
            XmlNode* player = action->getFirstChild();
            if (!player) return;
            StructGame game = getGameFromXml(action);
            StructPlayer p = getPlayerFromXml(player);
            emit sigActionCreateGame(game, p);
            return;
        }
        if (action->name() == "join-game")
        {
            int gameId = action->attribute("id").toInt();
            XmlNode* player = action->getFirstChild();
            if (!player) return;
            StructPlayer p = getPlayerFromXml(player);
            emit sigActionJoinGame(gameId, p);
            return;
        }
        if (action->name() == "leave-game")
        {
            emit sigActionLeaveGame();
            return;
        }
    }

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

void Parser::sendTermination()
{
    mp_streamWriter->writeEndElement();
    mp_streamWriter->writeEndDocument();
    emit terminated();
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
