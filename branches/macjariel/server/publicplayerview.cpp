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

#include "publicplayerview.h"
#include "player.h"
#include "playingcard.h"

PublicPlayerView::PublicPlayerView(Player* player): mp_player(player)
{
}

PublicPlayerView::~ PublicPlayerView()
{
}

int PublicPlayerView::id() const
{
    return this ? mp_player->id() : 0;
}

QString PublicPlayerView::name() const
{
    return mp_player->name();
}

bool PublicPlayerView::isCreator() const
{
    return mp_player->isCreator();
}

bool PublicPlayerView::isSheriff() const
{
    return (mp_player->role() == ROLE_SHERIFF);
}

bool PublicPlayerView::isAlive() const
{
    return mp_player->isAlive();
}

int PublicPlayerView::lifePoints() const
{
    return mp_player->lifePoints();
}

int PublicPlayerView::maxLifePoints() const
{
    return mp_player->maxLifePoints();
}

int PublicPlayerView::handSize() const
{
    return mp_player->handSize();
}

/**
 * Returns the role of the player. In case
 * the player is still alive and is not sheriff,
 * the unknown role is returned.
 */
PlayerRole PublicPlayerView::role() const
{
    if (mp_player->role() == ROLE_SHERIFF || !isAlive())
        return mp_player->role();
    return ROLE_UNKNOWN;
}

QList<PlayingCard*> PublicPlayerView::table() const
{
    return mp_player->table();
}

StructPlayer PublicPlayerView::structPlayer() const
{
    StructPlayer x;
    x.id = id();
    x.name = name();
    x.password = "";
    x.role = role();
    return x;
}

PublicPlayerData PublicPlayerView::publicPlayerData() const
{
    PublicPlayerData res;
    res.id          = mp_player->id();
    res.name        = mp_player->name();
    res.character   = mp_player->characterType();
    res.lifePoints  = lifePoints();
    res.isSheriff   = isSheriff();
    res.handSize    = handSize();
    foreach (PlayingCard* card, table()) {
        CardData cardData;
        cardData.id = card->id();
        cardData.type = card->type();
        res.table.append(cardData);
    }
    return res;
}
