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
#ifndef PLAYER_H
#define PLAYER_H

#include <QtCore>

#include "playingcard.h"
#include "playercontrollerrunner.h"
#include "publicplayerview.h"
#include "privateplayerview.h"
#include "playeractions.h"

class AbstractPlayerCtrl;
class CharacterCard;
class WeaponCard;
class Client;
class Game;

/**
 * The Player class represents a kbang player. The instance of this object
 * is created when a client joins a game as a player and it lives as long
 * as the game exists.
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Player : public QObject
{
    Q_OBJECT;
public:
    /**
     * Creates a new instance of Player class. You should always create instances
     * of this class on heap (with the ''new'' operator) because the lifetime of
     * this objects is managed inside. After creation of the object, the given client
     * and game are modified.
     */
    Player(int id, const QString& name, const QString& password, Game* game);
    ~Player();

public:

    /**
     * Returns number of life-points.
     */
    inline int lifePoints() const
    {
        return m_lifePoints;
    }

    /**
     * Returns the players' character.
     */
    inline const CharacterCard& getCharacterCard() const
    {
        return *m_characterCard;
    }


    /**
     * Returns the number of cards in player's hand.
     */
    inline int getCardsInHandCount() const
    {
        return m_cardsInHand.size();
    }

    inline QString name() const
    {
        return m_name;
    }

    const PublicPlayerView* publicPlayerView() const
    {
        return &m_publicPlayerView;
    }

    const PrivatePlayerView* privatePlayerView() const
    {
        return &m_privatePlayerView;
    }

    const PlayerActions* playerActions() const
    {
        return &m_playerActions;
    }

    const Game* game() const
    {
        return mp_game;
    }

    /**
     * This method attaches the PlayerController to the Player.
     * Player has to have his controller detached at the moment
     * of calling this method.
     */
     void attachPlayerController(AbstractPlayerCtrl* controller);

    /**
     * This method detaches the PlayerController of the Player.
     */
     void detachPlayerController();

private:
    int                       m_id;
    int                       m_lifePoints;
    CharacterCard*            m_characterCard;
    PlayingCardList           m_cardsInHand;
    WeaponCard*               m_weaponCard;
    QString                   m_name;
    QString                   m_password;
    Game const*               mp_game;
    PlayerControllerRunner    m_runner;
    const PublicPlayerView    m_publicPlayerView;
    const PrivatePlayerView   m_privatePlayerView;
    const PlayerActions       m_playerActions;
};

#endif
