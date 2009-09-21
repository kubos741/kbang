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

#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include "gameevents.h"

#include <QObject>

namespace client
{

class Game;
class GameEventCmd;

/**
 * @author MacJariel
 */
class GameEvent: public QObject
{
Q_OBJECT;
public:
    enum ExecutionMode {
        ExecuteNormal,
        ExecuteFast
    };

    /**
     * Constructs a GameEvent with is related to #game.
     */
    GameEvent(Game* game, GameEventDataPtr);

    /**
     * Destroys the GameEvent.
     */
    virtual ~GameEvent();

    /**
     * Returns whether the event is running.
     */
    inline bool isRunning() const {
        return m_isRunning;
    }

    /**
     * Returns whether the event runs (will run) for the first time or not.
     */
    inline bool isFirstRun() const {
        return m_isFirstRun;
    }

    inline Game* game() const {
        return mp_game;
    }

public:
    void doEvent(ExecutionMode);
    void undoEvent(ExecutionMode);

signals:
    /**
     * This signal is emmited when the GameEvent finishes.
     * @param gameEvent Pointer to the finishing GameEvent.
     */
    void finished(GameEvent* gameEvent);

public slots:
    void gameEventCmdFinished(GameEventCmd*);

private:
    void step();

    Game*                           mp_game;
    QList<GameEventCmd*>            m_commands;
    QListIterator<GameEventCmd*>*   mp_commandsIterator;
    bool                            m_forward;

    GameEventDataPtr                mp_gameEventData;
    bool                            m_isRunning;
    bool                            m_isFirstRun;
};
}

#endif // GAMEEVENT_H
