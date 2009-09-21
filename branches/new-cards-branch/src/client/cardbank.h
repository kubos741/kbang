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

#ifndef CARDBANK_H
#define CARDBANK_H

#include <QMap>
#include <QPixmap>
#include "cardsetinfo.h"
#include "card.h"

class QDomElement;

namespace client {

/**
 * The CardBank singleton class provides a storage for Card objects.
 * @attention Selection of CardSets is hard-coded until support in the protocol
 *            is introduced.
 * @author MacJariel
 */
class CardBank : public QObject
{
Q_OBJECT
public:
   /**
    * Returns a reference to the CardBank singleton instance.
    */
    inline static CardBank& instance() {
        static CardBank singleton;
        return singleton;
    }

protected:
    /**
     * Constructs an empty CardBank.
     */
    CardBank();

    /**
     * Destroys the CardBank.
     */
    virtual ~CardBank();

public:
    /**
     * Loads given card set. CardBank can hold more than one card set, but
     * you should not load the same card set more than once.
     */
    void loadCardSet(const CardSetInfo&);

    /**
     * Returns a pointer to the Card instance according to CardData. Only the
     * name attribute from CardData is used. The type attribute is used only if
     * name is empty, which is used for an unrevealed card. If CardBank does
     * not contain such Card, NULL pointer is returned.
     */
    const Card* card(const CardData&) const;

    QPixmap rank(const QString& cardSetName, CardRank) const;

    QPixmap suit(const QString& cardSetName, CardSuit) const;

    QPoint renderSignsPosition(const QString& cardSetName) const;

private:
    void addCard(const CardSetInfo&, const QDomElement&);


    struct SignBank {
        QMap<CardRank, QPixmap> ranks;
        QMap<CardSuit, QPixmap> suits;
        QPoint renderSignsPosition;
    };

    QMap<QString, Card*>    m_cardStorage;
    QMap<QString, SignBank> m_signStorage;
};

}
#endif // CARDBANK_H
