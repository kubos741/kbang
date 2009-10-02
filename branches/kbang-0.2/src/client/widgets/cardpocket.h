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
#ifndef CARDPOCKET_H
#define CARDPOCKET_H

#include <QFrame>
#include <QPoint>

#include "gametypes.h"                  // enum PocketType
#include "clienttypes.h"                // enum CardSizeRole

namespace client
{

class CardWidget;

/**
 * The CardPocket class is the base class of all widgets that can hold cards
 * (CardWidget instances). This class manages common properties of card pockets
 * and defines a common interface.
 * @author MacJariel
 */
class CardPocket : public QFrame
{
Q_OBJECT
protected:
    CardPocket(QWidget *parent, bool isRevealed);
    virtual ~CardPocket();

public:
    /**
     * Returns whether this pocket can contain revealed cards.
     */
    inline bool isRevealed() const {
        return m_isRevealed;
    }

    /**
     * Returns the owner's id.
     */
    inline PlayerId ownerId() const {
        return m_ownerId;
    }

    /**
     * Returns the position (relative to this widget) of the next card to be
     * added to pocket. This is used by CardMovementEvent.
     */
    virtual QPoint newCardPosition() const = 0;

    /**
     * Pushes a CardWidget into the pocket.
     */
    virtual void push(CardWidget*);

    /**
     * Removes all CardWidgets from the pocket.
     */
    virtual void clear() = 0;

    /**
     * Sets whether this pocket can contain revealed cards. If set to false,
     * cards that are pushed into this pocket are automatically unrevealed.
     * @note The unrevealing is implemented in CardMovementEvent.
     */
    void setRevealed(bool isRevealed);

    /**
     * Sets the PocketType to given type.
     */
    void setPocketType(const PocketType&);

    /**
     * Sets the owner of the pocket. Pockets without owner should be set to 0.
     */
    void setOwnerId(PlayerId);

    /**
     * Sets the CardSizeRole of the pocket. This role is used on all CardWidget
     * that this instance contains.
     */
    void setCardSizeRole(CardSizeRole);


public slots:
    /**
     * Recomputes size of the widget and reorders CardWidgets. The actual CardWidget size
     * from CardWidgetSizeManager is used.
     */
    virtual void updateWidgetSize() {}

signals:
    /**
     * This signal is emitted when CardPocket's newCardPosition() changes.
     * @todo make sure it's properly implemented
     */
    void newCardPositionChanged(const QPoint&);

protected:
    bool            m_isRevealed;
    PocketType      m_pocketType;
    PlayerId        m_ownerId;
    CardSizeRole    m_cardSizeRole;
};
}
#endif
