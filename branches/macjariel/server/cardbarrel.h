#ifndef CARDBARREL_H
#define CARDBARREL_H

#include "tablecard.h"

class CardBarrel : public TableCard
{
Q_OBJECT;
public:
    CardBarrel(Game *game, int id, CardSuit, CardRank);
    virtual ~CardBarrel();

    virtual void play();
    virtual void registerPlayer(Player* player);
    virtual void unregisterPlayer(Player* player);

    bool check();

    static bool checkBarrel(PlayingCard*);
};


#endif // CARDBARREL_H
