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

#ifndef GAMESYNCEVENT_H
#define GAMESYNCEVENT_H

#include "gameevent.h"
#include "gamestructs.h"

namespace client
{
/**
 * The GameSyncEvent class represents the game-sync game event. This event is
 * used to synchronize the whole state of the game. This event is usually
 * sent if a client connects to a game that has been started before.
 * @author MacJariel
 */
class GameSyncEvent: public GameEvent
{
public:
    /**
     * Constructs a GameSyncEvent related to <i>game</i>, according to
     * given GameSyncData.
     */
    GameSyncEvent(Game* game, const GameSyncData& gameSyncData);

    /**
     * Destroys the GameSyncEvent.
     */
    virtual ~GameSyncEvent();

    /**
     * Runs the event.
     */
    virtual void run();

private:
    GameSyncData m_gameSyncData;
};
}

#endif // GAMESYNCEVENT_H
