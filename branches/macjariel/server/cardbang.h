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
#ifndef CARDBANG_H
#define CARDBANG_H

#include <cardplayable.h>

/**
 * This class represents the Bang! cards.
 * @author MacJariel <MacJariel@gmail.com>
 */
class CardBang: public CardPlayable
{
Q_OBJECT
public:
    CardBang(Game* game, int id);
    ~CardBang();

    /**
     * Bang! card can be played without specifying target player only in
     * certain situations:
     *   * player is in Duel                    (NIY)
     *   * player responds to Indians card      (NIY)
     */
    virtual bool play();
    virtual bool play(Player* targetPlayer);
    virtual bool play(CardAbstract* targetCard);

    virtual QString type() const { return "bang"; }

    virtual void noReaction(Player* reactingPlayer);
};

#endif
