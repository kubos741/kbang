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
        if (cardWidget == mp_activeCard) {
            unsetActiveCard();
            return;
        }
        qDebug() << "card click cannot be handled now - expecting player click: " << cardWidget;
    }

    if (m_state == STATE_MAIN && cardWidget->pocketType() == POCKET_DECK) {
        mp_game->serverConnection()->drawCard();
    }

    if (m_state == STATE_MAIN && cardWidget->pocketType() == POCKET_HAND && cardWidget->ownerId() == mp_game->playerId())
    {
        onMainCardClicked(cardWidget);

    }
}

void GameObjectClickHandler::onPlayerClicked(PlayerWidget* playerWidget)
{
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
            debug("onMainCardClicked - bang");
            setActiveCard(cardWidget);
            setSelectPlayerState();
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
