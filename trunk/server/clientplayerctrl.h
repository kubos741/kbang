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
#ifndef CLIENTPLAYERCTRL_H
#define CLIENTPLAYERCTRL_H

#include <abstractplayerctrl.h>

class Client;
class ClientXmlParser;
class Player;

/**
 * The ClientPlayerCtrl class provides a wrapper to the...
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class ClientPlayerCtrl: public AbstractPlayerCtrl
{
    friend class Client;
    Q_OBJECT;
private:
    ClientPlayerCtrl(Client* client, ClientXmlParser* parser);
    ~ClientPlayerCtrl();


public:
    virtual void detachPlayer();

    

// API FOR Client class;
public slots:
    /**
     * Tells the client to leave the game.
     */
    void actionLeaveGame();
    

    
    

public slots:

    //void leaveGame();
    
    
    
    virtual void start();    


//    virtual bool event(QEvent* e);

    virtual void playTurn();

    /**
     * This method is called if the player is under attack.
     * @param attacker the attacking player
     * @param card the card used for attack
     */
    virtual void underAttack(const PublicPlayerView& attacker, const PlayingCard& card);

    /**
     * This method is called if the player is asked to choose a
     * card from a list of cards (e.g when playing General Store).
     * @param cardList a list of cards to choose from
     * @return reference to one of the cards from cardList
     */
    virtual const PlayingCard& pickACard(const PlayingCardList& cardList);


    /**
     * This method is called if the player is asked to choose a
     * character card from a list of cards. This happens before
     * the game starts.
     * @param characterList a list of characters to choose from
     * @return reference to one of the cards from characterList
     */
    virtual const CharacterCard& pickACharacter(const CharacterCardList& characterList);

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
                                     const PlayingCardList& cardList);


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
                                 const PlayingCard*     targetCard   = NULL);


    /**
     * This slot is called when any player discards some cards.
     * @param player the player that discards cards
     * @param cardList list of cards that were discarded
     */
    virtual void playerDiscardsCard(const PublicPlayerView& player,
                                    const PlayingCardList& cardList);

private:
    Client* mp_client;
    ClientXmlParser* mp_parser;
};

#endif
