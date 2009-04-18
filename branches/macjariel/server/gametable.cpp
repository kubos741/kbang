#include "gametable.h"
#include "common.h"
#include "cards.h"
#include "player.h"
#include "util.h"
#include "gameeventhandler.h"
#include "gameexceptions.h"


GameTable::GameTable(Game* game):
        mp_game(game)
{
}


void GameTable::prepareGame() {
    generateCards();
    foreach(Player* p, mp_game->playerList())
        p->gameEventHandler()->onGameSync();
    dealCards();
}



void GameTable::drawCard(Player *player, int count, bool revealCard)
{
    for(int i = 0; i < count; ++i)
    {
        CardAbstract* card = popCardFromDeck();
        player->appendCardToHand(card);
        card->setOwner(player);
        card->setPocketType(POCKET_HAND);
        foreach(Player* p, mp_game->playerList())
            p->gameEventHandler()->onPlayerDrawedCard(player->id(),
                    (p == player || revealCard) ? card : 0);
    }
}

void GameTable::discardCard(Player* player, CardAbstract* card)
{
    if (!player->removeCardFromHand(card))
        throw BadCardException();
    putCardToGraveyard(card);
    card->setOwner(0);
    card->setPocketType(POCKET_GRAVEYARD);
    foreach(Player* p, mp_game->playerList())
        p->gameEventHandler()->onPlayerDiscardedCard(player->id(), card);
}

void GameTable::playCard(Player* player, CardPlayable* card)
{
    player->removeCardFromHand(card);
    m_playedCards.push_back(card);
    card->setPocketType(POCKET_PLAYED);

    foreach(Player* p, mp_game->playerList())
        p->gameEventHandler()->onPlayerPlayedCard(player->id(), card);

}

void GameTable::playOnTable(Player* player, CardPlayable* card)
{
    player->removeCardFromHand(card);
    player->appendCardToTable(card);
    card->setPocketType(POCKET_TABLE);

    foreach(Player* p, mp_game->playerList())
        p->gameEventHandler()->onPlayerPlayedOnTable(player->id(), card);
}

void GameTable::clearPlayedCards()
{
    foreach(CardAbstract* card, m_playedCards)
    {
        m_graveyard << card;
        card->setPocketType(POCKET_GRAVEYARD);
        card->setOwner(0);
    }
    m_playedCards.clear();
    foreach(Player* p, mp_game->playerList())
        p->gameEventHandler()->onPlayedCardsCleared();
}


void GameTable::generateCards()
{
    static const int nBang = 100;
    static const int nMissed = 30;
    static const int nBeer = 50;
    static const int nMustang = 20;
    for(int i = 0; i < nBang; ++i)
    {
        int id = uniqueCardId();
        m_cards[id] = new CardBang(mp_game, id);
    }
    for(int i = 0; i < nMissed; ++i)
    {
        int id = uniqueCardId();
        m_cards[id] = new CardMissed(mp_game, id);
    }
    for(int i = 0; i < nBeer; ++i)
    {
        int id = uniqueCardId();
        m_cards[id] = new CardBeer(mp_game, id);
    }
    for(int i = 0; i < nMustang; ++i)
    {
        int id = uniqueCardId();
        m_cards[id] = new CardMustang(mp_game, id);
    }


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




int GameTable::uniqueCardId()
{
    int cardId;
    do {
        cardId = (int)random();
    } while(m_cards.contains(cardId));
    return cardId;
}

CardAbstract* GameTable::popCardFromDeck()
{
    if (m_deck.isEmpty()) regenerateDeck();
    return m_deck.takeFirst();
}

void GameTable::putCardToGraveyard(CardAbstract* card)
{
    m_graveyard.push_back(card);
}
