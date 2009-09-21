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

#include "gameeventcmd.h"
#include "gameevent.h"

using namespace client;

GameEventCmd::GameEventCmd(GameEvent* gameEvent):
        QObject(gameEvent),
        mp_gameEvent(gameEvent),
        m_isFirstRun(1),
        m_isRunning(0)
{
}

/* virtual */
GameEventCmd::~GameEventCmd()
{
}

bool GameEventCmd::isRunning() const
{
    return m_isRunning;
}

/* virtual */
void GameEventCmd::doEventCmd(GameEvent::ExecutionMode mode)
{
    Q_ASSERT(m_isRunning == 0);
    m_isRunning = (mode == GameEvent::ExecuteNormal);
}

/* virtual */
void GameEventCmd::undoEventCmd(GameEvent::ExecutionMode mode)
{
    Q_ASSERT(m_isRunning == 0);
    m_isRunning = (mode == GameEvent::ExecuteNormal);
}

/* virtual */
void GameEventCmd::finish()
{
    m_isRunning = 0;
    emit finished(this);
}
