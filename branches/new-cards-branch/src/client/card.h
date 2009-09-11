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
#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QPixmap>
#include "gametypes.h"

class CardData;

namespace client
{
class CardBank;             // Friend class

/**
 * The Card class provides a mechanism to obtain/generate graphics for cards in
 * KBang client. CardBank class is responsible for creating and holding Card
 * instances, that are then used by CardWidget to get the right graphics.
 *
 * @author MacJariel
 */
class Card: public QObject
{
    friend class CardBank;

    /**
     * Constructs a new Card according to given parameters.
     *
     * @param cardBank The CardBank that creates this card. CardBank
     *                 automatically becomes the parent of this instance.
     * @param name The card name.
     * @param type The card type.
     * @param cardSetName The name of CardSet this card comes from.
     */
    Card(CardBank* cardBank, const QString& name, CardType type,
         const QString& cardSetName);

    /**
     * Adds graphics to the card. In most cases each Card instance has just
     * one graphics associated with it, but in some more advanced scenarios
     * one Card can have more graphics. For example, there are more graphics
     * for Bang! card. You can distinguish one from another by specifying
     * suits and ranks. The resulting set of (suit,rank) pairs is determined
     * by cartesian product of suitString and rankString sets.
     *
     * Note that sets of (suit,rank) pairs for all graphics should be
     * disjoint.
     *
     * @param gfx Text string that is pointing to the graphics file.
     * @param suitString Text string that describes which suits are related
     *                   to this graphics. It can contain a comma separated
     *                   list of suits. An empty string means all suits.
     * @param rankString Text string that describes which ranks are related
     *                   to this graphics. It can contain a comma separated
     *                   list of ranks or rank ranges. For example: 2-5,J-A.
     *                   An empty string means all ranks.
     * @param renderSings Whether sings (suits and ranks) should be added
     *                    to graphics or not.
     */
    void addGraphics(const QString& gfx, const QString& suitString = QString(),
                     const QString& rankString = QString(), bool renderSigns = 0);

public:
    inline QString  name()  const { return m_name;  } ///< Returns card name.
    inline CardType type()  const { return m_type;  } ///< Returns card type.
    inline QString  cardSetName() const { return m_cardSetName; } ///< Returns name of the source CardSet.

    /**
     * Returns the graphics for given card. The suit and rank information
     * from CardData is used to decide which graphics is used and to
     * render signs (if renderSigns is set for given graphics).
     * If the Card has only one graphics, it is returned without (suit,rank)
     * matching. Else, the target graphics is chosen according to (suit,rank)
     * information, or unspecified graphics is returned if no matching
     * graphics is found.
     */
    QPixmap pixmap(const CardData&) const;

private:
    struct Graphics {
        Graphics(): rankFrom(2), rankTo(14), suit(SUIT_INVALID) {}
        CardRank rankFrom, rankTo;  ///< rank range
        CardSuit suit;              ///< suit
        bool     renderSigns;
        QPixmap  image;
    };

    CardBank*       m_cardBank;
    QString         m_name;
    CardType        m_type;
    QString         m_cardSetName;
    QList<Graphics> m_graphics;
};
}
#endif
