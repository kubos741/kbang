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

#include "publicplayerview.h"
#include "privateplayerview.h"
#include "parser/parserstructs.h"


class CardAbstract;
class CharacterCard;
class WeaponCard;
class PlayerCtrl;
class Game;
class GameEventHandler;

/**
 * The Player class represents a kbang player. The instance of this object
 * is created when a client joins a game and it lives as long as the game exists.
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Player : public QObject
{
    Q_OBJECT;
public:
    /**
     * Creates a new instance of Player class. You should always create instances
     * of this class on heap (with the ''new'' operator) because the lifetime of
     * this objects is managed inside.
     */
    Player(Game* game, int id, const QString& name, const QString& password, GameEventHandler* gameEventHandler);


public:

    /**
     * Returns the PlayerCtrl that allows clients to control the player.
     */
    PlayerCtrl* playerCtrl() const;

    /**
     * Returns the game id.
     */
    const int id() const;

    /**
     * Returns the name of the game.
     */
    QString name() const;

    /**
     * Returns the pointer to the game, which the player
     * belongs to.
     */
    Game* game() const;

    bool isCreator() const;

    /**
     *
     */
    bool isOnTurn() const;



    inline int lifePoints()     const { return m_lifePoints; }
    inline int maxLifePoints()  const { return m_maxLifePoints; }
    inline int handSize()       const { return m_cardsInHand.size(); }

    QList<CardAbstract*>    cardsInHand();

    /**
     * Returns the players' character.
     */

    //const CharacterCard& getCharacterCard() const;


    inline PlayerRole role() const { return m_role; }

    int initialCardCount() const;

    int weaponRange() const { return 1; } // TODO

    void modifyLifePoints(int x);

    /**
     * Returns the player struct.
     * @param returnPrivateInfo include private items if set to true
     * (defaults to false)
     */
     StructPlayer structPlayer(bool returnPrivateInfo = 0);

     GameEventHandler* gameEventHandler() const;

    void appendCardToHand(CardAbstract* card);

    /**
     * Removes the given card from players hand. Returns
     * true if player had that card in hand.
     */
    bool removeCardFromHand(CardAbstract* card);


    const PublicPlayerView&  publicView() const;
    const PrivatePlayerView& privateView() const;

    //const PlayerActions* playerActions() const;

    void setRole(const PlayerRole& role);




    inline static Player* player(const PublicPlayerView* publicPlayerView) {
        return publicPlayerView->mp_player;
    }

    
private:
    int                       m_id;
    int                       m_lifePoints;
    int                       m_maxLifePoints;
//    CharacterCard*            m_characterCard;
//    WeaponCard*               m_weaponCard;
    QList<CardAbstract*>      m_cardsInHand;
    QString                   m_name;
    QString                   m_password;
    PlayerRole                m_role;
    Game*                     mp_game;
    PlayerCtrl*               mp_playerCtrl;
    GameEventHandler*         mp_gameEventHandler;

    const PublicPlayerView    m_publicPlayerView;
    const PrivatePlayerView   m_privatePlayerView;
};

#endif
