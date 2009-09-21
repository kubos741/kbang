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
#include "cards/original/weaponcard.h"
#include "gameexceptions.h"
#include "player.h"
#include "gametable.h"
#include "gamecycle.h"

WeaponCard::WeaponCard(Game* game, CardId id, Weapon weapon,
                       CardSuit suit, CardRank rank):
        TableCard(game, id, WeaponCard::playingCardName(weapon),
                  suit, rank),
        m_weapon(weapon),
        m_range(WeaponCard::range(weapon)
{
}

/* virtual */
WeaponCard::~WeaponCard()
{
}

void WeaponCard::play()
{
    gameCycle()->assertTurn();
    assertInHand();

    foreach(PlayingCard* card, owner()->table()) {
        WeaponCard* weaponCard = qobject_cast<WeaponCard*>(card);
        if (weaponCard == 0) {
            continue;
        }
        if (weaponCard->type() == type()) {
            throw TwoSameOnTableException();
        }
        weaponCard->discard();
    }
    gameTable()->playerPlayCardOnTable(this);
}

void WeaponCard::registerPlayer(Player* player)
{
    player->setWeaponRange(m_range);
    if (m_range == 1) {
        player->modifyUnlimitedBangs(1);
    }
}

void WeaponCard::unregisterPlayer(Player* player)
{
    player->setWeaponRange(1);
    if (m_range == 1) {
        player->modifyUnlimitedBangs(-1);
    }
}

PlayingCardName
WeaponCard::playingCardName(Weapon weapon)
{
    switch(weapon) {
    case Volcanic:      return CARD_VOLCANIC;
    case Schofield:     return CARD_SCHOFIELD;
    case Remington:     return CARD_REMINGTON;
    case Carabine:      return CARD_CARABINE;
    case Winchester:    return CARD_WINCHESTER;
    default:            break;
    }
    return CARD_UNKNOWN;
}

int
WeaponCard::range(Weapon weapon)
{
    switch(weapon) {
    case Volcanic:      return 1;
    case Schofield:     return 2;
    case Remington:     return 3;
    case Carabine:      return 4;
    case Winchester:    return 5;
    default:            break;
    }
    return 0;
}
