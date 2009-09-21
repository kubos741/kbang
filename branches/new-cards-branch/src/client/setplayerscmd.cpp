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

#include "setplayerscmd.h"
#include "game.h"

#include <QTimer>

#include "debug/debugblock.h"

using namespace client;

SetPlayersCmd::SetPlayersCmd(GameEvent* gameEvent, SetPlayersCmdDataPtr cmd):
        GameEventCmd(gameEvent), mp_doCmd(cmd)
{
}

/* virtual */
SetPlayersCmd::~SetPlayersCmd()
{
}

/* virtual */
void SetPlayersCmd::doEventCmd(GameEvent::ExecutionMode)
{
    DEBUG_BLOCK;
    ///@todo Now this cmd works only for replays.

    foreach (const SetPlayersCmdData::PlayerData& player, mp_doCmd->players) {
        DEBUG_BLOCK;
        PublicPlayerData playerData;
        playerData.id = player.id;
        playerData.name = player.name;
        playerData.character = player.character;
        playerData.role = player.role;
        playerData.handSize = 0;
        playerData.isAI = 0;
        playerData.hasController = 1;
        playerData.isSheriff = (player.role == ROLE_SHERIFF);
        playerData.isWinner = 0;
        playerData.isAlive = 1;
        mp_gameEvent->game()->appendOpponent(playerData);
    }
    mp_doCmd.clear();
    QTimer::singleShot(50, this, SLOT(finish()));
}

/* virtual */
void SetPlayersCmd::undoEventCmd(GameEvent::ExecutionMode)
{
}
