/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
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

#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <QString>
#include "parser/parserstructs.h"


class PlayingCard;
class PublicPlayerView;
class PlayerCtrl;

/**
 * Abstract class that defines the interface to notify back PlayerControllers
 * about events.
 *
 * \note This class could be renamed. Candidates are:
 *   * GameEventsHandler
 */
class GameEventHandler
{
public:
    //GameEventHandler();
    /**
     * This method is called when someone sends a chat message.
     * \param player The publicPlayerView of sender.
     * \param playerName The name of the sender.
     * \param message The chat message.
     */
    virtual void onIncomingMessage(const PublicPlayerView& publicPlayerView, const QString& message) = 0;


    /**
     * This method is created right after the Player is created.
     * The controlling client gets the PlayerCtrl instance that
     * is used to control player and can do some caching of persistent
     * members (for example PublicGameView, PrivatePlayerView objects).
     */
    virtual void onPlayerInit(PlayerCtrl* playerCtrl) = 0;

    virtual void onGameSync() = 0;

    virtual void onPlayerExit() = 0;

    virtual void onPlayerJoinedGame(const PublicPlayerView&) = 0;

    virtual void onPlayerLeavedGame(const PublicPlayerView&) = 0;

    virtual void onPlayerDied(const PublicPlayerView&) = 0;

    virtual void onGameStartabilityChanged(bool isStartable) = 0;
    
    virtual void onGameStarted() = 0;

    /**
     * This method is called when a player draws a card. If the controlled player draws a card, the
     * card attribute points to that card, otherwise card is null.
     */
    virtual void onPlayerDrawedCard(int playerId, const PlayingCard* card) = 0;

    virtual void onPlayerDiscardedCard(int playerId, PocketType pocket, const PlayingCard* card) = 0;

    virtual void onPlayerPlayedCard(int playerId, const PlayingCard* card) = 0;

    virtual void onPlayerPlayedOnTable(int playerId, const PlayingCard* card) = 0;

    virtual void onPlayedCardsCleared() = 0;

    virtual void onGameContextChange(const GameContextData&) = 0;

    virtual void onLifePointsChange(const PublicPlayerView&, int oldLifePoints, int newLifePoints) = 0;

    virtual void onActionRequest(ActionRequestType requestType) = 0;

    virtual ~GameEventHandler() {};
};


#endif // GameEventHandler_H
