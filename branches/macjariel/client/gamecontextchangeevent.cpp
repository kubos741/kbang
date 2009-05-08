#include <QTimer>

#include "gamecontextchangeevent.h"
#include "game.h"
#include "playerwidget.h"

using namespace client;

GameContextChangeEvent::GameContextChangeEvent(Game* game, const GameContextData& gameContextData):
        GameEvent(game),
        m_gameContextData(gameContextData)
{
}

GameContextChangeEvent::~GameContextChangeEvent()
{
}

void GameContextChangeEvent::run()
{
    GameEvent::run();
    PlayerWidget* currentPlayer = mp_game->playerWidget(mp_game->currentPlayerId());
    PlayerWidget* requestedPlayer = mp_game->playerWidget(mp_game->requestedPlayerId());
    if (requestedPlayer)
        requestedPlayer->setActive(0);

    mp_game->setGameContext(m_gameContextData);

    currentPlayer = mp_game->playerWidget(m_gameContextData.currentPlayerId);
    requestedPlayer = mp_game->playerWidget(m_gameContextData.requestedPlayerId);

    if (requestedPlayer)
        requestedPlayer->setActive(255);
    else
        qCritical("Bad player in GameContextChangeEvent.");

    QTimer::singleShot(10, this, SLOT(finish()));
}
