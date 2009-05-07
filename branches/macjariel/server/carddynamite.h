#ifndef CARDDYNAMITE_H
#define CARDDYNAMITE_H

#include "tablecard.h"

class CardDynamite : public TableCard
{
public:
    CardDynamite(Game *game, int id, CardSuit, CardRank);
    virtual ~CardDynamite();

    virtual void play();
    void checkResult(bool result);
    virtual void registerPlayer(Player* player);
    virtual void unregisterPlayer(Player* player);

    static bool checkDynamite(PlayingCard*);
private:
    static const int PredrawCheck = 20;
};

#endif // CARDDYNAMITE_H
