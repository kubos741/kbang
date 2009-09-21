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


#include "gameeventplayer.h"
#include "game.h"

#include "debug/debugblock.h"

using namespace client;

GameEventPlayer::GameEventPlayer(Game* game):
        QObject(game),
        mp_game(game),
        mp_runningEvent(0),
        m_currentGameEventIndex(0),
        m_mode(GameEventPlayer::PlayForwardMode)
{
}

/* virtual */
GameEventPlayer::~GameEventPlayer()
{
}

void GameEventPlayer::playForward()
{
    m_mode = PlayForwardMode;
    step();
}

void GameEventPlayer::playBackward()
{
    m_mode = PlayBackwardMode;
    step();
}

void GameEventPlayer::stepForward()
{
    m_mode = StepForwardMode;
    step();
}

void GameEventPlayer::stepBackward()
{
    m_mode = StepBackwardMode;
    step();
}

void GameEventPlayer::pause()
{
    m_mode = PauseMode;
    step();
}


void GameEventPlayer::appendGameEvent(GameEventDataPtr gameEventData)
{
    DEBUG_BLOCK;
    GameEvent* gameEvent = new GameEvent(mp_game, gameEventData);
    connect(gameEvent, SIGNAL(finished(GameEvent*)),
            this, SLOT(gameEventFinished(GameEvent*)));
    m_gameEvents.append(gameEvent);
    step();
}


/* public slot */
void GameEventPlayer::gameEventFinished(GameEvent* gameEvent)
{
    DEBUG_BLOCK;
    Q_ASSERT(gameEvent == mp_runningEvent);
    mp_runningEvent = 0;
    if (m_mode == StepForwardMode || m_mode == StepBackwardMode) {
        updateMode(PauseMode);
    }
    step();
}

void GameEventPlayer::step()
{
    DEBUG_BLOCK;
    if (mp_runningEvent != 0) {
        qDebug("isRunning!");
        return;
    }
    switch (m_mode) {
    case StepForwardMode:
    case PlayForwardMode:
        if (m_currentGameEventIndex >= m_gameEvents.size()) {
            qDebug("isAtEnd");
            break;
        }
        mp_runningEvent = m_gameEvents[m_currentGameEventIndex++];
        mp_runningEvent->doEvent(GameEvent::ExecuteNormal);
        break;
    case StepBackwardMode:
    case PlayBackwardMode:
        if (m_currentGameEventIndex == 1) {
            m_mode = PausedMode;
            break;
        }
        mp_runningEvent = m_gameEvents[--m_currentGameEventIndex];
        mp_runningEvent->undoEvent(GameEvent::ExecuteNormal);
        break;
    case PauseMode:
        break;
    }
}

void GameEventPlayer::updateMode(Mode mode)
{
    m_mode = mode;
    emit modeUpdated(mode);
}
