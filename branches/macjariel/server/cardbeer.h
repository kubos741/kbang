#ifndef CARDBEER_H
#define CARDBEER_H

#include "cardplayable.h"

class Player;

class CardBeer : public CardPlayable
{
Q_OBJECT;
public:
    CardBeer(Game* game, int id);
    ~CardBeer();

    /**
     * Bang! card can be played without specifying target player only in
     * certain situations:
     *   * player is in Duel                    (NIY)
     *   * player responds to Indians card      (NIY)
     */
    virtual bool play();
    virtual bool play(Player* targetPlayer);
    virtual bool play(CardAbstract* targetCard);

    virtual CardType type() const { return CARD_BEER; }
    virtual QString typeStr() const { return "beer"; } /// \deprecated

    virtual void respondPass();
    virtual void respondCard(CardAbstract* targetCard);

private:
    Player* mp_attackedPlayer;


};

#endif // CARDBEER_H
