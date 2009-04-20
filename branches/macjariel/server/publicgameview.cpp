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
#include "publicgameview.h"
#include "publicplayerview.h"
#include "game.h"
#include "gameinfo.h"
#include "player.h"
#include "gamecycle.h"

PublicGameView::PublicGameView(Game* game):
mp_game(game)
{
}


PublicGameView::~PublicGameView()
{
}

int PublicGameView::id() const
{
    return mp_game->id();
}

QString PublicGameView::name() const
{
    return mp_game->gameInfo().name();
}

QString PublicGameView::description() const
{
    return mp_game->gameInfo().description();
}

int PublicGameView::playersCount() const
{
    return mp_game->playersCount();
}

StructGame PublicGameView::structGame() const
{
    return mp_game->gameInfo().structGame();
}

GameContextData PublicGameView::gameContextData() const
{
    return mp_game->gameCycle().gameContextData();
}

QList<const PublicPlayerView*>  PublicGameView::publicPlayerList() const
{
    return mp_game->publicPlayerList();
}

const PublicPlayerView* PublicGameView::publicPlayerView(int playerId) const
{
    Player* player = mp_game->player(playerId);
    if (player == 0) return 0;
    return &player->publicView();
}

QList<const PublicPlayerView*> PublicGameView::neighbors(const PublicPlayerView* source, int distance) const
{
    QList<const PublicPlayerView*> result;
    foreach (const PublicPlayerView* p, mp_game->publicPlayerList()) {
        if (p->id() == source->id()) continue;
        if (mp_game->getDistance(Player::player(source), Player::player(p)) <= distance)
            result.append(p);
    }
    return result;
}
