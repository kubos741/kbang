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
#include "gameserver.h"
#include "game.h"
#include "tcpserver.h"
#include "client.h"
#include "common.h"

#include <QTcpSocket>
#include <QXmlStreamWriter>

GameServer* GameServer::sm_instance = 0;

GameServer::GameServer():
    QObject(0),
    m_nextClientId(0),
    m_nextGameId(0),
    m_maxClientCount(1)
{
    mp_tcpServer = new TcpServer(this);
    m_name = Config::instance().getString("network", "server_name");
    m_description = Config::instance().getString("network", "server_description");
}


Game* GameServer::createGame(StructGame x)
{
    while (!m_nextGameId || m_games.contains(m_nextGameId)) m_nextGameId++;
    x.id = m_nextGameId++;
    Game* newGame = new Game(this, x);
    m_games[x.id] = newGame;
    return newGame;
}



bool GameServer::listen()
{
    if (!mp_tcpServer->isListening() && !mp_tcpServer->listen())
    {
        qCritical("ERROR: Unable to listen on %s:%d", mp_tcpServer->hostAddressString().toAscii().data(),
                  mp_tcpServer->port());
        return 0;
    }
    else
    {
        qDebug("Listening on %s:%d", mp_tcpServer->hostAddressString().toAscii().data(), mp_tcpServer->port());
    }
    return 1;
}

void GameServer::exit()
{
    emit aboutToQuit();
}

void GameServer::createClient()
{
    if (!mp_tcpServer->hasPendingConnections()) return;
    /* NOTE: This is bad - client should be ALWAYS allowed
       to connect to server (consider only querying for games
    if (m_clients.size() >= m_maxClientCount)
    {
        // The aplication of the client count limit should be
        // done in a more polite way
        QTcpSocket* socket = mp_tcpServer->nextPendingConnection();
        socket->disconnectFromHost();
        return;
    }
    */

    while (!m_nextClientId || m_clients.contains(m_nextClientId)) m_nextClientId++;
    int clientId = m_nextClientId++;
    m_clients.insert(clientId, 0);
    QTcpSocket* socket = mp_tcpServer->nextPendingConnection();
    m_clients[clientId] = new Client(this, clientId, socket);
    connect(m_clients[clientId], SIGNAL(disconnected(int)),
            this, SLOT(deleteClient(int)));
}

void GameServer::deleteClient(int clientId)
{
    m_clients.remove(clientId);
}

void GameServer::queryServerInfo(QueryResult result)
{
    StructServerInfo x;
    x.name = m_name;
    x.description = m_description;
    result.sendData(x);
}

void GameServer::queryGame(int gameId, QueryResult result)
{
    if (m_games.contains(gameId))
    {
        result.sendData(m_games[gameId]->structGame());
    }
    else
    {
        //TODO: send error
    }
}

void GameServer::queryGameList(QueryResult result)
{
    StructGameList x;
    foreach(const Game* game, m_games.values())
    {
        x.append(game->structGame());
    }
    result.sendData(x);
}


