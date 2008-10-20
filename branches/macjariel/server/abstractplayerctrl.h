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
#ifndef ABSTRACTPLAYERCTRL_H
#define ABSTRACTPLAYERCTRL_H

#include <QThread>

#include "playingcard.h"

class PublicPlayerView;
class PrivatePlayerView;
class PublicGameView;
class PlayerActions;

class CharacterCard;
class CharacterCardList;


/**
 * The AbstractPlayerCtrl class provides the base functionality common
 * to all player controllers. The role of a player controller is to
 * control player actions. These actions can be controlled either by an
 * AI or by humans. By subclassing this class you can write your own AIs.
 *
 * PlayerController communicates with the game with Events (see playerctrlevents.h)
 * and PlayerController can also query information from the PrivatePlayerView,
 * PublicPlayerView and PublicGameView instances. These instances are provided
 * by PlayerControllerRunner when a PlayerController is attached.
 *
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class AbstractPlayerCtrl: public QObject
{
    Q_OBJECT;
public:
    AbstractPlayerCtrl();
    virtual ~AbstractPlayerCtrl();
    virtual void attachPlayer(const PrivatePlayerView*,
                      const PublicGameView*,
                      const PlayerActions*);
    virtual void detachPlayer();

    

    
    virtual void start() = 0;
    
    inline bool isAttached() const
    {
        return m_attached;
    }
    /**
     * This method is called in the beginning of the player's turn and
     * as soon as this method returns, the player's turn is over.
     */
    virtual void playTurn() = 0;

    /**
     * This method is called if the player is under attack.
     * @param attacker the attacking player
     * @param card the card used for attack
     */
    virtual void underAttack(const PublicPlayerView& attacker, const PlayingCard& card) = 0;

    /**
     * This method is called if the player is asked to choose a
     * card from a list of cards (e.g when playing General Store).
     * @param cardList a list of cards to choose from
     * @return reference to one of the cards from cardList
     */
    virtual const PlayingCard& pickACard(const PlayingCardList& cardList) = 0;


    /**
     * This method is called if the player is asked to choose a
     * character card from a list of cards. This happens before
     * the game starts.
     * @param characterList a list of characters to choose from
     * @return reference to one of the cards from characterList
     */
    virtual const CharacterCard& pickACharacter(const CharacterCardList& characterList) = 0;

public slots:
    /**
     * This slot is called when any player recieves some cards.
     * @param player the player that recieved cards
     * @param cardList list of cards that was recieved - if some cards
     * were not revealed to the public, the object of UnknownPlayingCard is
     * in the list instead.
     *
     */
    virtual void playerRecievesCards(const PublicPlayerView& player,
                                     const PlayingCardList& cardList) = 0;


    /**
     * This slot is called when any player plays a card. Some cards needs closer specification when
     * played (e.g when playing Panic, target player and target card is required).
     * @param player the player that plays the card
     * @param card the played card
     * @param targetPlayer the target player (if necessary)
     * @param targetCard the target card (if necessary)
     */
    virtual void playerPlaysCard(const PublicPlayerView&  player,
                                 const PlayingCard&     card,
                                 const PublicPlayerView*  targetPlayer = NULL,
                                 const PlayingCard*     targetCard   = NULL) = 0;


    /**
     * This slot is called when any player discards some cards.
     * @param player the player that discards cards
     * @param cardList list of cards that were discarded
     */
    virtual void playerDiscardsCard(const PublicPlayerView& player,
                                    const PlayingCardList& cardList) = 0;



    int gameId() const;

public slots:
    /**
     * @param int senderId
     * @param QString senderName
     * @param QString message
     */
    virtual void incomingChatMessage(int, const QString&, const QString&) {}

protected:
    const PrivatePlayerView* mp_privatePlayerView;
    const PublicGameView*    mp_publicGameView;
    const PlayerActions*     mp_playerActions;
    bool                     m_attached;
};

#endif
