#ifndef CARDBEER_H
#define CARDBEER_H

#include "playingcard.h"
#include "reactionhandler.h"

class Player;

class CardBeer : public PlayingCard
{
Q_OBJECT;
public:
    CardBeer(Game* game, int id, CardSuit, CardRank, bool isSaloon);
    ~CardBeer();

    virtual void play();
private:
    bool m_isSaloon;
};

class BeerRescue: public QObject, public ReactionHandler
{
Q_OBJECT
public:
    BeerRescue(Game* game);
    virtual void respondPass();
    virtual void respondCard(PlayingCard* targetCard);

    void allowSaveWithBeer(Player* attacker, Player* target, int lifePointsToSave);

private:
    Player* mp_attacker;
    Player* mp_target;
    int     m_lifePointsToSave;
    Game*   mp_game;
};

#endif // CARDBEER_H
