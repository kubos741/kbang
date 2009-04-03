#ifndef GAMECYCLE_H
#define GAMECYCLE_H


class Game;
class Player;
class CardAbstract;
class CardPlayable;


class GameCycle
{
public:
    enum State {
        STATE_INVALID = 0,
        STATE_DRAW,
        STATE_TURN,
        STATE_RESPONSE,
        STATE_DISCARD
    };

    GameCycle(Game* game);

    inline  State   state()           const { return m_state; }
    inline  Player* currentPlayer()   const { return mp_currentPlayer; }
    inline  Player* requestedPlayer() const { return mp_requestedPlayer; }


    void start();


    /* Methods accessible from DRAW phase */

    /** The current player will <emph>draw</emph> cards. By default
     * the player will draw two cards from deck.
     *
     * \throws BadPlayerException       called by non-playing player.
     * \throws BadStateException        called in other than Draw state or requesting too many cards
     * \throws PrematureDrawException   missed card-effect - BOOM/PRISON (todo)
     *
     * \param player The calling player
     * \todo Draw cards from hands of other players (character feature).
     * \todo Draw three cards and return one on top of deck (character feature).
     */
    void drawCard(Player* player, int count = 1, bool revealCard = 0);

    /** The current player will <emph>check deck</emph> - revealing the top
     * card and puting it into graveyard.
     * \throws BadPlayerException       called by non-playing player.
     * \throws BadStateException        called in other than Draw state
     * \throws BadSituationException    called when no need to <emph>check deck</emph>
     *
     * \param playerId The calling player's id.
     */
    void checkDeck(Player* player);


    void finishTurn(Player* player);

    /* Methods accessible from TURN phase */
    // + seznam karet
    void discardCard(Player* player, CardAbstract* card);


    void playCard(Player* player, CardPlayable* card);
    void playCard(Player* player, CardPlayable* card, Player* targetPlayer);


    /* Methods accessible from RESPONSE phase */
    // nechcu reagovat kartou
    void pass(Player* player);


    void requestResponse(Player* player);
    void clearPlayedCards();

private:
    Game*   mp_game;
    State   m_state;
    Player* mp_currentPlayer;
    Player* mp_requestedPlayer;

    int     m_drawCardCount;
    int     m_drawCardMax;

private:
    void    sendRequest();
    void    checkPlayerAndState(Player* player, State state);
    void    startTurn(Player* player);
    int     needDiscard(Player* player);
};

#endif // GAMECYCLE_H
