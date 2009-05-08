#ifndef GAMELOGGER_H
#define GAMELOGGER_H

#include <fstream>

#include "gameeventhandler.h"


class GameLogger : public GameEventHandler
{
public:
    GameLogger();

    virtual bool isAI() { return 1; }

    virtual void onHandlerRegistered(PlayerCtrl* playerCtrl);
    virtual void onHandlerUnregistered();

    virtual void onGameStartabilityChanged(bool) {}

    virtual void onChatMessage(PublicPlayerView&, const QString&) {}
    virtual void onGameSync() {}
    virtual void onPlayerJoinedGame(PublicPlayerView&) {}
    virtual void onPlayerLeavedGame(PublicPlayerView&) {}
    virtual void onPlayerDied(PublicPlayerView&, PublicPlayerView* causedBy);
    virtual void onGameStarted();
    virtual void onPlayerDrawFromDeck(PublicPlayerView&, QList<const PlayingCard*>, bool);
    virtual void onPlayerDrawFromGraveyard(PublicPlayerView&, const PlayingCard*, const PlayingCard*);
    virtual void onPlayerDiscardCard(PublicPlayerView&, const PlayingCard*, PocketType);
    virtual void onPlayerPlayCard(PublicPlayerView&, const PlayingCard*);
    virtual void onPlayerPlayCard(PublicPlayerView&, const PlayingCard*, PublicPlayerView&);
    virtual void onPlayerPlayCard(PublicPlayerView&, const PlayingCard*, const PlayingCard*);
    virtual void onPlayerPlayCardOnTable(PublicPlayerView&, const PlayingCard*, PublicPlayerView&);
    virtual void onPassTableCard(PublicPlayerView&, const PlayingCard*, PublicPlayerView&);
    virtual void onPlayerPass(PublicPlayerView&);
    virtual void onDrawIntoSelection(QList<const PlayingCard*>);
    virtual void onPlayerPickFromSelection(PublicPlayerView&, const PlayingCard*);
    virtual void onUndrawFromSelection(const PlayingCard* card);
    virtual void onPlayerCheckDeck(PublicPlayerView&, const PlayingCard*, const PlayingCard*, bool);
    virtual void onPlayerStealCard(PublicPlayerView&, PublicPlayerView&, PocketType, const PlayingCard*);
    virtual void onPlayerCancelCard(PublicPlayerView&, PocketType, const PlayingCard*, PublicPlayerView*);
    virtual void onGameContextChange(const GameContextData&);
    virtual void onLifePointsChange(PublicPlayerView&, int, PublicPlayerView*);
    virtual void onDeckRegenerate();

    virtual void onActionRequest(ActionRequestType) {}

private:
    PlayerCtrl* mp_playerCtrl;
    std::ofstream m_logFile;
};

#endif // GAMELOGGER_H
