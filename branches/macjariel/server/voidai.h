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
    virtual void onIncomingMessage(const PublicPlayerView& publicPlayerView, const QString& message) {}
    virtual void onPlayerInit(PlayerCtrl* playerCtrl);
    virtual void onPlayerExit() {}
    virtual void onPlayerJoinedGame(const PublicPlayerView& publicPlayerView) {}
    virtual void onPlayerLeavedGame(const PublicPlayerView&) {}
    virtual void onGameStartabilityChanged(bool isStartable) {}
    virtual void onGameStarted() {}
    virtual void onPlayerDrawedCard(int playerId, const CardAbstract*) {}
    virtual void onPlayerDiscardedCard(int playerId, const CardAbstract* card) {}
    virtual void onPlayerPlayedCard(int playerId, const CardAbstract* card) {}
    virtual void onPlayedCardsCleared() {}
    virtual void onLifePointsChange(const PublicPlayerView&, int oldLifePoints, int newLifePoints) {}
    virtual void onGameFocusChange(int currentPlayerId, int requestedPlayerId) {}

    virtual void onActionRequest(ActionRequestType requestType);

public slots:
    void requestWithAction();

private:
    static int sm_playerCounter;
    int         m_id;
    PlayerCtrl* mp_playerCtrl;
    ActionRequestType m_requestType;
};

#endif // VOIDAI_H
