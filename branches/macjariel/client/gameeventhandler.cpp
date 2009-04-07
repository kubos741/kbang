
#include "gameeventhandler.h"
#include "gameeventqueue.h"
#include "game.h"

#include "cardmovementevent.h"
#include "gamefocuschangeevent.h"

using namespace client;

GameEventHandler::GameEventHandler(Game* game):
        QObject(game),
        mp_game(game)
{
    mp_queue = new GameEventQueue(this);
}

void GameEventHandler::connectSlots(QObject* signalEmitter)
{
    connect(signalEmitter,      SIGNAL(sigEventCardMovement(const StructCardMovement&)),
            this,               SLOT(onCardMovementEvent(const StructCardMovement&)));
    connect(signalEmitter,      SIGNAL(sigEventGameFocusChange(int, int)),
            this,               SLOT(onGameFocusChangeEvent(int,int)));
}

void GameEventHandler::onCardMovementEvent(const StructCardMovement& structCardMovement)
{
    mp_queue->add(new CardMovementEvent(mp_game, structCardMovement));
}

void GameEventHandler::onGameFocusChangeEvent(int currentPlayerId, int requestedPlayerId)
{
    mp_queue->add(new GameFocusChangeEvent(mp_game, currentPlayerId, requestedPlayerId));
}
