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

#include "serverconnection.h"
#include "serverquery.h"
#include "xmlnode.h"
#include <QTcpSocket>
#include <QtXml>

ServerConnection::ServerConnection(QObject *parent)
 : QObject(parent), m_depth(0), mp_rootNode(0), mp_currentNode(0)
{
    mp_tcpSocket = new QTcpSocket(this);
    mp_xmlStreamReader = new QXmlStreamReader(mp_tcpSocket);
    mp_xmlStreamWriter = new QXmlStreamWriter(mp_tcpSocket);

    ServerQuery::smp_xmlStreamWriter = mp_xmlStreamWriter;
    

    connect(mp_tcpSocket, SIGNAL(connected()),
            this, SLOT(connected()));
    connect(mp_tcpSocket, SIGNAL(disconnected()),
            this, SLOT(disconnected()));            
    connect(this, SIGNAL(statusChanged(bool, QString, QString, QString)),
            parent, SLOT(serverConnectionStatusChanged(bool, QString, QString, QString)));
            
    connect(mp_tcpSocket, SIGNAL(readyRead()),
            this,         SLOT(readData()));
}


ServerConnection::~ServerConnection()
{
    delete mp_xmlStreamReader;
    delete mp_xmlStreamWriter;
}

void ServerConnection::connectToServer(QString serverHost, int serverPort)
{
    if (mp_tcpSocket->state() == QAbstractSocket::UnconnectedState)
    {
        emit logMessage(tr("Connecting to %1.").arg(serverHost));
        mp_tcpSocket->connectToHost(serverHost, serverPort);
        m_serverHost = serverHost;
    }
}

void ServerConnection::disconnectFromServer()
{
    emit logMessage(tr("Disconnecting from %1.").arg(m_serverHost));
    mp_tcpSocket->disconnectFromHost();
}

void ServerConnection::connected()
{
    emit statusChanged(1, m_serverHost, "", "");
    emit logMessage(tr("Connected to %1.").arg(m_serverHost));
    mp_xmlStreamWriter->writeStartDocument();
    mp_xmlStreamWriter->writeStartElement("stream");
    mp_xmlStreamWriter->writeAttribute("version", "1.0");
    mp_xmlStreamWriter->writeCharacters("");
    ServerQuery* query = serverQuery("serverinfo");
    connect(query, SIGNAL(responseRecieved(XmlNode*)),
            this,  SLOT(recievedServerInfo(XmlNode*)));
    query->post();
}

void ServerConnection::disconnected()
{
    emit statusChanged(0, "", "", "");
    emit logMessage(tr("Disconnected."));
}

ServerQuery* ServerConnection::serverQuery(const QString & elementName)
{
    return new ServerQuery(this, elementName);
}

void ServerConnection::readData()
{
    QXmlStreamReader *x = mp_xmlStreamReader;
    emit incomingXml(mp_tcpSocket->peek(mp_tcpSocket->bytesAvailable()));
    while(!x->atEnd())
    {
        x->readNext();
        if (!(x->isStartElement() || x->isEndElement() ||
             (x->isCharacters() && !x->isWhitespace())))
        {
            continue;
        }
        if (x->isEndElement()) m_depth--;
        switch(m_depth)
        {
        case 0:
//            parseStream(); break;
            break;
        case 1:
            if (x->isStartElement()) // The start of new stanza
            {
                Q_ASSERT(!mp_rootNode && !mp_currentNode);
                mp_rootNode = mp_currentNode = new XmlNode(0, x->name(), x->attributes());
            }
            if (x->isEndElement()) // The end of stanza
            {
                Q_ASSERT(mp_rootNode);
                // Some processing - someone else is now responsible for freeing mp_rootNode
                processStanza(mp_rootNode);
                mp_rootNode = mp_currentNode = 0;
            }
            break;
        default:
            Q_ASSERT(mp_rootNode && mp_currentNode);
            if (x->isStartElement())
            {
                mp_currentNode = mp_currentNode->createChildNode(x->name(), x->attributes());
            }
            if (x->isEndElement())
            {
                
                mp_currentNode = mp_currentNode->parentNode();
            }
            break;
        }
        
        
        if (x->isStartElement()) m_depth++;
    }

}

void ServerConnection::processStanza(XmlNode* rootNode)
{
    if (rootNode->name() == "query" && rootNode->attribute("type") == "result")
    {
        ServerQuery::processResultQuery(rootNode); return;
    }
    XmlNode* childNode = rootNode->getFirstChild();
    if (rootNode->name() == "event" && childNode)
    {
        if (childNode->name() == "join-game")
        {
            recievedEventJoinGame(rootNode);
            return;
        }
        if (childNode->name() == "leave-game")
        {
            recievedEventLeaveGame(rootNode);
            return;
        }
        if (childNode->name() == "chat-message")
        {
            recievedEventChatMessage(rootNode);
            return;
        }
    }

}

void ServerConnection::recievedServerInfo(XmlNode* node)
{
    XmlNode* serverInfoNode = node->getFirstChild();
    if (serverInfoNode && serverInfoNode->name() == "serverinfo")
    {
        m_serverName = serverInfoNode->attribute("name");
        m_serverDescription = serverInfoNode->attribute("description");
        emit statusChanged(1, m_serverHost, m_serverName, m_serverDescription);
    }
}

void ServerConnection::joinGame(int gameId, QString gameName, bool spectate, QString password)
{
    emit logMessage(tr("Joining game %1.").arg(gameName));
    QXmlStreamWriter* x = mp_xmlStreamWriter;
    x->writeStartElement("action");
    x->writeStartElement("join-game");
    x->writeAttribute("id", QString::number(gameId));
    x->writeStartElement(spectate ? "spectator" : "player");
    x->writeAttribute("name", "Player"); // TODO
    if (!password.isNull())
    {
        x->writeAttribute("password", password);
    }
    x->writeEndElement();
    x->writeEndElement();
    x->writeEndElement();
}

void ServerConnection::leaveGame()
{
    QXmlStreamWriter* x = mp_xmlStreamWriter;
    x->writeStartElement("action");
    x->writeEmptyElement("leave-game");
    x->writeEndElement();
}



void ServerConnection::recievedEventJoinGame(XmlNode* node)
{
    emit logMessage(tr("You have entered the game."));
    delete node;
}

void ServerConnection::recievedEventLeaveGame(XmlNode* node)
{
    emit logMessage(tr("You have left the game."));
    delete node;
}

void ServerConnection::recievedEventChatMessage(XmlNode* node)
{
    XmlNode* messageNode = node->getFirstChild();
    Q_ASSERT(messageNode);
    const int& senderId = messageNode->attribute("senderId").toUInt();
    const QString& senderName = messageNode->attribute("senderName");
    const QString& message = messageNode->attribute("message");
    emit incomingChatMessage(senderId, senderName, message);
    delete node;
}

void ServerConnection::sendChatMessage(const QString& message)
{
    QXmlStreamWriter* x = mp_xmlStreamWriter;
    x->writeStartElement("action");
    x->writeStartElement("chat-message");
    x->writeAttribute("message", message);
    x->writeEndElement();
    x->writeEndElement();
}



