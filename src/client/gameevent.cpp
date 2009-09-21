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

#include "gameevent.h"
#include "gameeventcmd.h"
#include "game.h"
#include "cardmovementevent.h"
#include "gamecontextchangeevent.h"
#include "setplayerscmd.h"

#include "debug/debugblock.h"


using namespace client;

GameEvent::GameEvent(Game* game, GameEventDataPtr event):
        QObject(game), mp_game(game), mp_commandsIterator(0),
        mp_gameEventData(event), m_isRunning(0), m_isFirstRun(1)
{
    DEBUG_BLOCK;
    foreach (const GameEventCmdDataPtr& cmd, mp_gameEventData->cmds) {
        GameEventCmd* gameEventCmd = 0;
        switch (cmd->type()) {
        case GameEventCmdData::CardMovementType:
            gameEventCmd = new CardMovementEvent(this, cmd.staticCast<CardMovementCmdData>());
            break;
        case GameEventCmdData::GameContextType:
            gameEventCmd = new GameContextChangeEvent(this, cmd.staticCast<GameContextCmdData>());
            break;
        case GameEventCmdData::SetPlayersType:
            gameEventCmd = new SetPlayersCmd(this, cmd.staticCast<SetPlayersCmdData>());
            break;
        default:
            qDebug("TODO:___");
            ///@todo
            break;
        }
        Q_ASSERT(gameEventCmd != 0);
        connect(gameEventCmd, SIGNAL(finished(GameEventCmd*)),
                this, SLOT(gameEventCmdFinished(GameEventCmd*)));
        m_commands.append(gameEventCmd);
    }

}

/* virtual */
GameEvent::~GameEvent()
{
}

void GameEvent::doEvent(GameEvent::ExecutionMode mode)
{
    DEBUG_BLOCK;
    Q_ASSERT(m_isRunning == 0);
    m_isRunning = 1;

    if (m_isFirstRun) {
        if (mp_gameEventData->type == GameEventData::StartGameType) {
            mp_game->setGameState(GAMESTATE_PLAYING);
            mp_game->updateInterface();
        }

        ///@todo Append log message

        mp_gameEventData.clear();
        m_isFirstRun = 0;
    }

    m_forward = 1;
    step();
}

void GameEvent::undoEvent(GameEvent::ExecutionMode mode)
{
    DEBUG_BLOCK;
    Q_ASSERT(m_isRunning == 0);
    m_forward = 0;
    step();
}

void GameEvent::gameEventCmdFinished(GameEventCmd*)
{
    DEBUG_BLOCK;
    step();
}

void GameEvent::step()
{
    DEBUG_BLOCK;
    if (mp_commandsIterator == 0) {
        mp_commandsIterator = new QListIterator<GameEventCmd*>(m_commands);
        if (m_forward) {
            mp_commandsIterator->toFront();
        } else {
            mp_commandsIterator->toBack();
        }
    }

    if (m_forward && mp_commandsIterator->hasNext()) {
        mp_commandsIterator->next()->doEventCmd(ExecuteNormal);
    } else if (!m_forward && mp_commandsIterator->hasPrevious()) {
        mp_commandsIterator->previous()->undoEventCmd(ExecuteNormal);
    } else {
        delete mp_commandsIterator;
        mp_commandsIterator = 0;
        m_isRunning = 0;
        qDebug("emit GameEvent::finished()");
        emit finished(this);
    }
}
