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


class GameEventBroadcaster
{
public:
    GameEventBroadcaster();
    void registerHandler(GameEventHandler*, Player* player = 0);
    void unregisterHandler(GameEventHandler*, Player* player = 0);


    void onChatMessage(Player*, const QString& message);

    void onGameSync();

    void onPlayerJoinedGame(Player*);

    void onPlayerLeavedGame(Player*);

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


private:
    typedef QPair<GameEventHandler*, Player*> HandlerPair;
    QList<HandlerPair> m_handlers;

};

#endif // GAMEEVENTBROADCASTER_H
