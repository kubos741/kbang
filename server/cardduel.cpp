#include "cardduel.h"
#include "gametable.h"
#include "gamecycle.h"
#include "game.h"
#include "player.h"
#include "gameexceptions.h"

CardDuel::CardDuel(Game* game, int id, CardSuit cardSuit, CardRank cardRank):
        ReactionCard(game, id, CARD_DUEL, cardSuit, cardRank)
{
}

CardDuel::~CardDuel()
{
}

void CardDuel::play(Player* targetPlayer)
{
    gameCycle()->assertTurn();
    assertInHand();

    /* don't allow shoot yourself */
    if (owner() == targetPlayer)
        throw BadTargetPlayerException();

    // the positions will swap in requestNext(), therefore
    // are swapped here
    mp_requestedPlayer = owner();
    mp_shootingPlayer  = targetPlayer;

    gameTable()->playCard(this);
    requestNext();
}

void CardDuel::respondPass()
{
    game()->gameCycle().unsetResponseMode();
    mp_requestedPlayer->modifyLifePoints(-1, mp_shootingPlayer);
}

void CardDuel::respondCard(PlayingCard* targetCard)
{
    targetCard->assertInHand();
    switch(targetCard->type()) {
    case CARD_BANG:
        gameTable()->playCard(targetCard);
        game()->gameCycle().unsetResponseMode();
        requestNext();
        return;
/*
    case CARD_BEER:
        if (mp_requestedPlayer->lifePoints() == 1) {
            mp_requestedPlayer->modifyLifePoints(-1, mp_shootingPlayer, 1);
            gameTable()->playCard(targetCard);
            mp_requestedPlayer->modifyLifePoints(1, mp_shootingPlayer, 1);
            game()->gameCycle().unsetResponseMode();
            return;
        }
        break;
*/

    default:
        break;
    }
    throw BadCardException();
}

void CardDuel::requestNext()
{
    Player* tmp = mp_requestedPlayer;
    mp_requestedPlayer = mp_shootingPlayer;
    mp_shootingPlayer = tmp;
    game()->gameCycle().setResponseMode(this, mp_requestedPlayer);
}


