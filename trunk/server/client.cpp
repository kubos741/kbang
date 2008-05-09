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

#include "client.h"
#include "gameserver.h"

#include <QTcpSocket>
#include <iostream>



Client::Client(GameServer *parent, int clientId, QTcpSocket *socket)
 : QObject(parent), mp_tcpSocket(socket), m_clientId(clientId),
   m_xml(socket), m_parsingState(START)
{
    std::cerr << "Client id " << clientId << " connected." << std::endl;    
//    connect(socket, SIGNAL(destroyed()),
//            this, SLOT(deleteLater()));
/*            
    connect(this, SIGNAL(destroyed()),
            socket, SLOT(deleteLater()));
*/
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(readData()));
            
//    connect(socket, SIGNAL(disconnected()),
//            socket, SLOT(deleteLater()));
    
    connect(socket, SIGNAL(disconnected()),
            this, SLOT(disconnectFromHost()));
            
}




Client::~Client()
{
    std::cerr << "Client id " << m_clientId << " dies!" << std::endl;
}

void Client::readData()
{
    qDebug("Client::readData()");
    bool disconnect = 0;
    while(!m_xml.atEnd())
    {
        QXmlStreamReader::TokenType tokenType = m_xml.readNext();
        std::cout << tokenType << std::endl;
        if (tokenType <= 3 || tokenType >= 7) continue;
        switch(m_parsingState)
        {
            case START:
                disconnect = parseStart();
                break;
        }
    }
    QXmlStreamReader::Error error = m_xml.error();
    if (error && error != 4)
    {
        std::cout << error << std::endl;
        qDebug("Invalid client. XmlStreamReader::Error.");
        disconnect = 1;
    }
    if (disconnect)
    {
        disconnectFromHost();
    }
}

void Client::disconnectFromHost()
{
    m_xml.clear();
    mp_tcpSocket->disconnectFromHost();
    emit clientDisconnected(m_clientId);
}

bool Client::parseStart()
{
    if (!m_xml.isStartElement() || m_xml.name() != "stream")
    {
        qDebug("Invalid client. Opening stream tag expected.");
        return 1;
    }
    QXmlStreamAttributes attrs = m_xml.attributes();
    QStringList version = attrs.value("", "version").toString().split(".");
    if (version.size() >= 1) m_protocolVersion.first = version[0].toInt();
    if (version.size() >= 2) m_protocolVersion.second = version[1].toInt();
    std::cout << "Version: " << m_protocolVersion.first << "." << m_protocolVersion.second << std::endl;
    return 0;
}


