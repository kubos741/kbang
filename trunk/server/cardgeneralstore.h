#ifndef CARDGENERALSTORE_H
#define CARDGENERALSTORE_H

#include "reactioncard.h"

class CardGeneralStore : public ReactionCard
{
public:
    CardGeneralStore(Game* game, int id, CardSuit, CardRank);
    ~CardGeneralStore();
    virtual void play();
    virtual void respondCard(PlayingCard* targetCard);
private:
    void requestNext();

    Player* mp_firstPlayer;
    Player* mp_currentPlayer;

};

#endif // CARDGENERALSTORE_H
