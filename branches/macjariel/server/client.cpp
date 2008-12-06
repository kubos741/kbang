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
#include "game.h"

#include <QTcpSocket>

Client::Client(GameServer *parent, int clientId, QTcpSocket *socket):
 QObject(parent), m_id(clientId), mp_player(0)
{
    Q_ASSERT(m_id != 0);
    mp_parser = new Parser(this, socket);
    qDebug("%s:%d: Client #%d connected.", __FILE__, __LINE__, m_id);
    connect(mp_parser, SIGNAL(terminated()),
            this, SLOT(deleteLater()));
    connect(mp_parser, SIGNAL(sigQueryServerInfo(QueryResult)),
            parent, SLOT(queryServerInfo(QueryResult)));
    connect(mp_parser, SIGNAL(sigQueryGame(int, QueryResult)),
            parent, SLOT(queryGame(int, QueryResult)));
    connect(mp_parser, SIGNAL(sigQueryGameList(QueryResult)),
            parent, SLOT(queryGameList(QueryResult)));
    connect(mp_parser, SIGNAL(sigActionCreateGame(StructGame, StructPlayer)),
            this, SLOT(actionCreateGame(StructGame, StructPlayer)));
    connect(mp_parser, SIGNAL(sigActionJoinGame(int, StructPlayer)),
            this, SLOT(actionJoinGame(int, StructPlayer)));
    connect(mp_parser, SIGNAL(sigActionLeaveGame()),
            this, SLOT(actionLeaveGame()));
}


Client::~Client()
{
    emit disconnected(m_id);
    qDebug("%s:%d: Client #%d disconnected.", __FILE__, __LINE__, m_id);
}

int Client::id() const
{
    return m_id;
}

void Client::actionCreateGame(StructGame game, StructPlayer player)
{
    if (mp_player) return; // TODO: error
    Game* newGame = GameServer::instance().createGame(game);
    Q_ASSERT(newGame != 0);
    joinGame(newGame, player);
}

void Client::actionJoinGame(int gameId, StructPlayer player)
{
    Game* game = GameServer::instance().game(gameId);
    if (game == 0) return; // TODO: error
    joinGame(game, player);
}

void Client::joinGame(Game* game, const StructPlayer& player)
{
    mp_player = game->createNewPlayer(player);
    if (!mp_player) return;  // TODO: error
    connectPlayer();
    mp_parser->eventJoinGame(game->gameId(), mp_player->structPlayer(), 0);
}


void Client::actionLeaveGame()
{
    disconnectPlayer();
    int playerId = mp_player->id();
    mp_player->leaveGame();
}

void Client::connectPlayer()
{
    connect(mp_parser, SIGNAL(sigActionStartGame()),
            mp_player, SLOT(startGame()));
    connect(mp_parser, SIGNAL(sigActionMessage(const QString&)),
            mp_player, SLOT(sendMessage(const QString&)));
    connect(mp_player->game(), SIGNAL(incomingMessage(int, const QString&, const QString&)),
            mp_parser, SLOT(eventMessage(int, const QString&, const QString&)));
    connect(mp_player->game(), SIGNAL(playerJoinedGame(int, const StructPlayer&)),
            mp_parser, SLOT(eventJoinGame(int, const StructPlayer&)));
    connect(mp_player->game(), SIGNAL(playerLeavedGame(int,int)),
            this, SLOT(leavingGame(int,int)));
}

void Client::disconnectPlayer()
{
    /// Since the player is destroyed later, we don't need to
    /// manually disconnect signal-slot connections.
}

void Client::leavingGame(int gameId, int playerId)
{
    Q_ASSERT(mp_player);
    if (playerId == mp_player->id())
    {
        mp_parser->eventLeaveGame(gameId, playerId, 0);
        mp_player = 0;
    }
    else
    {
        mp_parser->eventLeaveGame(gameId, playerId, 1);
    }
}




