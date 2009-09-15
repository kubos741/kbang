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
#ifndef DECKWIDGET_H
#define DECKWIDGET_H

#include <cardpilewidget.h>

namespace client {

/**
 * The DeckWidget class is a widget that displays the main deck of
 * playing cards.
 * @author MacJariel
 */
class DeckWidget : public CardPileWidget
{
Q_OBJECT
public:
    /**
     * Constructs a DeckWidget which is child of parent.
     */
    DeckWidget(QWidget* parent);

    /**
     * Destroys the DeckWidget.
     */
    virtual ~DeckWidget();

    /**
     * Pushes a CardWidget on top of the deck.
     */
    virtual void push(CardWidget* card);

    /**
     * Removes the top-most CardWidget from the deck and returns it.
     */
    virtual CardWidget* pop();

    /**
     * Removes all CardWidgets from the pile and destroy them.
     */
    virtual void clear();

private:
    CardWidget* newCard();
};
}
#endif
