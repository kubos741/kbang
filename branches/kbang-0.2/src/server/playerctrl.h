/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
 *   echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil"                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef PLAYERCTRL_H
#define PLAYERCTRL_H

#include "gameexceptions.h"
#include "gamestructs.h"

#include <QObject>

class PublicPlayerView;
class PrivatePlayerView;

/**
 * The PlayerCtrl class provides complete interface for controlling a player.
 * @todo The documentation is too brief.
 */
class PlayerCtrl:  QObject
{
Q_OBJECT
friend class Player;

public slots:
    /**
     * The controlled player will leave the game.
     * @warning This method should not be used by AIs.
     */
    void leaveGame();

    /**
     * Starts the game.
     * @throws PermissionDeniedException Player is not allowed to start the game.
     * @throws BadGameStateException Either the game is already started, or
     *         the right conditions are not met, eg. there is not enough
     *         players in the game.
     */
    void startGame();

    /**
     * The controlled player will draw (typically two) cards from the deck.
     * @throws BadGameStateException The rules does not allow to draw at the
     *         moment.
     */
    void draw();

    /**
     * The controlled player will finish his turn.
     * @throws TooManyCardsInHandException Player has too many cards in hand
     *         to finish his turn.
     * @throws BadGameStateException The rules does not allow to finish turn
     *         at the moment.
     */
    void finishTurn();

    /**
     * The controlled player will discard a card.
     * @param cardId The id of the card.
     * @throws BadCardException Card cannot be found in player's hand.
     * @throws BadGameStateException Player cannot discard a card at the moment.
     */
    void discardCard(CardId cardId);

    /**
     * The controlled player will use his ability.
     */
    void useAbility(const ActionUseAbilityData&);

    /**
     * The controlled player will play a card.
     */
    void playCard(const ActionPlayCardData&);

    /**
     * The controlled player will pass.
     */
    void pass();

    /**
     * The controlled player will send a chat message.
     */
    void sendChatMessage(const QString&);

public:
    CardView* card(int cardId) const;


    const PublicGameView& publicGameView() const;
    const PublicPlayerView& publicPlayerView(int playerId = 0) const;
    const PrivatePlayerView& privatePlayerView() const;



    /**
     * Creates a new game and automatically puts the player in. This should be used
     * exclusively by nonAI client classes, as AIs typically don't create games.
     * \note The client class gets the PlayerCtrl instance through the
     *       GameEventListener::onPlayerInit(PlayerCtrl*) method.
     * \param game The game structure.
     * \param player The player structure.
     */
    static void createGame(const CreateGameData&, const CreatePlayerData&, GameEventListener*);

    /**
     * Puts the player to the game.
     * \note The client class gets the PlayerCtrl instance through the
     *       GameEventListener::onPlayerInit(PlayerCtrl*) method.
     *
     * \param gameId The id of the game.
     * \param player The player structure.
     * \throws BadGameException The game does not exist.
     * \throws BadGameStateException The game has already started.
     */
    static void joinGame(int gameId, const QString& gamePassword, const CreatePlayerData&, GameEventListener*);

    static void replacePlayer(int gameId, int playerId, const QString& password, const CreatePlayerData&, GameEventListener*);


    /**
     * Returns the StructServerInfo struct.
     */
    static ServerInfoData serverInfo();

    /**
     * Returns the list of PublicGameViews.
     */
    static QList<const PublicGameView*> publicGameList();

    /**
     * Returns the PublicGameView of the game specified by gameId.
     */
    static const PublicGameView& publicGameView(int gameId);


private:
    PlayerCtrl(Player* player);
    PlayerCtrl(const PlayerCtrl&): QObject(0) {}
    PlayerCtrl& operator=(const PlayerCtrl&) { return *this; }

    Player*                     mp_player;

};

#endif // PLAYERCTRL_H
