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
    qDebug() << "card clicked: " << cardWidget;
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

    debug(QString("card owner: %1").arg(cardWidget->ownerId()));


    if (m_state == STATE_MAIN && cardWidget->pocketType() == POCKET_DECK) {
        mp_game->serverConnection()->drawCard();
    }

    if (m_state == STATE_MAIN && cardWidget->pocketType() == POCKET_HAND && cardWidget->ownerId() == mp_game->playerId())
    {
        onMainCardClicked(cardWidget);

    }
    debug("");
}

void GameObjectClickHandler::onPlayerClicked(PlayerWidget* playerWidget)
{
    qDebug() << "player clicked: " << playerWidget->id();
    if (m_state != STATE_SELECT_PLAYER) {
        qDebug() << "player click cannot be handled now: " << playerWidget->id();
        return;
    }
    if (playerWidget->id() == 0) {
        qDebug("empty player widget clicked.");
        return;
    }
    if (mp_activeCard) {
        qDebug() << "playing card id" << mp_activeCard->cardId() << "on player" << playerWidget->id();
        mp_game->serverConnection()->playCardWithPlayer(mp_activeCard->cardId(), playerWidget->id());
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
    debug(QString("[Click]    onMainCardClicked, cardClass: %1").arg(cardWidget->cardClass()));
    if (m_inDiscardMode) {
        mp_game->serverConnection()->discardCard(cardWidget->cardId());
        return;
    }

    if (cardWidget->cardClass() == "bang") {
        debug("onMainCardClicked - bang");
        setActiveCard(cardWidget);
        setSelectPlayerState();
    } else {
        debug("onMainCardClicked - other");
        mp_game->serverConnection()->playCard(cardWidget->cardId());
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
