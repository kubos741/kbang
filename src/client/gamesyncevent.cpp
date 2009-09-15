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

#include "gamesyncevent.h"
#include "game.h"

using namespace client;

GameSyncEvent::GameSyncEvent(Game* game, const GameSyncData& gameSyncData):
        GameEvent(game),
        m_gameSyncData(gameSyncData)
{
}

/* virtual */
GameSyncEvent::~GameSyncEvent()
{
}

/* virtual */ void
GameSyncEvent::run()
{
    if (m_gameSyncData.players.size() > 7) {
        qCritical("Received GameSyncEvent with too many players.");
    }
    int index = 0;

    ///@note We can determine whether the player is playing or spectating by
    ///      checking the localPlayer.id. It would be nice to be able to switch
    ///      between player and spectator interfaces during the game.

    if (m_gameSyncData.localPlayer.id != 0) {
        // We try to determine index of local player in m_gameSyncData.players    
        for (; index < m_gameSyncData.players.size(); ++index) {
            if (m_gameSyncData.players[index].id == m_gameSyncData.localPlayer.id) {
                break;
            }
        }
    }

    game()->setGameState(m_gameSyncData.gameState);
    game()->setIsCreator(m_gameSyncData.isCreator);

    game()->setGraveyard(m_gameSyncData.graveyard);

    if (m_gameSyncData.localPlayer.id != 0) {
        // set the LocalPlayerWidget
        game()->setLocalPlayer(m_gameSyncData.players[index]);
        game()->setLocalPlayer(m_gameSyncData.localPlayer);
        int localPlayerIndex = index;

        // set OpponentWidgets to the left from local player
        index++;
        int opponentIndex = 1;
        while (index < m_gameSyncData.players.size()) {
            game()->insertOpponent(opponentIndex, m_gameSyncData.players[index]);
            index++; opponentIndex++;
        }
        int firstUnusedOpponentIndex = opponentIndex;

        // set OpponentWidgets to the right from local player
        index = localPlayerIndex - 1;
        opponentIndex = -1;
        while (index >= 0) {
            game()->insertOpponent(opponentIndex, m_gameSyncData.players[index]);
            index--; opponentIndex--;
        }
        int lastUnusedOpponentIndex = opponentIndex;

        // clear OpponentWidgets in range from firstUnusedOpponentWidget to
        // lastUnusedOpponentIndex
        game()->clearOpponentWidgetRange(firstUnusedOpponentIndex,
                                         lastUnusedOpponentIndex);
    } else {
        // when we spectate, we don't need to align players according to
        // local player
        for (index = 0; index < m_gameSyncData.players.size(); ++index) {
            game()->insertOpponent(index, m_gameSyncData.players[index]);
        }
        game()->clearOpponentWidgetRange(index + 1, -1);
    }

    game()->setGameContext(m_gameSyncData.gameContext);
    game()->setSelection(m_gameSyncData.selection);

    emit finished(this);
}
