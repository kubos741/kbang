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
#ifndef WEAPONCARD_H
#define WEAPONCARD_H

#include "cards/tablecard.h"

/**
 * The WeaponCard represents any weapon card.
 * @author MacJariel
 */
class WeaponCard: public TableCard
{
Q_OBJECT
public:
    enum Weapon {
        InvalidWeapon = 0,
        Volcanic = 1,
        Schofield = 2,
        Remington = 3,
        Carabine = 4,
        Winchester = 5
    };

    /**
     * Constructs a weapon card. The concrete card is created according to the range
     * parameter:
     *  * 1 - Volcanic
     *  * 2 - Schofield
     *  * 3 - Remington
     *  * 4 - Carabine
     *  * 5 - Winchester
     */
    WeaponCard(Game* game, CardId, Weapon, CardSuit, CardRank);
    virtual ~WeaponCard();

    virtual void play();

    virtual void registerPlayer(Player* player);
    virtual void unregisterPlayer(Player* player);

private:
    Weapon  m_weapon;
    int     m_range;

    static PlayingCardName playingCardName(Weapon);
    static int range(Weapon);
};

#endif
