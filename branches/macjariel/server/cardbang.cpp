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
#include "gametable.h"
#include "game.h"

CardBang::CardBang(Game* game, int id, CardSuit cardSuit, CardRank cardRank):
        ReactionCard(game, id, CARD_BANG, cardSuit, cardRank),
        mp_attackedPlayer(0)
{
}


CardBang::~CardBang()
{
}

void CardBang::play(Player *targetPlayer)
{
    gameCycle()->assertTurn();
    assertInHand();

    /* don't allow shoot yourself */
    if (owner() == targetPlayer)
        throw BadTargetPlayerException();

    /* distance check */
    if (game()->getDistance(owner(), targetPlayer) > owner()->weaponRange())
        throw PlayerOutOfRangeException();

    /* one-bang-per-turn check */
    if (!owner()->canPlayBang())
        throw OneBangPerTurnException();

    owner()->onBangPlayed();
    mp_attackingPlayer = owner();
    gameTable()->playCard(this);
    game()->gameCycle().setResponseMode(this, targetPlayer);
    mp_attackedPlayer = targetPlayer;
}

void CardBang::respondPass()
{
    Q_ASSERT(mp_attackedPlayer != 0);
    /// @todo announce pass
    game()->gameCycle().unsetResponseMode();
    mp_attackedPlayer->modifyLifePoints(-1, mp_attackingPlayer);

}

void CardBang::respondCard(PlayingCard* targetCard)
{
    targetCard->assertInHand();
    switch(targetCard->type()) {
    case CARD_MISSED:
        game()->gameCycle().unsetResponseMode();
        gameTable()->playCard(targetCard);

        return;
/*    case CARD_BEER:
        if (mp_attackedPlayer->lifePoints() == 1) {
            mp_attackedPlayer->modifyLifePoints(-1, mp_attackingPlayer, 1);
            gameTable()->playCard(targetCard);
            mp_attackedPlayer->modifyLifePoints(1, mp_attackingPlayer, 1);
            game()->gameCycle().unsetResponseMode();
            return;
        }
*/
    default:
        break;
    }
    throw BadCardException();
}


