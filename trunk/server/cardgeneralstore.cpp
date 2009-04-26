#include "cardgeneralstore.h"
#include "gametable.h"
#include "gamecycle.h"
#include "game.h"
#include "gameexceptions.h"

CardGeneralStore::CardGeneralStore(Game* game, int id, CardSuit cardSuit, CardRank cardRank):
        ReactionCard(game, id, CARD_GENERALSTORE, cardSuit, cardRank)
{
}

CardGeneralStore::~CardGeneralStore()
{
}

void CardGeneralStore::play()
{
    gameCycle()->assertTurn();
    assertInHand();
    mp_firstPlayer = owner();
    mp_currentPlayer = 0;
    gameTable()->playCard(this);
    gameTable()->drawIntoPublicSelection(game()->alivePlayersCount());
    requestNext();
}



void CardGeneralStore::respondCard(PlayingCard* targetCard)
{
    if (targetCard->pocket() != POCKET_SELECTION)
        throw BadCardException();
    gameTable()->drawFromPublicSelection(mp_currentPlayer,targetCard);
    game()->gameCycle().unsetResponseMode();
    requestNext();
}


void CardGeneralStore::requestNext()
{
    if (mp_currentPlayer == 0) {
        mp_currentPlayer = mp_firstPlayer;
    } else {
        mp_currentPlayer = game()->nextPlayer(mp_currentPlayer);
        if (mp_currentPlayer == mp_firstPlayer)
            return;
    }
    game()->gameCycle().setResponseMode(this, mp_currentPlayer);
}
