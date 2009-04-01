#include "gamecycle.h"
#include "gameexceptions.h"
#include "game.h"

GameCycle::GameCycle(Game* game): mp_game(game)
{
}

void GameCycle::start(int startingPlayer)
{
    m_currentPlayerId = m_activePlayerId = startingPlayer;
    m_state = STATE_DRAW;
}

void GameCycle::draw(int playerId)
{
    checkPlayerAndState(playerId, STATE_DRAW);

    /// \todo Premature draw check and notification

    /// \todo Give player his cards

    m_state = STATE_TURN;
}

void GameCycle::checkDeck(int playerId)
{
    checkPlayerAndState(playerId, STATE_DRAW);
    /// \todo
}

void GameCycle::discard(int playerId)
{
    checkPlayerAndState(playerId, STATE_TURN);

    m_currentPlayerId = mp_game->nextPlayerId(m_currentPlayerId);
    m_state = STATE_DRAW;
}


void GameCycle::checkPlayerAndState(int playerId, State state)
{
    if (playerId != m_activePlayerId)
        throw BadPlayerException(m_currentPlayerId);

    if (state != m_state)
        throw BadGameStateException();
}
