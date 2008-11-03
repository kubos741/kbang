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
 QObject(parent), m_id(clientId)
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
            parent, SLOT(actionCreateGame(StructGame, StructPlayer)));
    connect(mp_parser, SIGNAL(sigActionJoinGame(int, StructPlayer)),
            parent, SLOT(actionJoinGame(int, StructPlayer)));
    connect(mp_parser, SIGNAL(sigActionLeaveGame()),
            parent, SLOT(actionLeaveGame()));
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
    /// TODO: test if client is already in game
    
    Game* newGame = GameServer::instance().createGame(game);
    Player* newPlayer = newGame->createNewPlayer(player);
    
    
}

void Client::actionJoinGame(int gameId, StructPlayer player)
{
    /// TODO: join games...
}

void Client::actionLeaveGame()
{
    /// TODO: leave games

}



