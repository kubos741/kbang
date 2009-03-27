#ifndef PLAYERCTRL_H
#define PLAYERCTRL_H

#include <QObject>

#include "gameexceptions.h"
#include "parser/parserstructs.h"

class Player;
class AbstractPlayerController;
class PublicGameView;
class PublicPlayerView;
class PrivatePlayerView;

/**
 * This class provides the only "correct" form to
 * control a player. It means that any code that
 * wants to control a player needs to do it throught
 * this API. It's used primarily by AIs and the
 * adaptor between this class and xml parser.
 */
class PlayerCtrl :  QObject
{
    Q_OBJECT;
    friend class Player;
public:
    /**
     * Disconnects the player from the game, or possibly subtitutes player with
     * AI. This method should never be called by AIs
     * Typically you want to call this method after the remote client
     * disconnected or requested a disconnection.
     */
    void disconnect();

    /**
     * Starts the yet not started game.
     * \throws BadPlayerException The player does not have the permission to
     *         start the game.
     * \throws BadGameStateException Either the game is already started, or
     *         the right conditions are not met, eg. there is not enough
     *         players in the game.
     */
    void startGame();

    /**
     * Finishes the player's turn.
     * \throws TooManyCardsInHandException The player must discard some cards,
     *         before he can finish his turn.
     * \throws BadGameStateException The player cannot finish his turn, because
     *         it's not the right moment.
     */
    void finishTurn();

    /**
     * Discards a card.
     * \param cardId The id of the card.
     * \throws BadCardException There is no card with given id in player's hand.
     * \throws BadGameStateException There is no right moment for discarding cards.
     */
    void discardCard(int cardId);

    /**
     * Plays a card.
     */
    void playCard(int cardId);






    const PublicGameView& publicGameView() const;
    const PublicPlayerView& publicPlayerView(int playerId = 0) const;
    const PrivatePlayerView& privatePlayerView() const;



    /**
     * Creates a new game and returns the PlayerCtrl control. This should be used
     * exclusively by nonAI client classes, as AIs typically don't create games.
     * \param game The game structure.
     * \param player The player structure.
     */
    static PlayerCtrl* createGame(const StructGame& game, const StructPlayer& player);

    /**
     * Creates a new player and has him enter the game.
     * \param gameId The id of the game.
     * \param player The player structure.
     * \throws BadGameException The game does not exist.
     * \throws BadGameStateException The game has already started.
     */
    static PlayerCtrl* joinGame(int gameId, const StructPlayer& player);

    /**
     * Returns the StructServerInfo struct.
     */
    static StructServerInfo structServerInfo();

    /**
     * Returns the list of PublicGameViews.
     */
    static QList<const PublicGameView*> publicGameList();

    /**
     * Returns the PublicGameView of the game specified by gameId.
     */
    static const PublicGameView& publicGameView(int gameId);


private:
    PlayerCtrl(Player* player, AbstractPlayerController* abstractPlayerController);
    PlayerCtrl(const PlayerCtrl&): QObject(0) {}
    PlayerCtrl& operator=(const PlayerCtrl&) { return *this; }

    Player*                     mp_player;
    AbstractPlayerController*   mp_abstractPlayerController;
};

#endif // PLAYERCTRL_H
