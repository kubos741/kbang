#ifndef VOIDAI_H
#define VOIDAI_H

#include "gameeventhandler.h"
#include "parser/parserstructs.h"
#include <QObject>

class PlayerCtrl;

class VoidAI : public QObject, public GameEventHandler
{
Q_OBJECT;
public:
    VoidAI(int gameId);
    virtual ~VoidAI() {}

    virtual void onHandlerRegistered(PlayerCtrl* playerCtrl);
    virtual void onHandlerUnregistered() {}

    virtual void onGameStartabilityChanged(bool) {}

    virtual void onChatMessage(PublicPlayerView&, const QString&) {}
    virtual void onGameSync() {}
    virtual void onPlayerJoinedGame(PublicPlayerView&) {}
    virtual void onPlayerLeavedGame(PublicPlayerView&) {}
    virtual void onPlayerDied(PublicPlayerView&, PublicPlayerView* causedBy) {}
    virtual void onGameStarted() {}
    virtual void onPlayerDrawFromDeck(PublicPlayerView&, QList<const PlayingCard*>, bool) {}
    virtual void onPlayerDrawFromGraveyard(PublicPlayerView&, const PlayingCard*, const PlayingCard*) {}
    virtual void onPlayerDiscardCard(PublicPlayerView&, const PlayingCard*, PocketType) {}
    virtual void onPlayerPlayCard(PublicPlayerView&, const PlayingCard*) {}
    virtual void onPlayerPlayCard(PublicPlayerView&, const PlayingCard*, PublicPlayerView&) {}
    virtual void onPlayerPlayCard(PublicPlayerView&, const PlayingCard*, const PlayingCard*) {}
    virtual void onPlayerPlayCardOnTable(PublicPlayerView&, const PlayingCard*, PublicPlayerView&) {}
    virtual void onPassTableCard(PublicPlayerView&, const PlayingCard*, PublicPlayerView&) {}
    virtual void onPlayerPass(PublicPlayerView&) {}
    virtual void onDrawIntoSelection(QList<const PlayingCard*>) {}
    virtual void onPlayerPickFromSelection(PublicPlayerView&, const PlayingCard*) {}
    virtual void onUndrawFromSelection(const PlayingCard* card) {}
    virtual void onPlayerCheckDeck(PublicPlayerView&, const PlayingCard*, const PlayingCard*, bool) {}
    virtual void onPlayerStealCard(PublicPlayerView&, PublicPlayerView&, PocketType, const PlayingCard*) {}
    virtual void onPlayerCancelCard(PublicPlayerView&, PocketType, const PlayingCard*, PublicPlayerView*) {}
    virtual void onGameContextChange(const GameContextData&) {}
    virtual void onLifePointsChange(PublicPlayerView&, int, PublicPlayerView*) {}
    virtual void onDeckRegenerate() {}

    virtual void onActionRequest(ActionRequestType);

public slots:
    void requestWithAction();

private:
    static int sm_playerCounter;
    int         m_id;
    PlayerCtrl* mp_playerCtrl;
    ActionRequestType m_requestType;
};

#endif // VOIDAI_H
