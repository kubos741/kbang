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
#ifndef GAMEEVENTQUEUE_H
#define GAMEEVENTQUEUE_H

#include <QObject>
#include <QQueue>

namespace client
{
class GameEvent;

/**
 * The GameEventQueue class provides a queue for holding GameEvents that are
 * about to be executed.
 * @author MacJariel
 */
class GameEventQueue: public QObject
{
Q_OBJECT
public:
    /**
     * Constructs a GameEventQueue which is child of <i>parent</i>.
     */
    GameEventQueue(QObject* parent);

    /**
     * Destroys the GameEventQueue.
     */
    ~GameEventQueue();

    /**
     * Enqueues a new GameEvent. As soon as all GameEvents before this one
     * finish, this GameEvent is run.
     */
    void add(GameEvent*);

    /**
     * Pauses the dequeuing of GameEvents.
     */
    void pause();

    /**
     * Resumes the dequeuing of GameEvents.
     */
    void resume();

public slots:
    void onGameEventFinished(GameEvent*);

private:
    void runGameEvent();

private:
    QQueue<GameEvent*> m_queue;
    bool m_paused;
    bool m_eventOnHold;
};
}

#endif // GAMEEVENTQUEUE_H
