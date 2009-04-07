#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <QObject>
#include "parser/parserstructs.h"

namespace client
{
class GameEventQueue;
class Game;

class GameEventHandler: public QObject
{
Q_OBJECT;
public:
    GameEventHandler(Game* game);
    void connectSlots(QObject* signalEmitter);

public slots:
    void onCardMovementEvent(const StructCardMovement&);
    void onGameFocusChangeEvent(int currentPlayerId, int requestedPlayerId);
    void onGameSyncEvent(const GameSyncData&);
    void onLifePointsChangeEvent(int playerId, int lifePoints);

private:
    Game*           mp_game;
    GameEventQueue* mp_queue;
};

}
#endif // GAMEEVENTHANDLER_H
