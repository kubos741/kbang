#include "cardmultishoot.h"
#include "gametable.h"
#include "gamecycle.h"
#include "game.h"
#include "player.h"
#include "gameexceptions.h"

CardMultiShoot::CardMultiShoot(Game* game, int id, CardMultiShoot::Type type, CardSuit cardSuit, CardRank cardRank):
        ReactionCard(game, id, CARD_UNKNOWN, cardSuit, cardRank),
        m_type(type),
        mp_requestedPlayer(0)
{
    switch(m_type) {
    case Indians:
        setType(CARD_INDIANS);
        break;
    case Gatling:
        setType(CARD_GATLING);
        break;
    }
}

CardMultiShoot::~CardMultiShoot()
{
}

void CardMultiShoot::play()
{
    gameCycle()->assertTurn();
    mp_shootingPlayer = owner();
    mp_requestedPlayer = owner();
    gameTable()->playerPlayCard(this);
    requestNext();
}

void CardMultiShoot::respondPass()
{
    game()->gameCycle().unsetResponseMode();
    mp_requestedPlayer->modifyLifePoints(-1, mp_shootingPlayer);
    requestNext();
}

void CardMultiShoot::respondCard(PlayingCard* targetCard)
{
    switch(targetCard->type()) {
    case CARD_BANG:
        if (m_type != Indians)
            break;
        targetCard->assertInHand();
        gameTable()->playerPlayCard(targetCard);
        game()->gameCycle().unsetResponseMode();
        requestNext();
        return;

    case CARD_MISSED:
        if (m_type != Gatling)
            break;
        targetCard->assertInHand();
        gameTable()->playerPlayCard(targetCard);
        game()->gameCycle().unsetResponseMode();
        requestNext();
        return;

/*
    case CARD_BEER:
        if (mp_requestedPlayer->lifePoints() == 1) {
            mp_requestedPlayer->modifyLifePoints(-1, mp_shootingPlayer, 1);
            gameTable()->playCard(targetCard);
            mp_requestedPlayer->modifyLifePoints(1, mp_shootingPlayer, 1);
            game()->gameCycle().unsetResponseMode();
            requestNext();
            return;
        }
        break;
*/

    default:
        break;
    }
    throw BadCardException();
}

ReactionType CardMultiShoot::reactionType() const
{
    switch(m_type) {
    case Indians:
        return REACTION_INDIANS;
    case Gatling:
        return REACTION_GATLING;
    }
}

void CardMultiShoot::requestNext()
{
    mp_requestedPlayer = game()->nextPlayer(mp_requestedPlayer);
    if (mp_requestedPlayer == mp_shootingPlayer) return;
    game()->gameCycle().setResponseMode(this, mp_requestedPlayer);
}
