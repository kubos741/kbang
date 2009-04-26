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
#ifndef GAMEARBITER_H
#define GAMEARBITER_H

#include <QObject>

class Player;
class AbstractPlayerCtrl;
class CharacterCard;



/**
 * The GameArbiter class represents a imaginary "person"
 * that controls the game.
 *
 * @author MacJariel <MacJariel@gmail.com>
 */
class GameArbiter : public QObject
{
    Q_OBJECT

public:
    GameArbiter(QObject *parent = 0);
    /**
     * The createPlayer method is called whenever someone
     * requests to play the game, although this method can
     * be called only before the game starts.
     */
    Player* createPlayer(const AbstractPlayerCtrl& playerController);


    ~GameArbiter();
};

#endif
