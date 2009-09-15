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
#include "deckwidget.h"
#include "cardwidget.h"

using namespace client;

DeckWidget::DeckWidget(QWidget *parent):
        CardPileWidget(parent, 0)
{
    setPocketType(POCKET_DECK);
    newCard();
}

/* virtual */
DeckWidget::~DeckWidget()
{
}

/* virtual */ void
DeckWidget::push(CardWidget* card)
{
    card->hide();
    card->deleteLater();
}

/* virtual */ CardWidget*
DeckWidget::pop()
{
    return newCard();
}

/* virtual */ void
DeckWidget::clear()
{
}

CardWidget*
DeckWidget::newCard()
{
    CardWidget* card = new CardWidget(this);
    card->cardData().type = CARDTYPE_PLAYING;
    card->setCardSizeRole(m_cardSizeRole);
    card->updatePixmap();
    card->raise();
    card->move(newCardPosition());
    card->show();
    card->setOwnerId(0);
    card->setPocketType(POCKET_DECK);
    return card;
}
