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
#include "command.h"
#include <QTcpSocket>
#include <QStringList>
#include <QtDebug>

#include <iostream>


ClientXmlParser::ClientXmlParser(Client* parent, QTcpSocket* socket):
QObject(parent), m_xmlIn(socket), m_xmlOut(socket), mp_socket(socket),
mp_client(parent), m_depth(0), m_inStreamInitialized(0),
m_outStreamInitialized(0), mp_command(0)
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
while(!m_xmlIn.atEnd())
    {
        m_xmlIn.readNext();
        if (!(m_xmlIn.isStartElement() || m_xmlIn.isEndElement() ||
             (m_xmlIn.isCharacters() && !m_xmlIn.isWhitespace()))) continue;
        qDebug() << "T:" << m_xmlIn.tokenType() << "N:" << m_xmlIn.name().toString() << "Text:" << m_xmlIn.text().toString();
        if (m_xmlIn.isEndElement()) m_depth--;
        switch(m_depth)
        {
        case 0:
            parseStream();
            break;
        case 1:
            if (m_xmlIn.isStartElement()) // The start of a new stanza recieved
            {
                Q_ASSERT(!mp_command);
                mp_command = Command::create(m_xmlIn);
            }
            if (m_xmlIn.isEndElement()) // The end of stanza - completing command and sending for another processing
            {
                Q_ASSERT(mp_command);
                mp_command->execute(m_xmlOut);
                //sendData(mp_command->execute());
                delete mp_command;
                mp_command = 0;
            }
            break;
        default:
            // Depth > 1 - we are in the middle of a stanza - let command handle it
            mp_command->processToken(m_xmlIn);
            break;
        }
        if (m_xmlIn.isStartElement()) m_depth++;
    }

    QXmlStreamReader::Error error = m_xmlIn.error();
    if (error && error != 4)
    {
        qDebug("Invalid client. XmlStreamReader::Error.");
        mp_client->disconnectFromHost();
    }
}


void ClientXmlParser::disconnectFromHost()
{
    mp_socket->flush();
    m_xmlIn.clear();
    mp_socket->disconnectFromHost();
    mp_socket->deleteLater();
}

void ClientXmlParser::parseStream()
{
    if (!m_inStreamInitialized)
    {
        // Parsing incoming <stream>
        if (!m_xmlIn.isStartElement() || m_xmlIn.name() != "stream")
        {
            qDebug("Invalid client: expected <stream> as first element.");
            mp_client->disconnectFromHost();
            return;
        }
        QXmlStreamAttributes attrs = m_xmlIn.attributes();
        QStringList version = attrs.value("", "version").toString().split(".");
        if (version.size() >= 1) m_protocolVersion.major = version[0].toInt();
        if (version.size() >= 2) m_protocolVersion.minor = version[1].toInt();
        m_inStreamInitialized = 1;

        m_xmlOut.setAutoFormatting(1);
        m_xmlOut.writeStartDocument();
        m_xmlOut.writeStartElement("stream");
        m_xmlOut.writeAttribute("version", "1.0");
        m_xmlOut.writeCharacters("");

        m_outStreamInitialized = 1;
        return;
    }

    if (m_xmlIn.isEndElement() && m_xmlIn.name() == "stream")
    {
        // Finishing stream & disconnecting
        m_xmlOut.writeEndDocument();
        mp_client->disconnectFromHost();
        return;
    }
    // Unknown element, disconnecting
    mp_client->disconnectFromHost();
}

void ClientXmlParser::sendData(const QString& data)
{
    mp_socket->write(data.toUtf8());
}

void ClientXmlParser::parseStanza()
{



}


