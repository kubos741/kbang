#include "cardmustang.h"
#include "gameexceptions.h"
#include "util.h"
#include "player.h"
#include "gametable.h"
#include "gamecycle.h"

CardMustang::CardMustang(Game* game, int id):
        CardPlayable(game, id)
{
}

CardMustang::~CardMustang()
{
}

bool CardMustang::play()
{
    if (owner()->hasDuplicateOnTable(this)) {
        throw TwoSameOnTableException();
    }
    mp_game->gameTable().playOnTable(owner(), this);
}

bool CardMustang::play(Player* targetPlayer)
{
    throw BadUsageException();
}

bool CardMustang::play(CardAbstract* targetCard)
{
    throw BadUsageException();
}

void CardMustang::respondPass()
{
    NOT_REACHED();
}

void CardMustang::respondCard(CardAbstract*)
{
    NOT_REACHED();
}
