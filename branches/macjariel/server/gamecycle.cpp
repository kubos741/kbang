#include "gamecycle.h"
#include "gametable.h"
#include "gameexceptions.h"
#include "game.h"
#include "player.h"
#include "gameeventhandler.h"
#include "cards.h"
#include <QDebug>

GameCycle::GameCycle(Game* game): mp_game(game)
{
}

void GameCycle::start()
{
    Player* player;
    foreach (player, mp_game->playerList())
        if (player->role() == ROLE_SHERIFF)
            break;
    Q_ASSERT(player->role() == ROLE_SHERIFF);
    qDebug("Starting game cycle.");
    startTurn(player);
}

void GameCycle::startTurn(Player* player)
{

    mp_currentPlayer = mp_requestedPlayer = player;
    m_state = STATE_DRAW;
    announceFocusChange();
    m_drawCardCount = 0;
    m_drawCardMax = 2;
    sendRequest();
}

void GameCycle::drawCard(Player* player, int numCards, bool revealCard)
{
    checkPlayerAndState(player, STATE_DRAW);

    if (m_drawCardCount + numCards > m_drawCardMax) {
        throw BadGameStateException();
    }

    /// \todo Premature draw check and notification

    /// Give player his cards
    mp_game->gameTable().drawCard(player, numCards, revealCard);
    m_drawCardCount += numCards;
    if (m_drawCardCount == m_drawCardMax) {
        m_state = STATE_TURN;
    }
    sendRequest();
}

void GameCycle::checkDeck(Player* player)
{
    checkPlayerAndState(player, STATE_DRAW);
    /// \todo
}

void GameCycle::finishTurn(Player* player)
{
    if (player != mp_requestedPlayer)
        throw BadPlayerException(mp_currentPlayer->id());

    if ((m_state != STATE_TURN) && (m_state != STATE_DISCARD))
        throw BadGameStateException();

    if (needDiscard(player))
        throw TooManyCardsInHandException();

    startTurn(mp_game->nextPlayer(mp_currentPlayer));
}

void GameCycle::discardCard(Player* player, CardAbstract* card)
{
    if (player != mp_requestedPlayer)
        throw BadPlayerException(mp_currentPlayer->id());

    if (m_state != STATE_TURN && m_state != STATE_DISCARD)
        throw BadGameStateException();

    if (needDiscard(player) == 0)
        throw BadGameStateException();

    mp_game->gameTable().discardCard(player, card);
    m_state = STATE_DISCARD;

    if (needDiscard(player) == 0)
        startTurn(mp_game->nextPlayer(mp_currentPlayer));
    else
        sendRequest();


}

void GameCycle::playCard(Player* player, CardPlayable* card)
{
    if (player != mp_requestedPlayer)
        throw BadPlayerException(mp_currentPlayer->id());

    if (m_state == STATE_DRAW || m_state == STATE_DISCARD)
        throw BadGameStateException();

    if (m_state == STATE_TURN)
        card->play();
    else
        mp_game->gameTable().firstPlayedCard()->respondCard(card);
}


void GameCycle::playCard(Player* player, CardPlayable* card, Player* targetPlayer)
{
    if (player != mp_requestedPlayer)
        throw BadPlayerException(mp_currentPlayer->id());

    if (m_state == STATE_DRAW || m_state == STATE_DISCARD)
        throw BadGameStateException();

    card->play(targetPlayer);
}

void GameCycle::pass(Player* player)
{
    if (player != mp_requestedPlayer)
        throw BadPlayerException(mp_currentPlayer->id());

    if (m_state != STATE_RESPONSE)
        throw BadGameStateException();

    mp_game->gameTable().firstPlayedCard()->respondPass();
}


void GameCycle::requestResponse(Player* player)
{
    if (mp_requestedPlayer != player && m_state != STATE_RESPONSE) {
        mp_requestedPlayer = player;
        m_state = STATE_RESPONSE;
        announceFocusChange();
    }
    sendRequest();
}

void GameCycle::clearPlayedCards()
{
    mp_requestedPlayer = mp_currentPlayer;
    m_state = STATE_TURN;
    announceFocusChange();
    mp_game->gameTable().clearPlayedCards();
    sendRequest();
}


void GameCycle::sendRequest()
{
    ActionRequestType requestType;
    switch(m_state) {
        case STATE_DRAW:
            requestType = REQUEST_DRAW;
            break;
        case STATE_TURN:
            requestType = REQUEST_PLAY;
            break;
        case STATE_RESPONSE:
            requestType = REQUEST_RESPOND;
            break;
        case STATE_DISCARD:
            requestType = REQUEST_DISCARD;
            break;
        default:
            NOT_REACHED();
    }
    qDebug(qPrintable(QString("GameCycle: sendRequest to #%1 (%2)").arg(mp_requestedPlayer->id()).arg(mp_requestedPlayer->name())));
    mp_requestedPlayer->gameEventHandler()->onActionRequest(requestType);
}

void GameCycle::checkPlayerAndState(Player* player, State state)
{
    if (player != mp_requestedPlayer)
        throw BadPlayerException(mp_currentPlayer->id());

    if (state != m_state)
        throw BadGameStateException();
}

int GameCycle::needDiscard(Player* player)
{
    int lifePoints = player->lifePoints();
    int handSize = player->handSize();
    return lifePoints > handSize ? 0 : handSize - lifePoints;
}

void GameCycle::announceFocusChange()
{
    foreach(Player* p, mp_game->playerList())
        p->gameEventHandler()->onGameFocusChange(mp_currentPlayer->id(), mp_requestedPlayer->id());

}
