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
    connect(mp_parser, SIGNAL(sigActionStartGame()),
            this, SLOT(actionStartGame()));
}


Client::~Client()
{
    if (mp_player) actionLeaveGame(); // If client is in game, it should leave it
    emit disconnected(m_id);
    qDebug("%s:%d: Client #%d disconnected.", __FILE__, __LINE__, m_id);
}

int Client::id() const
{
    return m_id;
}

void Client::actionCreateGame(const StructGame& game, const StructPlayer& player)
{
    if (mp_player) return; // Already in game - do nothing
    StructGame g = game;
    g.creatorId = id();
    Game* newGame = GameServer::instance().createGame(g);
    Q_ASSERT(newGame != 0);
    joinGame(newGame, player);
}

void Client::actionJoinGame(int gameId, const StructPlayer& player)
{
    qDebug() << gameId;
    if (mp_player) return; // TODO: Already in game - do nothing
    Game* game = GameServer::instance().game(gameId);
    qDebug() << game;
    if (game == 0) return; // TODO: error
    qDebug("actionJoinGame");
    joinGame(game, player);
}

void Client::joinGame(Game* game, const StructPlayer& player)
{
    qDebug(qPrintable(QString("Player %1 is joining the game %2").arg(player.name).arg(game->name())));
    mp_player = game->createNewPlayer(player);
    Q_ASSERT(mp_player != 0);
    connectPlayer();
    mp_parser->eventJoinGame(game->gameId(), mp_player->structPlayer(), 0);
}


void Client::actionLeaveGame()
{
    if (mp_player == 0) return; // Client is not in a game
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
    connect(mp_player->game(), SIGNAL(playerLeavedGame(int, const StructPlayer&)),
            this, SLOT(leavingGame(int,const StructPlayer&)));
    connect(mp_player->game(), SIGNAL(playerDrawedCard(Player*, CardAbstract*)),
            this, SLOT(playerDrawedCard(Player*, CardAbstract*)));
}

void Client::disconnectPlayer()
{
    disconnect(mp_player->game(), SIGNAL(incomingMessage(int, const QString&, const QString&)),
               mp_parser, SLOT(eventMessage(int, const QString&, const QString&)));
    disconnect(mp_player->game(), SIGNAL(playerJoinedGame(int, const StructPlayer&)),
               mp_parser, SLOT(eventJoinGame(int, const StructPlayer&)));
    disconnect(mp_player->game(), SIGNAL(playerLeavedGame(int, const StructPlayer&)),
               this, SLOT(leavingGame(int,const StructPlayer&)));
    disconnect(mp_player->game(), SIGNAL(playerDrawedCard(Player*, CardAbstract*)),
               this, SLOT(playerDrawedCard(Player*, CardAbstract*)));

}

void Client::leavingGame(int gameId, const StructPlayer& player)
{
    Q_ASSERT(mp_player);
    if (player.id == mp_player->id())
    {
        mp_parser->eventLeaveGame(gameId, player, 0);
        disconnectPlayer();
        mp_player = 0;
    }
    else
    {
        mp_parser->eventLeaveGame(gameId, player, 1);
    }
}

void Client::actionStartGame()
{
    if (mp_player == 0) return;
    if (mp_player->game()->creatorId() == id())
    {
        mp_player->game()->startGame();
    }
}

void Client::playerDrawedCard(Player *player, CardAbstract *card)
{
    StructCardMovement x;
    x.pocketFrom = POCKET_DECK;
    x.pocketTo   = POCKET_HAND;
    x.playerTo   = player->id();
    if (player == mp_player)
    {
        x.cardDetails = card->cardDetails();
    }
    mp_parser->eventCardMovement(x);
}




