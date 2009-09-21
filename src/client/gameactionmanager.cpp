#include "gameactionmanager.h"
#include "game.h"
#include "playerwidget.h"
#include "serverconnection.h"
#include "cardwidget.h"
#include "cardzoomwidget.h"
#include "gamestructs.h"

using namespace client;

GameActionManager::GameActionManager(Game* game):
        m_state(STATE_MAIN),
        mp_game(game),
        mp_activeCard(0)
{
}



bool GameActionManager::isClickable(CardWidget*)
{
    return 1;
}

bool GameActionManager::onCardClicked(CardWidget* cardWidget)
{
    if (!mp_game->isRequested()) {
        return 0;
    }

    switch(m_state) {
    case STATE_DISCARD:
        if (cardWidget->pocketType() != POCKET_HAND ||
            cardWidget->ownerId()    != mp_game->localPlayerId())
            return 0;
        ServerConnection::instance()->discardCard(cardWidget->cardData().id);
        return 1;

    case STATE_SELECT_PLAYER:
        unsetActiveCard();
        return 1;

    case STATE_SELECT_CARDS:
        Q_ASSERT(mp_activeCard != 0);
        if (cardWidget == mp_activeCard) {
            unsetActiveCard();
            return 1;
        }
        if (m_cardSelection.contains(cardWidget)) {
            removeFromSelection(cardWidget);
            return 1;
        }

        addToSelection(cardWidget);
        if (m_cardSelection.size() == m_selectionSize) {
            if (mp_activeCard->cardData().type == CARDTYPE_CHARACTER) {
                useAbilityWithCards();
            } else {
                playWithCards();
            }
            unsetActiveCard();
        }
        return 1;

    case STATE_MAIN:
        if (cardWidget->cardData().type == CARDTYPE_CHARACTER &&
            cardWidget->ownerId() == mp_game->localPlayerId()) {
            onCharacterClicked(cardWidget);
            return 1;
        }

        if (cardWidget->pocketType() == POCKET_DECK) {
            ServerConnection::instance()->drawCard();
            return 1;
        }

        if (cardWidget->cardData().id == 0)
            return 0;

        if (mp_game->gamePlayState() == GAMEPLAYSTATE_RESPONSE) {
            ActionPlayCardData data;
            data.playedCardId = cardWidget->cardData().id;
            ServerConnection::instance()->playCard(data);
            return 1;
        }

        if (cardWidget->pocketType() == POCKET_HAND &&
            cardWidget->ownerId() == mp_game->localPlayerId()) {
            onMainCardClicked(cardWidget);
        } else {
            ActionPlayCardData data;
            data.playedCardId = cardWidget->cardData().id;
            ServerConnection::instance()->playCard(data);
        }
        return 1;
    }

    return 1;
}

void GameActionManager::onCardRightClicked(CardWidget* cardWidget)
{
    qDebug("TEST");
    new CardZoomWidget(mp_game, cardWidget);
}

void GameActionManager::onPlayerClicked(PlayerWidget* playerWidget)
{
    if (!mp_game->isRequested() || m_state != STATE_SELECT_PLAYER ||
        playerWidget->id() == 0     || mp_activeCard == 0)
        return;

    if (mp_activeCard->cardData().type == CARDTYPE_CHARACTER) {
        ActionUseAbilityData data;
        data.targetPlayerId = playerWidget->id();
        ServerConnection::instance()->useAbility(data);
    } else {
        ActionPlayCardData data;
        data.playedCardId = mp_activeCard->cardData().id;
        data.targetPlayerId = playerWidget->id();
        ServerConnection::instance()->playCard(data);
    }
    unsetActiveCard();
}

void GameActionManager::onEndTurnClicked()
{
    unsetActiveCard();
    ServerConnection::instance()->endTurn();
}

void GameActionManager::onPassClicked()
{
    unsetActiveCard();
    ServerConnection::instance()->pass();
}

void GameActionManager::setDiscardMode(bool inDiscardMode)
{
    unsetActiveCard();
    m_state = inDiscardMode ? STATE_DISCARD : STATE_MAIN;
}

void GameActionManager::onMainCardClicked(CardWidget* cardWidget)
{
#if 0
    switch (cardWidget->cardData().type) {
        case CARD_BANG:
        case CARD_DUEL:
        case CARD_JAIL:
                selectPlayer(cardWidget);
                break;
        case CARD_PANIC:
        case CARD_CATBALOU:
                selectCards(cardWidget, 1);
                break;
        default:
            if (cardWidget->cardData().type == CARD_MISSED &&
                mp_game->character() == CHARACTER_CALAMITY_JANET) {
                selectPlayer(cardWidget);
                break;
            }
            ServerConnection::instance()->playCard(cardWidget->cardData().id);
            break;
    }
#endif
}

void GameActionManager::onCharacterClicked(CardWidget* cardWidget)
{
#if 0
    switch(mp_game->character()) {
    case CHARACTER_JESSE_JONES:
        selectPlayer(cardWidget);
        break;
    case CHARACTER_SID_KETCHUM:
        selectCards(cardWidget, 2);
        break;
    default:
        ServerConnection::instance()->useAbility();
        break;
    }
#endif
}

void GameActionManager::selectPlayer(CardWidget* activeCard)
{
#if 0
    Q_ASSERT(mp_activeCard == 0);
    Q_ASSERT(m_state == STATE_MAIN);
    mp_activeCard = activeCard;
    m_state = STATE_SELECT_PLAYER;
    mp_activeCard->setHighlight(1);
#endif
}

void GameActionManager::selectCards(CardWidget* activeCard, int cardCount)
{
#if 0
    Q_ASSERT(mp_activeCard == 0);
    Q_ASSERT(m_state == STATE_MAIN);
    mp_activeCard = activeCard;
    m_state = STATE_SELECT_CARDS;
    m_cardSelection.clear();
    m_selectionSize = cardCount;
    mp_activeCard->setHighlight(1);
#endif
}

void GameActionManager::unsetActiveCard()
{
    if (m_state == STATE_SELECT_CARDS) {
        foreach (CardWidget* c, m_cardSelection)
            removeFromSelection(c);
    }
    if (mp_activeCard != 0) {
        mp_activeCard->setHighlight(0);
        mp_activeCard = 0;
    }
    m_state = STATE_MAIN;
}


void GameActionManager::addToSelection(CardWidget* card)
{
    m_cardSelection.append(card);
    if (m_cardSelection.size() != m_selectionSize)
        card->setHighlight(1);
}

void GameActionManager::removeFromSelection(CardWidget* card)
{
    m_cardSelection.removeAll(card);
    card->setHighlight(0);
}

void GameActionManager::useAbilityWithCards()
{
    ActionUseAbilityData data;
    foreach (CardWidget* card, m_cardSelection) {
        data.targetCardsId.append(card->cardData().id);
    }
    ServerConnection::instance()->useAbility(data);
}

void GameActionManager::playWithCards()
{
#if 0
    if (m_cardSelection.size() == 1) {
        CardWidget* card = m_cardSelection[0];
        if (card->pocketType() == POCKET_HAND) {
            ServerConnection::instance()->playCardWithPlayer(mp_activeCard->cardData().id, card->ownerId());
        } else {
            ServerConnection::instance()->playCardWithCard(mp_activeCard->cardData().id, card->cardData().id);
        }
    } else {
        NOT_REACHED();
    }
#endif
}


void GameActionManager::debug(const QString& msg)
{
    qDebug(qPrintable(QString("[Click]         %1").arg(msg)));
}
