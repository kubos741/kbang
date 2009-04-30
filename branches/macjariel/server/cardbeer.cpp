#include "cardbeer.h"
#include "player.h"
#include "gametable.h"
#include "gamecycle.h"
#include "game.h"
#include "gameexceptions.h"

CardBeer::CardBeer(Game* game, int id, CardSuit cardSuit, CardRank cardRank, bool isSaloon):
        PlayingCard(game, id, CARD_BEER, cardSuit, cardRank),
        m_isSaloon(isSaloon)
{
    if (isSaloon)
        setType(CARD_SALOON);
}


CardBeer::~CardBeer()
{
}

void CardBeer::play()
{
    gameCycle()->assertTurn();
    assertInHand();
    Player* player = owner();
    gameTable()->playerPlayCard(this);
    player->modifyLifePoints(1, 0);
    if (m_isSaloon) {
        for (Player* p = game()->nextPlayer(player);
             p != player;
             p = game()->nextPlayer(p)) {
            p->modifyLifePoints(1, 0);
        }
    }
}


BeerRescue::BeerRescue(Game* game):
        QObject(game),
        mp_game(game)
{
}

void BeerRescue::respondPass()
{
    mp_game->gameCycle().unsetResponseMode();
    mp_target->modifyLifePoints(0, mp_attacker, 1);
}

void BeerRescue::respondCard(PlayingCard* targetCard)
{
    targetCard->assertInHand();
    if (targetCard->type() == CARD_BEER) {
            m_lifePointsToSave--;
            mp_game->gameTable().playerPlayCard(targetCard);
            if (m_lifePointsToSave == 0) {
                mp_game->gameCycle().unsetResponseMode();
                mp_target->modifyLifePoints(1, mp_attacker);
            }
            return;
    }
    throw BadCardException();
}

void BeerRescue::allowSaveWithBeer(Player* attacker, Player* target, int lifePointsToSave)
{
    mp_attacker = attacker;
    mp_target = target;
    m_lifePointsToSave = lifePointsToSave;
    mp_game->gameCycle().setResponseMode(this, mp_target);
}
