#include "gameevent.h"
#include "game.h"

using namespace client;

GameEvent::GameEvent(Game* game):
        QObject(game),
        mp_game(game)
{
}

GameEvent::~GameEvent()
{
}

bool GameEvent::isReadyRun()
{
    return 1;
}
