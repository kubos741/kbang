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

#include <QObject>

namespace client
{

class Game;

/**
 * The GameEvent class provides base functionality and interface for game
 * events. Game events come from the server through the parser to the client
 * and they are then applied to the game, by changing something. Some of
 * the game events take some time, before they finnish. Because of that
 * game events are put into queue after they are received, and then they
 * are dequeued, one after one.
 * @see GameEventHandler
 * @see GameEventQueue
 * @author MacJariel
 */
class GameEvent: public QObject
{
Q_OBJECT;
public:
    /**
     * Constructs a GameEvent with is related to <i>game</i>.
     */
    GameEvent(Game* game);

    /**
     * Destroys the GameEvent.
     */
    virtual ~GameEvent();

    /**
     * Returns, whether the game event is running.
     */
    bool isRunning() const;

public slots:
    /**
     * Sets the GameEvent to running state. You can reimplement this method,
     * but make sure you call the original one in your reimplementation.
     */
    virtual void run();

    /**
     * Sets the GameEvent to not running state and emits the
     * finished(GameEvent*) signal.
     */
    virtual void finish();

signals:
    /**
     * This signal is emmited when the GameEvent finishes.
     * @param gameEvent Pointer to the finishing GameEvent.
     */
    void finished(GameEvent* gameEvent);

protected:
    inline Game* game() {
        return mp_game;
    }

private:
    Game*   mp_game;
    bool    m_isRunning;
};
}

#endif // GAMEEVENT_H
