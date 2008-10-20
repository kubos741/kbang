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
#include "charactercard.h"


//CharacterCardList CharacterCard::sm_characterBank;

CharacterCard::CharacterCard()
        : AbstractCard()
{
}


CharacterCard::~CharacterCard()
{
}

CharacterCardList CharacterCard::getCharacterCards()
{
    CharacterCardList list;
    CharacterCard* card;
    card = new CharacterCard();
    card->setName("Bart Cassidy");
    card->m_maxLifePoints = 4;
    list.append(card);

    card = new CharacterCard();
    card->setName("Black Jack");
    card->m_maxLifePoints = 4;
    list.append(card);

    card = new CharacterCard();
    card->setName("Calamity Janet");
    card->m_maxLifePoints = 4;
    list.append(card);

    card = new CharacterCard();
    card->setName("El Gringo");
    card->m_maxLifePoints = 4;
    list.append(card);
    return list;
}

