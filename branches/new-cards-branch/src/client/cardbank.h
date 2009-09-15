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
#include "cardsetinfo.h"
#include "card.h"

class QDomElement;

namespace client {

/**
 * The CardBank singleton class provides a storage for Card objects.
 * As soon as client joins a game, the CardBank singleton is stuffed with
 * CardSets (through CardSetInfo instances). CardWidget instances then use this
 * class to get card graphics. The CardBank instance dies when client leaves
 * the game.
 * @attention Selection of CardSets is hard-coded until support in the protocol
 *            is introduced.
 * @author MacJariel
 */
class CardBank : public QObject
{
Q_OBJECT
public:
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
     * Returns the Card instance according to CardData. Only the name attribute
     * from CardData is used. The type attribute is used only if name is empty,
     * which means an unrevealed card. If CardBank does not contain such Card,
     * 0 is returned.
     */
    const Card* card(const CardData&);

private:
    void addCard(const CardSetInfo&, const QDomElement&);

    QMap<QString, Card*> m_cardStorage;
};

}
#endif // CARDBANK_H
