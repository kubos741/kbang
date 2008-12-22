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
#include "cardbang.h"
#include "player.h"

CardBang::CardBang(Game* game, int id): CardPlayable(game, id)
{

}


CardBang::~CardBang()
{
}

bool CardBang::play()
{

}

bool CardBang::play(Player *targetPlayer)
{
    /* situation check */
    if ((mp_game->playerOnTurn() != owner()) ||
        !mp_game->isBaseTurn()) return 0; // TODO: error handling

    /* distance check */
    if (mp_game->getDistance(owner(), targetPlayer) > owner()->weaponRange()) return 0; // TODO: error handling

    /* one-bang-per-turn check */
    // TODO

    CardPlayable::play();

    //    mp_game->requestReaction(targetPlayer);
    return 1;
}

bool CardBang::play(CardAbstract* targetCard)
{
}

void CardBang::noReaction(Player *reactingPlayer)
{
    reactingPlayer->modifyLifePoints(-1);
}


