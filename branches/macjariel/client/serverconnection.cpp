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
#include "parser/parser.h"
#include "parser/queryget.h"

#include <QTcpSocket>

ServerConnection::ServerConnection(QObject *parent)
 : QObject(parent), mp_parser(0), m_gameId(0)
{
    mp_tcpSocket = new QTcpSocket();
    connect(mp_tcpSocket, SIGNAL(connected()),
            this, SLOT(connected()));
    connect(mp_tcpSocket, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
}


ServerConnection::~ServerConnection()
{
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
    if (mp_tcpSocket->state() != QAbstractSocket::UnconnectedState)
    {
        emit logMessage(tr("Disconnecting from %1.").arg(m_serverHost));
        mp_tcpSocket->disconnectFromHost();
    }
}

void ServerConnection::connected()
{
    emit statusChanged();
    emit logMessage(tr("Connected to %1.").arg(m_serverHost));
    mp_parser = new Parser(this, mp_tcpSocket);
    initializeParserConnections();
    mp_parser->initializeStream();
    m_gameId = 0;

    QueryGet* query = queryGet();
    connect(query, SIGNAL(result(const StructServerInfo&)),
            this, SLOT(recievedServerInfo(const StructServerInfo&)));
    query->getServerInfo();
}

void ServerConnection::disconnected()
{
    mp_parser->deleteLater();
    mp_parser = 0;
    emit statusChanged();
    emit logMessage(tr("Disconnected."));
}

void ServerConnection::recievedServerInfo(const StructServerInfo& serverInfo)
{
    m_serverName = serverInfo.name;
    m_serverDescription = serverInfo.description;
    emit statusChanged();
}

void ServerConnection::joinGame(int gameId, const QString& gamePassword, const QString& playerName)
{
    emit logMessage(tr("Joining game id %1.").arg(gameId));
    StructPlayer x;
    x.name = playerName;
    mp_parser->actionJoinGame(gameId, gamePassword, x);
}

void ServerConnection::leaveGame()
{
    mp_parser->actionLeaveGame();
}

void ServerConnection::sendChatMessage(const QString& message)
{
    mp_parser->actionMessage(message);
}

QueryGet* ServerConnection::queryGet()
{
    Q_ASSERT(mp_parser != 0);
    return mp_parser->queryGet();
}

void ServerConnection::recievedEventJoinGame(int gameId, const StructPlayer& player, bool other)
{
    if (!other)
    {
        m_gameId = gameId;
        emit statusChanged();
        emit logMessage(tr("You have entered the game."));
    }
    else
    {
        emit logMessage(tr("%1 has entered the game.").arg(player.name));
    }
}

void ServerConnection::recievedEventLeaveGame(int /*gameId*/, const StructPlayer& player, bool other)
{
    if (!other)
    {
        m_gameId = 0;
        emit statusChanged();
        emit logMessage(tr("You have left the game."));
    }
    else
    {
        emit logMessage(tr("%1 has left the game.").arg(player.name));
    }

}

void ServerConnection::initializeParserConnections()
{
    connect(mp_parser, SIGNAL(sigEventJoinGame(int, const StructPlayer&, bool)),
            this, SLOT(recievedEventJoinGame(int, const StructPlayer&, bool)));
    connect(mp_parser, SIGNAL(sigEventLeaveGame(int, const StructPlayer&, bool)),
            this, SLOT(recievedEventLeaveGame(int, const StructPlayer&, bool)));
    connect(mp_parser, SIGNAL(sigEventMessage(int, const QString&, const QString&)),
            this, SIGNAL(incomingChatMessage(int, const QString&, const QString&)));
}

bool ServerConnection::isConnected()
{
    return (mp_parser != 0);
}

bool ServerConnection::isInGame()
{
    return (isConnected() && (m_gameId != 0));
}

QString ServerConnection::serverName()
{
    return m_serverName;
}

QString ServerConnection::hostName()
{
    return m_serverHost;
}



