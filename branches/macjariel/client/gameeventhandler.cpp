
#include "gameeventhandler.h"
#include "gameeventqueue.h"
#include "game.h"

#include "cardmovementevent.h"

using namespace client;

GameEventHandler::GameEventHandler(Game* game):
        QObject(game),
        mp_game(game)
{
    mp_queue = new GameEventQueue(this);
}

void GameEventHandler::connectSlots(QObject* signalEmitter)
{
    connect(signalEmitter,      SIGNAL(eventCardMovement(const StructCardMovement&)),
            this,               SLOT(onCardMovementEvent(const StructCardMovement&)));
}

void GameEventHandler::onCardMovementEvent(const StructCardMovement& structCardMovement)
{
    mp_queue->add(new CardMovementEvent(mp_game, structCardMovement));
}
