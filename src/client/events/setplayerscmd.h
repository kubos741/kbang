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

#ifndef SETPLAYERSCMD_H
#define SETPLAYERSCMD_H

#include "gameeventcmd.h"

namespace client
{

class SetPlayersCmd: public GameEventCmd
{
Q_OBJECT;
public:
    SetPlayersCmd(GameEvent*, SetPlayersCmdDataPtr);
    virtual ~SetPlayersCmd();
    virtual void doEventCmd(GameEvent::ExecutionMode);
    virtual void undoEventCmd(GameEvent::ExecutionMode);


private:
    SetPlayersCmdDataPtr    mp_doCmd;
};
}
#endif // SETPLAYERSCMD_H
