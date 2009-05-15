#ifndef GAMEMESSAGEEVENT_H
#define GAMEMESSAGEEVENT_H

#include "gameevent.h"
#include "parser/parserstructs.h"

namespace client
{
class GameMessageEvent: public GameEvent
{
Q_OBJECT;
public:
    GameMessageEvent(Game* game, const GameMessage&);
    virtual ~GameMessageEvent();
    virtual void run();

private:
    QString cardToString(const CardData&, bool withRankAndSuit = 1);
    QString cardListToString(QList<CardData>);

    GameMessage m_gameMessage;

};
}

#endif // GAMEMESSAGEEVENT_H
