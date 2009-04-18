#ifndef CARDMUSTANG_H
#define CARDMUSTANG_H

#include "cardplayable.h"

class Player;

class CardMustang : public CardPlayable
{
Q_OBJECT;
public:
    CardMustang(Game* game, int id);
    ~CardMustang();

    virtual bool play();
    virtual bool play(Player* targetPlayer);
    virtual bool play(CardAbstract* targetCard);

    virtual CardType type() const { return CARD_MUSTANG; }
    virtual QString typeStr() const { return "mustang"; } /// \deprecated

    virtual void respondPass();
    virtual void respondCard(CardAbstract* targetCard);
};

#endif // CARDMUSTANG_H
