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
#ifndef CARDPILEWIDGET_H
#define CARDPILEWIDGET_H

#include <QStack>
#include <QSize>

#include "cardpocket.h"

namespace client
{

class CardWidget;

/**
 * The CardPileWidget class is a widget that stores CardWidget instances and
 * displays them on a pile. The CardPileWidget class is used to display
 * discard pile (graveyard).
 *
 * @note Client only needs to remember the top card of the pile, so there's
 *       no need to simulate the real pile of cards and store all of them.
 *       Currently only subclasses of this class are used, so we are not
 *       wasting, but the most of the code here is never used and maybe it
 *       should be removed.
 * @author MacJariel
 */
class CardPileWidget : public CardPocket
{
Q_OBJECT
public:
    /**
     * Constructs a CardPileWidget which is child of parent.
     */
    CardPileWidget(QWidget *parent, bool isRevealed);

    /**
     * Destroys the CardPileWidget.
     */
    virtual ~CardPileWidget();

    /**
     * Returns the position (relative to this widget) of the next card to be
     * added to pocket. This is used by CardMovementEvent.
     */
    virtual QPoint newCardPosition() const;

#if 0
    /**
     * Pushes a CardWidget on top of the pile.
     */
    virtual void push(CardWidget* card);

    /**
     * Returns the top-most CardWidget without removing it from the pile.
     */
    virtual CardWidget* peek();

    /**
     * Removes the top-most CardWidget from the pile and returns it.
     */
    virtual CardWidget* pop();

    /**
     * Removes all CardWidgets from the pile and destroy them.
     */
    virtual void clear();
#endif

public slots:
    /**
     * Recomputes size of the widget and reorders CardWidgets. The actual CardWidget size
     * from CardWidgetSizeManager is used.
     */
    virtual void updateWidgetSize();

#if 0
protected:
    QStack<CardWidget*> m_cards;
#endif

private:
    QSize            m_padding;   
};
}
#endif
