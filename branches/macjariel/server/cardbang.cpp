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
#include "gamecycle.h"
#include "gameexceptions.h"
#include "cardmissed.h"
#include "cardbeer.h"
#include "gametable.h"

CardBang::CardBang(Game* game, int id):
        CardPlayable(game, id),
        mp_attackedPlayer(0)
{

}


CardBang::~CardBang()
{
}

bool CardBang::play()
{
    throw BadUsageException();
    return 0;
}

bool CardBang::play(Player *targetPlayer)
{

    /* situation check */
    if (!mp_game->gameCycle().isTurn())
        throw BadGameStateException();


    /* distance check */
    if (mp_game->getDistance(owner(), targetPlayer) > owner()->weaponRange())
        throw BadPlayerException(targetPlayer->id()); // TODO: other exception maybe

    /* one-bang-per-turn check */
    if (!owner()->canPlayBang())
        throw OneBangPerTurnException();

    owner()->onBangPlayed();
    CardPlayable::play();
    mp_game->gameCycle().requestResponse(targetPlayer);
    mp_attackedPlayer = targetPlayer;
    return 1;
}

bool CardBang::play(CardAbstract* targetCard)
{
    Q_UNUSED(targetCard);
    throw BadUsageException();
    return 0;
}

void CardBang::respondPass()
{
    Q_ASSERT(mp_attackedPlayer != 0);
    qDebug() << "RESPOND PASS";
    mp_attackedPlayer->modifyLifePoints(-1); // TODO: abstract this - for abilities
    mp_game->gameCycle().clearPlayedCards();
}

void CardBang::respondCard(CardAbstract* targetCard)
{
    CardMissed* cardMissed = qobject_cast<CardMissed*>(targetCard);
    if (cardMissed != 0) {
        mp_game->gameTable().playCard(targetCard->owner(), cardMissed);
        mp_game->gameCycle().clearPlayedCards();
        return;
    }
    CardBeer* cardBeer = qobject_cast<CardBeer*>(targetCard);
    if (cardBeer != 0 && mp_attackedPlayer->lifePoints() == 1) {
        mp_attackedPlayer->modifyLifePoints(-1);
        mp_game->gameCycle().clearPlayedCards();
        mp_game->gameTable().playCard(targetCard->owner(), cardBeer);
        mp_attackedPlayer->modifyLifePoints(1);
        mp_game->gameCycle().clearPlayedCards();
        return;
    }
    throw BadCardException();
}


