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

#ifndef GAMEEVENTCMD_H
#define GAMEEVENTCMD_H

#include "gameevent.h"
#include <QObject>

namespace client
{

class GameEventCmd: public QObject
{
Q_OBJECT;
public:
    /**
     * Constructs a GameEventCmd.
     */
    GameEventCmd(GameEvent*);

    /**
     * Destroys the GameEventCmd.
     */
    virtual ~GameEventCmd();

    /**
     * Returns, whether the game event is running.
     */
    bool isRunning() const;

public slots:
    /**
     * Sets the GameEventCmd to running state. You can reimplement this method,
     * but make sure you call the original one in your reimplementation.
     */
    virtual void doEventCmd(GameEvent::ExecutionMode);

    virtual void undoEventCmd(GameEvent::ExecutionMode);

    /**
     * Sets the GameEventCmd to not running state and emits the
     * finished(GameEventCmd*) signal.
     */
    virtual void finish();

signals:
    /**
     * This signal is emmited when the GameEventCmd finishes.
     * @param gameEvent Pointer to the finishing GameEventCmd.
     */
    void finished(GameEventCmd* gameEvent);

protected:
    GameEvent*  mp_gameEvent;
    bool        m_isFirstRun;

private:
    bool        m_isRunning;
};
}

#endif // GAMEEVENTCMD_H
