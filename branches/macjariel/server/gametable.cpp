#include "gametable.h"
#include "common.h"
#include "cards.h"
#include "player.h"
#include "util.h"
#include "gameeventbroadcaster.h"
#include "gameexceptions.h"
#include "game.h"
#include "tablecard.h"
#include "cardfactory.h"

GameTable::GameTable(Game* game):
        mp_game(game)
{
}


void GameTable::prepareGame(CardFactory* cardFactory) {
    generateCards(cardFactory);
    mp_game->gameEventBroadcaster().onGameSync();
    dealCards();
}



void GameTable::playerDrawFromDeck(Player* player, int count, bool revealCards)
{
    QList<const PlayingCard*> drawedCards;
    for(int i = 0; i < count; ++i)
    {
        PlayingCard* card = popCardFromDeck();
        player->appendCardToHand(card);
        card->setOwner(player);
        card->setPocket(POCKET_HAND);
        drawedCards.append(card);
    }
    mp_game->gameEventBroadcaster().onPlayerDrawFromDeck(player, drawedCards, revealCards);
}

void GameTable::playerDiscardCard(PlayingCard* card)
{
    Player*     owner  = card->owner();
    PocketType  pocket = card->pocket();

    Q_ASSERT(pocket == POCKET_HAND || pocket == POCKET_TABLE);
    moveCardToGraveyard(card);

    mp_game->gameEventBroadcaster().onPlayerDiscardCard(owner, card, pocket);
}


void GameTable::playerPlayCard(PlayingCard* card)
{
    Q_ASSERT(card->pocket() == POCKET_HAND);
    Player* owner = card->owner();
    moveCardToGraveyard(card);
    mp_game->gameEventBroadcaster().onPlayerPlayCard(owner, card);
}

void GameTable::playerPlayCard(PlayingCard* card, Player* targetPlayer)
{
    Q_ASSERT(card->pocket() == POCKET_HAND);
    Player* owner = card->owner();
    moveCardToGraveyard(card);
    mp_game->gameEventBroadcaster().onPlayerPlayCard(owner, card, targetPlayer);
}

void GameTable::playerPlayCard(PlayingCard* card, PlayingCard* targetCard)
{
    Q_ASSERT(card->pocket() == POCKET_HAND);
    Player* owner = card->owner();
    moveCardToGraveyard(card);
    mp_game->gameEventBroadcaster().onPlayerPlayCard(owner, card, targetCard);
}

void GameTable::playerPlayCardOnTable(TableCard* card, Player* targetPlayer)
{
    Q_ASSERT(card->pocket() == POCKET_HAND);
    Player* owner = card->owner();

    if (targetPlayer == 0)
        targetPlayer = owner;

    owner->removeCardFromHand(card);

    targetPlayer->appendCardToTable(card);
    card->setOwner(targetPlayer);
    card->setPocket(POCKET_TABLE);
    card->registerPlayer(targetPlayer);

    mp_game->gameEventBroadcaster().onPlayerPlayCardOnTable(owner, card, targetPlayer);
}

void GameTable::passTableCard(TableCard* card, Player* targetPlayer)
{
    Q_ASSERT(card->pocket() == POCKET_TABLE);
    Player* owner = card->owner();

    owner->removeCardFromTable(card);
    card->unregisterPlayer(owner);

    targetPlayer->appendCardToTable(card);
    card->setOwner(targetPlayer);
    card->setPocket(POCKET_TABLE);
    card->registerPlayer(targetPlayer);
    mp_game->gameEventBroadcaster().onPassTableCard(owner, card, targetPlayer);
}

void GameTable::drawIntoSelection(int count, Player* selectionOwner)
{
    Q_ASSERT(m_selection.isEmpty());
    QList<const PlayingCard*> drawedCards;
    for(int i = 0; i < count; ++i)
    {
        PlayingCard* card = popCardFromDeck();
        m_selection.append(card);
        card->setOwner(selectionOwner);
        card->setPocket(POCKET_SELECTION);
        drawedCards.append(card);
    }
    mp_game->gameEventBroadcaster().onDrawIntoSelection(selectionOwner, drawedCards);
}

void GameTable::playerPickFromSelection(Player* player, PlayingCard* card)
{
    bool revealCard = (card->owner() != player);
    m_selection.removeAll(card);
    player->appendCardToHand(card);
    card->setOwner(player);
    card->setPocket(POCKET_HAND);
    mp_game->gameEventBroadcaster().onPlayerPickFromSelection(player, card, revealCard);
}



bool GameTable::playerCheckDeck(Player* player, PlayingCard* reasonCard, bool (*checkFunc)(PlayingCard*))
{
    PlayingCard* checkedCard = popCardFromDeck();
    putCardToGraveyard(checkedCard);
    checkedCard->setOwner(0);
    checkedCard->setPocket(POCKET_GRAVEYARD);
    bool checkResult = (*checkFunc)(checkedCard);
    mp_game->gameEventBroadcaster().onPlayerCheckDeck(player, checkedCard, reasonCard, checkResult);
    return checkResult;
}

void GameTable::playerStealCard(Player* player, PlayingCard* card)
{
    PocketType pocket = card->pocket();
    Player*    owner  = card->owner();

    switch(pocket) {
    case POCKET_HAND:
        owner->removeCardFromHand(card);
        break;
    case POCKET_TABLE:
        owner->removeCardFromTable(card);
        (qobject_cast<TableCard*>(card))->unregisterPlayer(owner);
        break;
    default:
        NOT_REACHED();
    }

    player->appendCardToHand(card);
    card->setOwner(player);
    card->setPocket(POCKET_HAND);

    mp_game->gameEventBroadcaster().onPlayerStealCard(player, owner, pocket, card);
}


void GameTable::cancelCard(PlayingCard* card, Player* player)
{
    PocketType pocket = card->pocket();
    Player*    owner  = card->owner();

    moveCardToGraveyard(card);

    mp_game->gameEventBroadcaster().onCancelCard(owner, pocket, card, player);
}


void GameTable::generateCards(CardFactory* cardFactory)
{
    m_cards = cardFactory->generateCards(mp_game);
    m_deck << m_cards.values();
}

void GameTable::shuffleDeck()
{
    shuffleList(m_deck);
}


void GameTable::dealCards()
{
    int cardCount = 0, players = 0;
    do {
        players = 0;
        foreach(Player* p, mp_game->playerList())
        {
            if (p->initialCardCount() > cardCount)
            {
                playerDrawFromDeck(p);
                players++;
            }
        }
        cardCount++;
    } while(players != 0);
}

void GameTable::regenerateDeck()
{
    Q_ASSERT(m_deck.isEmpty());
    Q_ASSERT(!m_graveyard.isEmpty());
    m_deck << m_graveyard;
    m_graveyard.clear();
    m_graveyard << m_deck.takeLast();
    shuffleList(m_graveyard);
    mp_game->gameEventBroadcaster().onDeckRegenerate();
}

void GameTable::moveCardToGraveyard(PlayingCard* card)
{
    Player* owner = card->owner();
    switch(card->pocket()) {
    case POCKET_HAND:
        owner->removeCardFromHand(card);
        break;
    case POCKET_TABLE:
        owner->removeCardFromTable(card);
        (qobject_cast<TableCard*>(card))->unregisterPlayer(owner);
        break;
    case POCKET_SELECTION:
        m_selection.removeAll(card);
        break;
    default:
        NOT_REACHED();
    }

    putCardToGraveyard(card);
    card->setOwner(0);
    card->setPocket(POCKET_GRAVEYARD);
}


PlayingCard* GameTable::popCardFromDeck()
{
    if (m_deck.isEmpty()) regenerateDeck();
    return m_deck.takeFirst();
}

void GameTable::putCardToGraveyard(PlayingCard* card)
{
    m_graveyard.push_back(card);
}
