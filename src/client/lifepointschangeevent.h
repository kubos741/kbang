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
//#ifndef LIFEPOINTSCHANGEEVENT_H
#define LIFEPOINTSCHANGEEVENT_H

#include "gameevent.h"
#include "gametypes.h"

namespace client
{
/**
 * The LifePointsChangeEvent class represents the lifepoints-change game event.
 * @author MacJariel
 */
class LifePointsChangeEvent: public GameEvent
{
Q_OBJECT;
public:
    /**
     * Constructs a LifePointsChangeEvent related to <i>game</i>, according to
     * given <i>playerId</i> and <i>lifePoints</i>.
     */
    LifePointsChangeEvent(Game* game, PlayerId playerId, int lifePoints);

    /**
     * Destroys the LifePointsChangeEvent.
     */
    virtual ~LifePointsChangeEvent();

    /**
     * Runs the event.
     */
    virtual void run();

private:
    PlayerId m_playerId;
    int m_lifePoints;
};
}
#endif // LIFEPOINTSCHANGEEVENT_H
