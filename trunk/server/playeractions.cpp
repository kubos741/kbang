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
#include "playeractions.h"
#include "player.h"

#define QUEUEDCALL(signal) if (QThread::currentThread() != thread()) { emit signal; return; }

PlayerActions::PlayerActions(Player* player):
mp_player(player)
{
    connect(this, SIGNAL(leaveGameSignal()), this, SLOT(leaveGame()));

}

PlayerActions::~ PlayerActions()
{
}

void PlayerActions::leaveGame() const
{
    if (QThread::currentThread() != thread())
    {
        // This code is executed in the playerController thread
        //mp_player->playerControllerRunner()->quit();
    }
    
    QUEUEDCALL(leaveGameSignal());
    
    /// If the player is not already playing (before the game is active),
    /// the whole player is deleted. Else only playerController is detached,
    /// but player doesn't die.
    /// TODO: implement this idea
    
    mp_player->detachPlayerController();
}
