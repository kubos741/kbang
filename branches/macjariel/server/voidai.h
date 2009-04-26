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
    virtual void onIncomingMessage(const PublicPlayerView&, const QString&) {}
    virtual void onPlayerInit(PlayerCtrl*);
    virtual void onGameSync() {}
    virtual void onPlayerExit() {}
    virtual void onPlayerJoinedGame(const PublicPlayerView&) {}
    virtual void onPlayerLeavedGame(const PublicPlayerView&) {}
    virtual void onPlayerDied(const PublicPlayerView&) {}
    virtual void onGameStartabilityChanged(bool isStartable) { Q_UNUSED(isStartable); }
    virtual void onGameStarted() {}
    virtual void onPlayerDrawedCard(int playerId, const PlayingCard*) { Q_UNUSED(playerId); }
    virtual void onPlayerDiscardedCard(int playerId, PocketType, const PlayingCard*) { Q_UNUSED(playerId); }
    virtual void onPlayerPlayedCard(int playerId, const PlayingCard*) { Q_UNUSED(playerId); }
    virtual void onPlayerPlayedOnTable(int playerId, PocketType, const PlayingCard*, int targetPlayerId) { Q_UNUSED(playerId); }
    virtual void onPlayerCheckedCard(int, const PlayingCard*, const PlayingCard*, bool) {}
    virtual void onPlayerStealedCard(int, int, PocketType, const PlayingCard*) {}
    virtual void onDrawIntoSelection(const PlayingCard*) {}
    virtual void onPlayerDrawedFromSelection(int, const PlayingCard*) {}
    virtual void onPlayedCardsCleared() {}
    virtual void onLifePointsChange(const PublicPlayerView&, int oldLifePoints, int newLifePoints)
                { Q_UNUSED(oldLifePoints); Q_UNUSED(newLifePoints);}
    virtual void onGameContextChange(const GameContextData&) {}
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
