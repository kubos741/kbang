#ifndef CARDMULTISHOOT_H
#define CARDMULTISHOOT_H

#include "reactioncard.h"

class Player;

class CardMultiShoot : public ReactionCard
{
Q_OBJECT;
public:
    enum Type {
        Indians,
        Gatling
    };
    CardMultiShoot(Game* game, int id, Type type, CardSuit, CardRank);
    ~CardMultiShoot();
    virtual void play();

    virtual void respondPass();
    virtual void respondCard(PlayingCard* targetCard);

    virtual ReactionType reactionType() const;

private:
    void requestNext();

    Type    m_type;
    Player* mp_shootingPlayer;
    Player* mp_requestedPlayer;
};


#endif // CARDMULTISHOOT_H
