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
#ifndef PUBLICPLAYERVIEW_H
#define PUBLICPLAYERVIEW_H

#include "common.h"

class Player;

/**
 *
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
*/
class PublicPlayerView {
friend class Player;
protected:
    PublicPlayerView(Player* player);
    virtual ~PublicPlayerView();
private:
    PublicPlayerView(const PublicPlayerView&);
    PublicPlayerView& operator=(const PublicPlayerView&);


public:
    inline QString name() const;

    inline bool isAlive() const
    {
        // TODO
        return 0;
    }

    inline bool isSheriff() const
    {
        // TODO
        return 0;
    }

    /**
     * Returns the role of the player. In case
     * the player is still alive and is not sheriff,
     * the unknown role is returned.
     */
    virtual int role() const
    {
        // TODO
        return 0;
    }

    inline int lifePoints() const
    {
        // TODO
        return 0;
    }

    inline int numCardsInHand() const
    {
        // TODO
        return 0;
    }

    // write method cardsOnTable

private:
    Player* mp_player;
};

#endif
