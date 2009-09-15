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
#ifndef CARDLISTWIDGET_H
#define CARDLISTWIDGET_H

#include <QList>

#include "cardpocket.h"                 // inheritance

namespace client {

/**
 * The CardListWidget class is a widget that stores CardWidget instances and
 * displays them in a row. It is used to show cards in hands and on player's
 * table.
 * @author MacJariel
 */
class CardListWidget: public CardPocket
{
Q_OBJECT
public:
    /**
     * Constructs a CardListWidget which is child of parent.
     */
    CardListWidget(QWidget *parent, bool isRevealed = 1);

    /**
     * Destroys the CardListWidget.
     */
    virtual ~CardListWidget();

    /**
     * Returns the position (relative to this widget) of the next card to be
     * added to pocket. This is used by CardMovementEvent.
     */
    virtual QPoint newCardPosition() const;

    /**
     * Pushes a CardWidget into the pocket.
     */
    virtual void push(CardWidget* card);

    /**
     * Removes a CardWidget with given id from the pocket and returns it. If id is 0,
     * a random card is picked. Use this only with CardListWidgets that contain only
     * unknown cards.
     */
    virtual CardWidget* take(CardId id);

    /**
     * Removes the last CardWidget from the pocket and returns it.
     */
    virtual CardWidget* pop();

    /**
     * Sets the hasBox property. If hasBox is set, the widget is painted on a
     * semi-transparent box. @see paintEvent(QPaintEvent*)
     */
    void setHasBox(bool hasBox);

    /**
     * Removes all CardWidgets from the list and destroys them.
     */
    virtual void clear();

public slots:
    /**
     * Recomputes size of the widget and reorders CardWidgets. The actual CardWidget size
     * from CardWidgetSizeManager is used.
     */
    virtual void updateWidgetSize();

protected:
    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);

    QList<CardWidget*> m_cards;

private:
    void reorder();
    int cardX(int i, bool newCard = 0) const;

    bool            m_hasBox;
    int             m_moveFactor;
    int             m_hPadding, m_vPadding;
};

}

#endif
