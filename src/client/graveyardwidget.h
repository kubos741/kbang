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
#ifndef GRAVEYARDWIDGET_H
#define GRAVEYARDWIDGET_H

#include "cardpilewidget.h"

class CardData;

namespace client {

/**
 * The GraveyardWidget class provides a widget that displays the graveyard
 * (discard pile).
 * @author MacJariel
 */
class GraveyardWidget: public CardPileWidget
{
Q_OBJECT
public:
    /**
     * Constructs a GraveyardWidget.
     */
    GraveyardWidget(QWidget* parent = 0);
    /**
     * Destroys the GraveyardWidget.
     */
    virtual ~GraveyardWidget();

    /**
     * Removes the top card from the graveyard and returns it. Use setSecondCard
     * to set a card that is under the returned card (and will become new top
     * of the graveyard).
     */
    virtual CardWidget* pop();

    /**
     * Puts <i>card</i> on top of the graveyard.
     */
    virtual void push(CardWidget* card);

    /**
     * Removes all CardWidgets from the pile and destroy them.
     */
    virtual void clear();

    /**
     * Sets the top card of the graveyard according to given CardData.
     */
    void setFirstCard(const CardData&);

    /**
     * Sets the card under the top card of the graveyard according to
     * given CardData. If cardData.id is 0, second card is removed (in case
     * of graveyard with only one card).
     */
    void setSecondCard(const CardData&);

private:
    CardWidget* setCard(const CardData&);

    CardWidget* mp_firstCard;
    CardWidget* mp_secondCard;
};
}
#endif // GRAVEYARDWIDGET_H
