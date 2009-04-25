#ifndef CARDJAIL_H
#define CARDJAIL_H

#include "tablecard.h"

class CardJail : public TableCard
{
public:
    CardJail(Game *game, int id, CardSuit, CardRank);
    ~CardJail();

    virtual void play();
    virtual void play(Player* targetPlayer);

    virtual void registerPlayer(Player* player);
    virtual void unregisterPlayer(Player* player);

    static bool checkJail(PlayingCard*);

private:
    static const int PredrawCheck = 10;
};

#endif // CARDJAIL_H
