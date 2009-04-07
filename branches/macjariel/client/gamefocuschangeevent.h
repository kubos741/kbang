#ifndef GAMEFOCUSCHANGEEVENT_H
#define GAMEFOCUSCHANGEEVENT_H

#include "gameevent.h"

namespace client
{
class Game;

class GameFocusChangeEvent : public GameEvent
{
Q_OBJECT;
public:
    GameFocusChangeEvent(Game* game, int currentPlayerId, int requestedPlayerId);
    virtual ~GameFocusChangeEvent();
    virtual void run();
private:
    int m_currentPlayerId;
    int m_requestedPlayerId;
};
}
#endif // GAMEFOCUSCHANGEEVENT_H
