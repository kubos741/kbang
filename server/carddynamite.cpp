#include "carddynamite.h"
#include "gamecycle.h"
#include "gameexceptions.h"
#include "gametable.h"
#include "game.h"
#include "player.h"

CardDynamite::CardDynamite(Game *game, int id, CardSuit suit, CardRank rank):
        TableCard(game, id, CARD_DYNAMITE, suit, rank)
{
}

CardDynamite::~CardDynamite()
{
}

void CardDynamite::play()
{
    if (gameCycle()->isDraw()) {
        assertOnTable();
        owner()->predrawCheck(PredrawCheck);
        bool check = gameTable()->checkCard(owner(), this, *CardDynamite::checkDynamite);
        if (check) { // luck
            gameTable()->playOnTable(this, game()->nextPlayer(owner()));
        } else {
            Player* o = owner();
            gameTable()->playerDiscardCard(this);
            o->modifyLifePoints(-3, 0);
        }
    } else {
        gameCycle()->assertTurn();
        assertInHand();
        if (owner()->hasIdenticalCardOnTable(this)) {
            throw TwoSameOnTableException();
        }
        gameTable()->playOnTable(this);
    }
}


void CardDynamite::registerPlayer(Player* player)
{
   player->registerPredrawCheck(PredrawCheck);
}

void CardDynamite::unregisterPlayer(Player* player)
{
   player->unregisterPredrawCheck(PredrawCheck);
}


bool CardDynamite::checkDynamite(PlayingCard* card)
{
    return  (card->suit() != SUIT_SPADES || card->rank() > 9);
}
