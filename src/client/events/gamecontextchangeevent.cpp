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

#include "gamecontextchangeevent.h"
#include "game.h"
#include <QTimer>                   // for QTimer::singleShot()

using namespace client;

GameContextChangeEvent::GameContextChangeEvent(GameEvent* gameEvent,
                                               GameContextCmdDataPtr cmd):
        GameEventCmd(gameEvent),
        m_newContext(cmd->gameContext)
{
}

/* virtual */
GameContextChangeEvent::~GameContextChangeEvent()
{
}

/* virtual */
void GameContextChangeEvent::doEventCmd(GameEvent::ExecutionMode mode)
{
    GameEventCmd::doEventCmd(mode);
    if (m_isFirstRun) {
        m_oldContext = mp_gameEvent->game()->gameContext();
    }
    mp_gameEvent->game()->setGameContext(m_newContext);
    if (mode == GameEvent::ExecuteNormal) {
        QTimer::singleShot(100, this, SLOT(finish()));
    }
}

/* virtual */
void GameContextChangeEvent::undoEventCmd(GameEvent::ExecutionMode mode)
{
    GameEventCmd::undoEventCmd(mode);
    mp_gameEvent->game()->setGameContext(m_oldContext);
    if (mode == GameEvent::ExecuteNormal) {
        QTimer::singleShot(100, this, SLOT(finish()));
    }
}
