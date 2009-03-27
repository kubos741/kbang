#ifndef GAMECYCLE_H
#define GAMECYCLE_H


class Game;


class GameCycle
{
public:
    enum State {
        STATE_INVALID = 0,
        STATE_DRAW,
        STATE_TURN,
        STATE_RESPONSE
    };

    GameCycle(Game* game);

    inline  State   state()             const { return m_state; }
    inline  int     currentPlayerId()   const { return m_currentPlayerId; }
    inline  int     activePlayerId()    const { return m_activePlayerId; }





    /* Methods accessible from DRAW phase */

    /** The current player will <emph>draw</emph> cards. By default
     * the player will draw two cards from deck.
     *
     * \throws BadPlayerException       called by non-playing player.
     * \throws BadStateException        called in other than Draw state
     * \throws PrematureDrawException   missed card-effect - BOOM/PRISON (todo)
     *
     * \param playerId The calling player's id.
     * \todo Draw cards from hands of other players (character feature).
     * \todo Draw three cards and return one on top of deck (character feature).
     */
    void draw(int playerId);

    /** The current player will <emph>check deck</emph> - revealing the top
     * card and puting it into graveyard.
     * \throws BadPlayerException       called by non-playing player.
     * \throws BadStateException        called in other than Draw state
     * \throws BadSituationException    called when no need to <emph>check deck</emph>
     *
     * \param playerId The calling player's id.
     */
    void checkDeck(int playerId);

    /* Methods accessible from TURN phase */
    // + seznam karet
    void discard(int playerId);


    /* Methods accessible from RESPONSE phase */
    // nechcu reagovat kartou
    void pass(int playerId);

private:
    Game*   mp_game;
    State   m_state;
    int     m_currentPlayerId;
    int     m_activePlayerId;


private:
    void    start(int startingPlayerId);
    void    checkPlayerAndState(int playerId, State state);

};

#endif // GAMECYCLE_H
