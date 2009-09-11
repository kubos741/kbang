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

#include "gameevent.h"

using namespace client;

GameEvent::GameEvent(QObject* parent):
        QObject(parent),
        m_isRunning(0)
{
}

/* virtual */
GameEvent::~GameEvent()
{
}

bool
GameEvent::isRunning() const
{
    return m_isRunning;
}

/* virtual */ void
GameEvent::run()
{
    m_isRunning = 1;
}

/* virtual */ void
GameEvent::finish()
{
    m_isRunning = 0;
    emit finished(this);
}
