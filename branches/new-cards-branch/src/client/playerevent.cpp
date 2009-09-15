/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
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

#include "playerevent.h"
#include "game.h"

using namespace client;

PlayerEvent::PlayerEvent(Game* game):
        GameEvent(game)
{
}

/* virtual */
PlayerEvent::~PlayerEvent()
{
}

PlayerEvent*
PlayerEvent::playerJoined(const PublicPlayerData& publicPlayerData)
{
    m_type = PlayerJoined;
    m_publicPlayerData = publicPlayerData;
    return this;
}

PlayerEvent*
PlayerEvent::playerLeaved(int playerId)
{
    m_type = PlayerLeaved;
    m_playerId = playerId;
    return this;
}

PlayerEvent*
PlayerEvent::playerUpdate(const PublicPlayerData& publicPlayerData)
{
    m_type = PlayerUpdate;
    m_publicPlayerData = publicPlayerData;
    return this;
}

/* virtual */ void
PlayerEvent::run()
{
    GameEvent::run();
    switch(m_type) {
    case PlayerJoined:
        game()->appendOpponent(m_publicPlayerData);
        break;
    case PlayerLeaved:
        game()->removeOpponent(m_playerId);
        break;
    case PlayerUpdate:
        game()->updateOpponent(m_publicPlayerData);
        break;
    }
    GameEvent::finish();
}
