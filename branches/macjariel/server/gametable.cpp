#include "gametable.h"
#include "common.h"
#include "cards.h"
#include "player.h"
#include "util.h"

GameTable::GameTable(Game* game):
        mp_game(game)
{
}


void GameTable::prepareGame() {
    generateCards();
    dealCards();


}

void GameTable::drawCard(Player *p, int count)
{
    for(int i = 0; i < count; ++i)
    {
        CardAbstract* card = popCardFromDeck();
        p->appendCardToHand(card);
        //emit playerDrawedCard(p, card);
    }
}

void GameTable::discardCard(Player* player, CardAbstract* card)
{
    card = player->removeCardFromHand(card);
    if (!card) {
        qCritical() << "Cannot discard card " << card->id();
        return;
    }
    putCardToGraveyard(card);
    //emit playerDiscardedCard(player, card);
}

void GameTable::generateCards()
{
    static const int nBang = 20;
    static const int nMissed = 20;
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


void GameTable::setPlayerOnTurn(Player* player)
{
    mp_playerOnTurn = player;
}
