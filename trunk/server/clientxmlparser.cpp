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

#include "clientxmlparser.h"
#include "client.h"
#include <QTcpSocket>
#include <QStringList>

#include <iostream>

ClientXmlParser::ClientXmlParser(Client* parent, QTcpSocket* socket)
 : QObject(parent), m_xml(socket), mp_socket(socket), mp_client(parent),
   m_depth(0), m_inStreamInitialized(0), m_outStreamInitialized(0)
{
    connect(socket, SIGNAL(readyRead()),
            this,   SLOT(readData()));
    m_protocolVersion.major = 0;
    m_protocolVersion.minor = 0;
}


ClientXmlParser::~ClientXmlParser()
{
}

void ClientXmlParser::readData()
{
while(!m_xml.atEnd())
    {
        QXmlStreamReader::TokenType tokenType = m_xml.readNext();
        if (tokenType <= 3 || tokenType >= 7) continue;
        if (tokenType == 6 && m_xml.isWhitespace()) continue;
        std::cerr << "Type: " << tokenType << ", Name: " << m_xml.name().toString().toStdString() << ", Text: " << m_xml.text().toString().toStdString() << std::endl;        
        if (tokenType == 5) m_depth--;
        switch(m_depth)
        {
            case 0: parseStream();
                    break;
            case 1: parseStanza();
                    break;
        }
        if (tokenType == 4) m_depth++;
    }

    QXmlStreamReader::Error error = m_xml.error();
    if (error && error != 4)
    {
        qDebug("Invalid client. XmlStreamReader::Error.");
        mp_client->disconnectFromHost();
    }
}


void ClientXmlParser::disconnectFromHost()
{
    mp_socket->flush();
    m_xml.clear();
    mp_socket->disconnectFromHost();
    mp_socket->deleteLater();
}

void ClientXmlParser::parseStream()
{
    if (!m_inStreamInitialized)
    {
        // Parsing incoming <stream>
        if (!m_xml.isStartElement() || m_xml.name() != "stream")
        {
            qDebug("Invalid client: expected <stream> as first element.");
            mp_client->disconnectFromHost();
            return;
        }
        QXmlStreamAttributes attrs = m_xml.attributes();
        QStringList version = attrs.value("", "version").toString().split(".");
        if (version.size() >= 1) m_protocolVersion.major = version[0].toInt();
        if (version.size() >= 2) m_protocolVersion.minor = version[1].toInt();
        m_inStreamInitialized = 1;
        
        // Initiating outgoing <stream>
        sendData("<stream version=\"1.0\">\n");
        m_outStreamInitialized = 1;
        return;
    }
    
    if (m_xml.isEndElement() && m_xml.name() == "stream")
    {
        // Finishing stream & disconnecting
        sendData("</stream>\n");
        mp_client->disconnectFromHost();
        return;
    }
    // Unknown element, disconnecting
    mp_client->disconnectFromHost();
}

void ClientXmlParser::sendData(const QString & data)
{
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out << data;
        mp_socket->write(block);
}

void ClientXmlParser::parseStanza()
{
    // TODO: I need to figure out how to parse stanzas

}


