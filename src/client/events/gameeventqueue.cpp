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
#if 0
#include "gameeventqueue.h"
#include "gameevent.h"

using namespace client;

GameEventQueue::GameEventQueue(QObject* parent):
        QObject(parent),
        m_paused(0),
        m_eventOnHold(0)
{
}

/* virtual */
GameEventQueue::~GameEventQueue()
{
}

void
GameEventQueue::add(GameEvent* gameEvent)
{
    if (m_queue.isEmpty()) {
        m_queue.enqueue(gameEvent);
        runGameEvent();
    } else {
        m_queue.enqueue(gameEvent);
    }
}


void
GameEventQueue::pause()
{
    m_paused = 1;
}

void
GameEventQueue::resume()
{
    m_paused = 0;
    if (m_eventOnHold) {
        m_eventOnHold = 0;
        runGameEvent();
    }
}

#if 0
void GameEventQueue::clear()
{
    m_aboutToDelete = 1;
    if (!m_queue.isEmpty() && m_queue.head()->isRunning()) {
        m_queue.head()->stop();
    }
}
#endif


/* slot */ void
GameEventQueue::onGameEventFinished(GameEvent* gameEvent)
{
    Q_ASSERT(gameEvent == m_queue.head());
    Q_UNUSED(gameEvent);
    m_queue.dequeue()->deleteLater();
    if (!m_queue.isEmpty()) {
        runGameEvent();
    }
}

void
GameEventQueue::runGameEvent()
{
    if (m_paused) {
        m_eventOnHold = 1;
        return;
    }
    GameEvent* gameEvent = m_queue.head();
    Q_ASSERT(!gameEvent->isRunning());
    connect(gameEvent, SIGNAL(finished(GameEvent*)),
            this,      SLOT(onGameEventFinished(GameEvent*)));
    gameEvent->run();
}
#endif
