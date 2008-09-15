/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
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

#include "abstractplayerctrl.h"
#include "player.h"
#include "publicgameview.h"

AbstractPlayerCtrl::AbstractPlayerCtrl():
QObject(0), mp_privatePlayerView(0), mp_publicGameView(0), mp_playerActions(0),
m_attached(0)
{
    qDebug() << "Creating AbstractPlayerCtrl" << this;
}

void AbstractPlayerCtrl::attachPlayer(const PrivatePlayerView* privatePlayerView,
                                      const PublicGameView*    publicGameView,
                                      const PlayerActions*     playerActions)
{
    Q_ASSERT(m_attached == 0);
    mp_privatePlayerView = privatePlayerView;
    mp_publicGameView = publicGameView;
    mp_playerActions = playerActions;
    m_attached = 1;
}

void AbstractPlayerCtrl::detachPlayer()
{
    mp_privatePlayerView = 0;
    mp_publicGameView = 0;
    mp_playerActions = 0;
    m_attached = 0;
}

AbstractPlayerCtrl::~ AbstractPlayerCtrl()
{
    qDebug() << "Destroying AbstractPlayerCtrl" << this;
}



int AbstractPlayerCtrl::gameId() const
{
    if (!m_attached) return 0;
    return mp_publicGameView->gameId();
}

