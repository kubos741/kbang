#ifndef GAMETABLE_H
#define GAMETABLE_H

#include <QtCore>

class CardAbstract;
class CardPlayable;
class Player;
class Game;


class GameTable
{
    friend class Game;
public:
    GameTable(Game* game);

    /**
     * The player obtains certain number of cards from the deck.
     * \param player    Target player
     * \param count     The count of cards
     */
    void drawCard(Player* player, int count = 1, bool revealCard = 0);

    /**
     * The player discards the specified card.
     */
    void discardCard(Player* p, CardAbstract* card);

    /**
     * Player moves a card from his hand/table to the playedCards list.
     */
    void playCard(Player* p, CardPlayable* card);

    void playOnTable(Player* p, CardPlayable* card);

    /**
     * Returns the last played card.
     */
    inline CardPlayable* lastPlayedCard() const {
        return m_playedCards.last();
    }

    CardPlayable* firstPlayedCard() const {
        return m_playedCards.first();
    }

    CardAbstract* card(int cardId) const {
        return (m_cards.contains(cardId)) ? m_cards[cardId] : 0;
    }


    /**
     * Returns the playedCards list.
     */
    inline QList<CardPlayable*> playedCards() const {
        return m_playedCards;
    }


    void pushPlayedCard(CardPlayable* card);

    /**
     * Clears the playedCards list by appending its content
     * to the graveyard.
     */
    void clearPlayedCards();


signals:
    void playerDrawedCard(Player* player, CardAbstract* card);
    void playerDiscardedCard(Player* player, CardAbstract* card);

private:
    void generateCards();
    void shuffleDeck();
    void dealCards();
    void regenerateDeck();
    int  uniqueCardId();

    inline CardAbstract* popCardFromDeck();
    inline void putCardToGraveyard(CardAbstract* card);


protected:
   /**
     * Prepares the game.
     */
    void prepareGame();

private:
    Game*                           mp_game;
    QList<CardAbstract*>            m_deck;
    QList<CardAbstract*>            m_graveyard;
    QList<CardPlayable*>            m_playedCards;
    QMap<int, CardAbstract*>        m_cards;
};

#endif // GAMETABLE_H
