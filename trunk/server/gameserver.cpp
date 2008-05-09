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

GameServer::GameServer(): QObject(0),  m_nextClientId(0)
{
    mp_tcpServer = new TcpServer(this);
}

QPointer< GameState > GameServer::createGame(const Client & creator, int maxPlayers, int AIPlayers)
{
    QPointer<GameState> gameState = new GameState(this, creator, maxPlayers, AIPlayers);
    m_games.append(gameState);
    return gameState;
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
    /* TODO: Max Clients Limit */
    while (m_clients.contains(m_nextClientId)) m_nextClientId++;
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





