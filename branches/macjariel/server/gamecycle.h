#ifndef GAMECYCLE_H
#define GAMECYCLE_H

#include "parser/parserstructs.h"

#include <QQueue>

class Game;
class Player;
class PlayingCard;
class ReactionHandler;


class GameCycle
{
public:
    GameCycle(Game* game);

    inline  GamePlayState   gamePlayState()   const { return m_state; }
    inline  Player*         currentPlayer()   const { return mp_currentPlayer; }
    inline  Player*         requestedPlayer() const { return mp_requestedPlayer; }
    inline  int             turnNumber()      const { return m_turnNum; }

    inline bool isDraw()     const { return m_state == GAMEPLAYSTATE_DRAW; }
    inline bool isTurn()     const { return m_state == GAMEPLAYSTATE_TURN; }
    inline bool isResponse() const { return m_state == GAMEPLAYSTATE_RESPONSE; }
    inline bool isDiscard()  const { return m_state == GAMEPLAYSTATE_DISCARD; }

    void assertDraw() const;
    void assertTurn() const;
    void assertResponse() const;
    void assertDiscard() const;

    inline ReactionHandler* reactionHandler() const { return isResponse() ? m_reactionHandlers.head() : 0; }

    GameContextData gameContextData() const;

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
    void draw(Player* player, bool specialDraw = 0);

    void skipPlayersTurn();

    void finishTurn(Player* player);

    /* Methods accessible from TURN phase */
    // + seznam karet
    void discardCard(Player* player, PlayingCard* card);


    void playCard(Player* player, PlayingCard* card);
    void playCard(Player* player, PlayingCard* card, Player* targetPlayer);
    void playCard(Player* player, PlayingCard* card, PlayingCard* targetCard);
    void pass(Player* player);


    void setResponseMode(ReactionHandler* reactionHandler, Player* requestedPlayer);
    void unsetResponseMode();

private:
    Game*                       mp_game;
    GamePlayState               m_state;
    GamePlayState               m_lastState;
    Player*                     mp_currentPlayer;
    Player*                     mp_requestedPlayer;
    QQueue<ReactionHandler*>    m_reactionHandlers;
    QQueue<Player*>             m_reactionPlayers;

    int     m_drawCardCount;
    int     m_drawCardMax;
    int     m_turnNum;

private:
    void    sendRequest();
    void    checkPlayerAndState(Player* player, GamePlayState state);
    void    startTurn(Player* player);
    int     needDiscard(Player* player);
    void    announceContextChange();
};

#endif // GAMECYCLE_H
