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

#ifndef PLAYINGCARD_H
#define PLAYINGCARD_H

#include "gamestructs.h"        // CardData
#include "servertypes.h"

#include <QObject>

class Game;
class Player;
class GameTable;
class GameCycle;

/**
 * The PlayingCard class is the base class for all playing cards. Each playing
 * card has the following attributes:
 *  - id   - the unique numeric identifactor of the card
 *  - name - e.g. bang, missed, ...
 *  - suit - e.g. Diamonds, Spades, ...
 *  - rank - e.g. 7, K, A
 *
 * Moreover, each card also rembembers where it's located at the moment. This
 * is achieved by storing the PocketType and Owner. The class that moves cards
 * (the GameTable class) is responsible to maintain these values correct.
 *
 * @author MacJariel <MacJariel@gmail.com>
 */
class PlayingCard: public QObject
{
Q_OBJECT
public:
    PlayingCard(Game*, CardId, PlayingCardName, CardSuit, CardRank);
    virtual ~PlayingCard();

    inline CardId           id()         const { return m_cardData.id;  }
    inline PlayingCardName  name()       const { return m_name;         }
    inline CardSuit         suit()       const { return m_cardData.suit;}
    inline CardRank         rank()       const { return m_cardData.rank;}
    inline Player*          owner()      const { return mp_owner;       }
    inline PocketType       pocketType() const { return m_pocketType;   }
    inline bool             isVirtual()  const { return m_isVirtual;    }
    inline PlayingCard*     master()     const { return mp_master;      }
    inline const CardData&  cardData()   const { return m_cardData;     }

    virtual void play();
    virtual void play(Player* targetPlayer);
    virtual void play(PlayingCard* targetCard);

    void assertInHand() const;
    void assertOnTable() const;

    void setVirtual(PlayingCard* master);
    void setVirtual(Player* owner, PocketType pocket);

protected:
    inline Game* game() const { return mp_game; }
    GameTable* gameTable() const;
    GameCycle* gameCycle() const;

    void setName(PlayingCardName);

    void discard();


    virtual void move(Player*, PocketType);

private:
    void insertIntoPocket();
    void removeFromPocket();

    CardData        m_cardData;
    PlayingCardName m_name;
    Player*         mp_owner;
    PocketType      m_pocketType;
    Game*           mp_game;
    bool            m_isRevealed;
    bool            m_isVirtual;
    PlayingCard*    mp_master;
};

#endif // PLAYINGCARD_H
