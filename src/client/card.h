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

#include "gametypes.h"

#include <QPixmap>

class CardData;

namespace client
{
class CardBank;             // Friend class

/**
 * The Card class represents a Bang! card. Those Cards are usually loaded on
 * the startup by the CardBank class, which then manages them. In Bang! a
 * card can have more pictures than one (eg. Bang, Missed) and the used picture
 * depends only on card suit and rank. To achieve this feature, Cards can
 * be linked with multiple pictures, identified by suit and rank set.
 *
 * A Card instance is initialized by calling the constructor and by using
 * the addGraphics() method to attach pictures. After that, card parameters
 * can be obtained by calling const Card methods.
 *
 * Although Card pictures can contain suit and rank information, it is wise
 * to retouch card pictures and remove those signs. After that you can use
 * this class to paint the suit and rank signs in the runtime. The pictures
 * for those signs are defined in the parent CardSet and can be obtained using
 * CardBank::suit() and CardBank::rank() methods.
 *
 * @author MacJariel
 */
class Card: public QObject
{
    friend class CardBank;

    /**
     * Constructs a new Card according to given parameters.
     * @param cardBank The CardBank that creates this card. CardBank
     *                 automatically becomes the parent of this instance.
     * @param name The card name.
     * @param type The card type.
     * @param cardSetName The name of the CardSet this card comes from.
     */
    Card(CardBank* cardBank, const QString& name, CardType type,
         const QString& cardSetName);

    /**
     * Loads the image from <i>gfx</i> file and links it to this Card.
     *
     * @param gfx The full path to the image.
     * @param suitString Text string that describes which suit is related
     *                   to this image. Use empty string for all suits.
     * @param rankString Text string that describes which ranks are related
     *                   to this graphics. It can contain either a single rank,
     *                   or a range (e.g. "8", "10-K"). Use empty string for
     *                   all ranks, instead of using "2-A".
     * @param renderSigns Tells whether this graphics requires runtime painting
     *                    of suit and rank signs.
     * @note Only playing cards can have suits and ranks. The last three
     *       parameters are ignored in case of other type of card.
     */
    void addGraphics(const QString& gfx, const QString& suitString = QString(),
                     const QString& rankString = QString(), bool renderSigns = 1);

public:
    /**
     * Returns the name (string identifier) of the card.
     */
    inline CardName name()  const {
        return m_name;
    }

    /**
     * Returns the type of the card.
     */
    inline CardType type() const {
        return m_type;
    }

    /**
     * Returns the name of the CardSet.
     */
    inline QString cardSetName() const {
        return m_cardSetName;
    }

    /**
     * Returns the picture for given card. The suit and rank information
     * from CardData is used to decide which graphics is used and to
     * render signs (if renderSigns is set for given graphics).
     * If the Card is not playing card (resp. has only one graphics), the first
     * (resp. the only one) graphics is used. Otherwise the target graphics is
     * chosen according to suit and rank information. If no graphics is
     * matching given criteria, a null picture is returned.
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
    CardName        m_name;
    CardType        m_type;
    QString         m_cardSetName;
    QList<Graphics> m_graphics;
};
}
#endif
