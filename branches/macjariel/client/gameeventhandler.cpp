
#include "gameeventhandler.h"
#include "gameeventqueue.h"
#include "game.h"

#include "cardmovementevent.h"
#include "gamefocuschangeevent.h"
#include "gamesyncevent.h"
#include "lifepointschangeevent.h"

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
    connect(signalEmitter,      SIGNAL(sigEventGameSync(const GameSyncData&)),
            this,               SLOT(onGameSyncEvent(const GameSyncData&)));
    connect(signalEmitter,      SIGNAL(sigEventLifePointsChange(int, int)),
            this,               SLOT(onLifePointsChangeEvent(int, int)));
}

void GameEventHandler::onCardMovementEvent(const StructCardMovement& structCardMovement)
{
    qDebug() << "CardMovementEvent";
    mp_queue->add(new CardMovementEvent(mp_game, structCardMovement));
}

void GameEventHandler::onGameFocusChangeEvent(int currentPlayerId, int requestedPlayerId)
{
    qDebug() << "FocusChangeEvent";
    mp_queue->add(new GameFocusChangeEvent(mp_game, currentPlayerId, requestedPlayerId));
}

void GameEventHandler::onGameSyncEvent(const GameSyncData& gameSyncData)
{
    qDebug() << "GameSyncEvent";
    mp_queue->add(new GameSyncEvent(mp_game, gameSyncData));
}

void GameEventHandler::onLifePointsChangeEvent(int playerId, int lifePoints)
{
    qDebug() << "LifePointsChangeEvent";
    mp_queue->add(new LifePointsChangeEvent(mp_game, playerId, lifePoints));
}

