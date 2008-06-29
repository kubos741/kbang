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
#include "gamestate.h"
#include "tcpserver.h"
#include "client.h"

#include <QTcpSocket>

GameServer* GameServer::sm_instance = 0;

GameServer::GameServer():
    QObject(0),
    m_nextClientId(0),
    m_nextGameId(0),
    m_maxClientCount(1)
{
    mp_tcpServer = new TcpServer(this);
}

GameState* GameServer::createGame(const QString & name, const QString & description, int creatorId,
                                  int minPlayers, int maxPlayers, int maxObservers,
                                  const QString & playerPassword, const QString & observerPassword,
                                  bool shufflePlayers)
{
    while (!m_nextGameId || m_games.contains(m_nextGameId)) m_nextGameId++;
    int gameId = m_nextGameId++;
    GameState* newGame = new GameState(this, gameId, name, description, creatorId, minPlayers, maxPlayers,
                                       maxObservers, playerPassword, observerPassword, shufflePlayers);
    m_games[gameId] = newGame;
    return newGame;
}


/**
 * Tells the TcpServer to listen for incoming connections.
 * @return
 */
bool GameServer::listen()
{
    if (!mp_tcpServer->isListening()) return mp_tcpServer->listen();
    return 1;
}

void GameServer::exit()
{
    emit aboutToQuit();
}

void GameServer::createClient()
{
    if (!mp_tcpServer->hasPendingConnections()) return;
    if (m_clients.size() >= m_maxClientCount)
    {
        // The aplication of the client count limit should be
        // done in a more polite way
        QTcpSocket* socket = mp_tcpServer->nextPendingConnection();
        socket->disconnectFromHost();
        return;
    }

    while (!m_nextClientId || m_clients.contains(m_nextClientId)) m_nextClientId++;
    int clientId = m_nextClientId++;
    m_clients.insert(clientId, 0);
    QTcpSocket* socket = mp_tcpServer->nextPendingConnection();
    m_clients[clientId] = new Client(this, clientId, socket);
    connect(m_clients[clientId], SIGNAL(clientDisconnected(int)),
            this, SLOT(deleteClient(int)));
}

void GameServer::deleteClient(int clientId)
{
    if (m_clients.contains(clientId) && m_clients[clientId]) m_clients[clientId]->deleteLater();
    //if (m_clients.contains(clientId) && m_clients[clientId]) delete m_clients[clientId];
    m_clients.remove(clientId);
}







