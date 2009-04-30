#include "cardtaker.h"
#include "player.h"
#include "gamecycle.h"
#include "gametable.h"
#include "gameexceptions.h"
#include "game.h"

CardTaker::CardTaker(Game* game, int id, CardTaker::Type type, CardSuit cardSuit, CardRank cardRank):
        PlayingCard(game, id, CARD_UNKNOWN, cardSuit, cardRank),
        m_type(type)
{
    if (m_type == Panic)
        setType(CARD_PANIC);
    else
        setType(CARD_CATBALOU);
}

CardTaker::~CardTaker()
{
}

void CardTaker::play(Player* targetPlayer)
{
    gameCycle()->assertTurn();
    assertInHand();

    /* don't allow steel yourself */
    if (owner() == targetPlayer)
        throw BadTargetPlayerException();

     PlayingCard* targetCard = targetPlayer->getRandomCardFromHand();
     if (targetCard == 0)
        throw BadTargetPlayerException();

     play(targetCard);
}

void CardTaker::play(PlayingCard* targetCard)
{
    gameCycle()->assertTurn();
    assertInHand();

    Player* o = owner();

    /* don't allow steel yourself */
    if (owner() == targetCard->owner())
        throw BadTargetCardException();

    if (m_type == Panic) {
        /* distance check */
        if (game()->getDistance(owner(), targetCard->owner()) > 1)
            throw PlayerOutOfRangeException();
        gameTable()->playerPlayCard(this, targetCard);
        gameTable()->playerStealCard(o, targetCard);
    } else {
        gameTable()->playerPlayCard(this, targetCard);
        gameTable()->cancelCard(targetCard, o);
    }
}

