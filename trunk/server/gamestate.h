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
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "player.h"
#include "gamearbiter.h"
#include <QtCore>

class Client;

enum {  STATE_AWAITING = 1, // Players are connecting
        STATE_PREGAME  = 2, // The number of players is fixed - time for choosing roles
        STATE_GAME     = 3  // Game is ready
};



/**
 * The GameState class is the major class that control a bang game. Every bang game running
 * on the server has just one instance of this class. This class stores all global information
 * about the game and thus must not be accessible to player controllers, because they could be
 * cheating.
 * The bang game is created.
 * @author MacJariel <macjariel@users.sourceforge.net>
 */
class GameState : public QObject
{
Q_OBJECT
public:
    GameState(QObject *parent, const Client& client, int maxPlayers, int AIPlayers);
    ~GameState();

private:
    QList<Player*> m_players;
    GameArbiter m_arbiter;
    int m_state;

};

#endif
