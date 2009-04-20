#ifndef GAMETABLE_H
#define GAMETABLE_H

#include <QtCore>

class PlayingCard;
class TableCard;
class Player;
class Game;
class CardFactory;


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
     * The player discards the specified card. The card can be in the player's
     * hand, table or selection.
     */
    void playerDiscardCard(PlayingCard* card);

    /**
     * Player moves a card from his hand/table to the playedCards list.
     */
    void playCard(PlayingCard* card);

    void playOnTable(TableCard* card, Player* targetPlayer = 0);

    PlayingCard* card(int cardId) const {
        return (m_cards.contains(cardId)) ? m_cards[cardId] : 0;
    }

private:
    void generateCards(CardFactory*);
    void shuffleDeck();
    void dealCards();
    void regenerateDeck();

    inline PlayingCard* popCardFromDeck();
    inline void putCardToGraveyard(PlayingCard* card);


protected:
   /**
     * Prepares the game.
     */
    void prepareGame(CardFactory*);

private:
    Game*                          mp_game;
    QList<PlayingCard*>            m_deck;
    QList<PlayingCard*>            m_graveyard;
    QList<PlayingCard*>            m_selection;
    QMap<int, PlayingCard*>        m_cards;
};

#endif // GAMETABLE_H
