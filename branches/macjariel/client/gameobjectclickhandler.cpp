#include "gameobjectclickhandler.h"
#include "game.h"
#include "playerwidget.h"
#include "serverconnection.h"


using namespace client;

GameObjectClickHandler::GameObjectClickHandler(Game* game):
        m_state(STATE_MAIN),
        mp_game(game),
        mp_activeCard(0),
        m_inDiscardMode(0)

{
}



bool GameObjectClickHandler::isClickable(CardWidget*)
{
    return 1;
}

void GameObjectClickHandler::onCardClicked(CardWidget* cardWidget)
{
    if (!mp_game->isAbleToRequest()) {
        qDebug() << "card click cannot be handled now: " << cardWidget;
        return;
    }

    if (m_state == STATE_SELECT_PLAYER) {
        unsetActiveCard();
        return;
    } else if (m_state == STATE_SELECT_CARD) {
        Q_ASSERT(mp_activeCard != 0);
        if (cardWidget->pocketType() == POCKET_HAND && cardWidget->ownerId() != mp_game->playerId()) {
            mp_game->serverConnection()->playCardWithPlayer(mp_activeCard->cardData().id, cardWidget->ownerId());
        } else {
            mp_game->serverConnection()->playCardWithCard(mp_activeCard->cardData().id, cardWidget->cardData().id);
        }
        unsetActiveCard();
        return;
    }

    if (m_state == STATE_MAIN && cardWidget->pocketType() == POCKET_DECK) {
        mp_game->serverConnection()->drawCard();
    }

    if (mp_game->gamePlayState() == GAMEPLAYSTATE_RESPONSE) {
        mp_game->serverConnection()->playCard(cardWidget->cardData().id);
        return;
    }



    if (m_state == STATE_MAIN && cardWidget->pocketType() == POCKET_HAND && cardWidget->ownerId() == mp_game->playerId())
    {
        onMainCardClicked(cardWidget);\
    } else {
        mp_game->serverConnection()->playCard(cardWidget->cardData().id);
    }

}

void GameObjectClickHandler::onPlayerClicked(PlayerWidget* playerWidget)
{
    if (!mp_game->isAbleToRequest()) {
        qDebug() << "clicks cannot be handled now: ";
        return;
    }

    if (m_state != STATE_SELECT_PLAYER) {
        qDebug() << "player click cannot be handled now: " << playerWidget->id();
        return;
    }
    if (playerWidget->id() == 0) {
        qDebug("empty player widget clicked.");
        return;
    }
    if (mp_activeCard) {
        qDebug() << "playing card id" << mp_activeCard->cardData().id << "on player" << playerWidget->id();
        mp_game->serverConnection()->playCardWithPlayer(mp_activeCard->cardData().id, playerWidget->id());
        unsetActiveCard();
    }

}

void GameObjectClickHandler::onEndTurnClicked()
{
    mp_game->serverConnection()->endTurn();
}

void GameObjectClickHandler::onPassClicked()
{
    mp_game->serverConnection()->pass();
}

void GameObjectClickHandler::setDiscardMode(bool inDiscardMode)
{
    m_inDiscardMode = inDiscardMode;
}


void GameObjectClickHandler::onMainCardClicked(CardWidget* cardWidget)
{

    if (m_inDiscardMode) {
        mp_game->serverConnection()->discardCard(cardWidget->cardData().id);
        return;
    }

    switch (cardWidget->cardData().type) {
        case CARD_BANG:
        case CARD_DUEL:
        case CARD_JAIL:
                setActiveCard(cardWidget);
                m_state = STATE_SELECT_PLAYER;
                break;
        case CARD_PANIC:
        case CARD_CATBALOU:
                setActiveCard(cardWidget);
                m_state = STATE_SELECT_CARD;
                break;
        default:
            debug("onMainCardClicked - other");
            mp_game->serverConnection()->playCard(cardWidget->cardData().id);
            break;
    }
}

void GameObjectClickHandler::setActiveCard(CardWidget* cardWidget)
{
    mp_activeCard = cardWidget;
    mp_activeCard->setHighlight(1);
}

void GameObjectClickHandler::unsetActiveCard()
{
    if (mp_activeCard != 0) {
        mp_activeCard->setHighlight(0);
        mp_activeCard = 0;
    }
    m_state = STATE_MAIN;
}

void GameObjectClickHandler::setSelectPlayerState()
{
    m_state = STATE_SELECT_PLAYER;
}

void GameObjectClickHandler::debug(const QString& msg)
{
    qDebug(qPrintable(QString("[Click]         %1").arg(msg)));
}
