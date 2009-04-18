#include "cardbeer.h"
#include "gameexceptions.h"
#include "util.h"
#include "player.h"
#include "gamecycle.h"

CardBeer::CardBeer(Game* game, int id):
        CardPlayable(game, id)
{
}

CardBeer::~CardBeer()
{
}

bool CardBeer::play()
{
    CardPlayable::play();
    owner()->modifyLifePoints(1);
    mp_game->gameCycle().clearPlayedCards();
}

bool CardBeer::play(Player* targetPlayer)
{
    throw BadUsageException();
}

bool CardBeer::play(CardAbstract* targetCard)
{
    throw BadUsageException();
}

void CardBeer::respondPass()
{
    NOT_REACHED();
}

void CardBeer::respondCard(CardAbstract*)
{
    NOT_REACHED();
}
