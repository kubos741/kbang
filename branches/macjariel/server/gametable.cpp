#include "gametable.h"
#include "common.h"
#include "cards.h"
#include "player.h"
#include "util.h"
#include "gameeventhandler.h"
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
    foreach(Player* p, mp_game->playerList())
        p->gameEventHandler()->onGameSync();
    dealCards();
}



void GameTable::drawCard(Player *player, int count, bool revealCard)
{
    for(int i = 0; i < count; ++i)
    {
        PlayingCard* card = popCardFromDeck();
        player->appendCardToHand(card);
        card->setOwner(player);
        card->setPocket(POCKET_HAND);
        foreach(Player* p, mp_game->playerList())
            p->gameEventHandler()->onPlayerDrawedCard(player->id(),
                    (p == player || revealCard) ? card : 0);
    }
}

void GameTable::playerDiscardCard(PlayingCard* card)
{
    Player* owner = card->owner();
    if (card->pocket() == POCKET_HAND) {
        owner->removeCardFromHand(card);
    } else if (card->pocket() == POCKET_TABLE) {
        owner->removeCardFromTable(card);
    } else if (card->pocket() == POCKET_SELECTION && card->owner() != 0) {
        owner->removeCardFromSelection(card);
    } else {
        NOT_REACHED();
    }
    m_graveyard.push_back(card);
    int ownerId         = owner->id();
    PocketType pocket   = card->pocket();
    card->setOwner(0);
    card->setPocket(POCKET_GRAVEYARD);
    foreach(Player* p, mp_game->playerList())
        p->gameEventHandler()->onPlayerDiscardedCard(ownerId, pocket, card);
}

void GameTable::playCard(PlayingCard* card)
{
    Player* owner = card->owner();
    owner->removeCardFromHand(card);
    m_graveyard.push_back(card);
    card->setPocket(POCKET_GRAVEYARD);

    foreach(Player* p, mp_game->playerList())
        p->gameEventHandler()->onPlayerPlayedCard(owner->id(), card);
}

void GameTable::playOnTable(TableCard* card, Player* targetPlayer)
{
    Player* owner = card->owner();
    if (targetPlayer == 0)
        targetPlayer = owner;
    owner->removeCardFromHand(card);
    targetPlayer->appendCardToTable(card);
    card->setOwner(targetPlayer);
    card->setPocket(POCKET_TABLE);
    card->registerPlayer(targetPlayer);

    foreach(Player* p, mp_game->playerList())
        p->gameEventHandler()->onPlayerPlayedOnTable(owner->id(), card);
        // TODO - onPlayerPlayedOnTable(player, card, targetPlayer)
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
                drawCard(p);
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
}

PlayingCard* GameTable::popCardFromDeck()
{
    if (m_deck.isEmpty()) regenerateDeck();
    return m_deck.takeFirst();
}


