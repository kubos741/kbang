#ifndef GAMEEVENTBROADCASTER_H
#define GAMEEVENTBROADCASTER_H

#include "parser/parserstructs.h"
#include "gameeventhandler.h"

#include <QString>
#include <QList>
#include <QPair>

class GameEventHandler;
class Player;
class PlayingCard;
class Game;


class GameEventBroadcaster
{
public:
    GameEventBroadcaster(Game*);
    void registerHandler(GameEventHandler*, Player* player = 0);
    void registerSupervisor(GameEventHandler*);
    void unregisterHandler(GameEventHandler*);


    void onChatMessage(Player*, const QString& message);

    void onGameSync();

    void onPlayerJoinedGame(Player*);

    void onPlayerLeavedGame(Player*);

    void onPlayerUpdated(Player*);

    void onPlayerDied(Player*, Player* causedBy);

    void onGameStarted();



    void onPlayerDrawFromDeck(Player*, QList<const PlayingCard*>, bool revealCards);

    void onPlayerDrawFromGraveyard(Player*, const PlayingCard*, const PlayingCard*);

    void onPlayerDiscardCard(Player*, PlayingCard*, PocketType pocketFrom);

    void onPlayerPlayCard(Player*, PlayingCard*);

    void onPlayerPlayCard(Player*, PlayingCard*, Player* targetPlayer);

    void onPlayerPlayCard(Player*, PlayingCard*, PlayingCard* targetCard);

    void onPlayerPlayCardOnTable(Player*, PlayingCard*, Player* targetPlayer);

    void onPassTableCard(Player*, PlayingCard*, Player* targetPlayer);

    void onPlayerRespondWithCard(Player*, PlayingCard*);

    void onPlayerPass(Player*);

    void onDrawIntoSelection(Player* selectionOwner, QList<const PlayingCard*>);

    void onPlayerPickFromSelection(Player*, PlayingCard*, bool revealCard);

    void onUndrawFromSelection(PlayingCard*, Player* selectionOwner);

    void onPlayerCheckDeck(Player*, PlayingCard* checkedCard, PlayingCard* causedBy, bool checkResult);

    void onPlayerStealCard(Player*, Player* targetPlayer, PocketType pocketFrom, PlayingCard*);

    void onCancelCard(Player* targetPlayer, PocketType pocketFrom, PlayingCard*, Player*);

    void onGameContextChange(const GameContextData&);

    void onLifePointsChange(Player*, int lifePoints, Player* causedBy);

    void onDeckRegenerate();

    void onPlayerUseAbility(Player*);

    struct Handler {

        Handler(): handler(0), player(0), isSupervisor(0) {}
        Handler(GameEventHandler* h, Player* p, bool s = 0):
                handler(h), player(p), isSupervisor(s) {}
        GameEventHandler* handler;
        Player*           player;
        bool              isSupervisor;
    };


private:
    Game*           mp_game;
    QList<Handler*> m_handlers;

};

#endif // GAMEEVENTBROADCASTER_H
