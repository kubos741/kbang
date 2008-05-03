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

#include <QObject>
#include "playingcard.h"


class CharacterCard;
class WeaponCard;
class AbstractPlayerCtrl;

/**
 * @author MacJariel <macjariel@users.sourceforge.net>
 */
class Player : public QObject
{
    Q_OBJECT

friend class GameArbiter;

    Player(QObject *parent);

    ~Player();
public:

    /**
     * Returns number of life-points.
     */
    inline int getLifePoints() const
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

    /**
     * This method attaches the PlayerController to the Player.
     * Player has to have his controller detached at the moment
     * of calling this method.
     */
    void attachPlayerController(const AbstractPlayerCtrl* controller);

    /**
     * This method detaches the PlayerController of the Player.
     */
    void detachPlayerController();

private:
    int                       m_lifePoints;
    CharacterCard*            m_characterCard;
    PlayingCardList           m_cardsInHand;
    WeaponCard*               m_weaponCard;
    const AbstractPlayerCtrl* m_controller;





};

#endif
