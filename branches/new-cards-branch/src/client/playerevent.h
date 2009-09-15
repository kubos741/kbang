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

#ifndef PLAYEREVENT_H
#define PLAYEREVENT_H

#include "gameevent.h"
#include "gamestructs.h"

namespace client
{
/**
 * The PlayerEvent class can represent one of these game events:
 * * player-joined
 * * player-leaved
 * * player-update
 *
 * @author MacJariel
 */
class PlayerEvent: public GameEvent
{
Q_OBJECT;
public:
    enum Type {
        PlayerJoined,
        PlayerLeaved,
        PlayerUpdate
    };

    /**
     * Constructs a PlayerEvent.
     */
    PlayerEvent(Game* game);

    /**
     * Destroys the PlayerEvent.
     */
    virtual ~PlayerEvent();

    /**
     * Sets the PlayerEvent to player-joined game-event.
     */
    PlayerEvent* playerJoined(const PublicPlayerData&);

    /**
     * Sets the PlayerEvent to player-leaved game-event.
     */
    PlayerEvent* playerLeaved(int playerId);

    /**
     * Sets the PlayerEvent to player-update game-event.
     */
    PlayerEvent* playerUpdate(const PublicPlayerData&);

    /**
     * Runs the event.
     */
    virtual void run();

private:
    Type                m_type;
    PlayerId            m_playerId;
    PublicPlayerData    m_publicPlayerData;
};
}

#endif // PLAYEREVENT_H
