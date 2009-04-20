#ifndef CARDBEER_H
#define CARDBEER_H

#include "playingcard.h"

class Player;

class CardBeer : public PlayingCard
{
Q_OBJECT;
public:
    CardBeer(Game* game, int id, CardSuit, CardRank);
    ~CardBeer();

    virtual void play();
};

#endif // CARDBEER_H
