#include "cardbeer.h"
#include "player.h"
#include "gametable.h"

CardBeer::CardBeer(Game* game, int id, CardSuit cardSuit, CardRank cardRank):
        PlayingCard(game, id, CARD_BEER, cardSuit, cardRank)
{
}

CardBeer::~CardBeer()
{
}

void CardBeer::play()
{
    gameTable()->playCard(this);
    owner()->modifyLifePoints(1);
}
