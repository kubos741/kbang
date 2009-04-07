#include "gamefocuschangeevent.h"
#include "game.h"
#include "playerwidget.h"

using namespace client;

GameFocusChangeEvent::GameFocusChangeEvent(Game* game, int currentPlayerId, int requestedPlayerId):
        GameEvent(game),
        m_currentPlayerId(currentPlayerId),
        m_requestedPlayerId(requestedPlayerId)
{
}

GameFocusChangeEvent::~GameFocusChangeEvent()
{
}

void GameFocusChangeEvent::run()
{
    qDebug() << "GameFocusChangeEvent";
    GameEvent::run();
    PlayerWidget* currentPlayer = mp_game->playerWidget(mp_game->currentPlayerId());
    PlayerWidget* requestedPlayer = mp_game->playerWidget(mp_game->requestedPlayerId());
    if (requestedPlayer)
        requestedPlayer->setActive(0);

    mp_game->setCurrentPlayerId(m_currentPlayerId);
    mp_game->setRequestedPlayerId(m_requestedPlayerId);


    currentPlayer = mp_game->playerWidget(m_currentPlayerId);
    requestedPlayer = mp_game->playerWidget(m_requestedPlayerId);



    if (requestedPlayer)
        requestedPlayer->setActive(255);
    else
        qCritical("Bad player in GameFocusChangeEvent.");

    GameEvent::finish();
}

