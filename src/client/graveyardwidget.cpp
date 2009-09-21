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

#include "graveyardwidget.h"
#include "cardwidget.h"

using namespace client;

GraveyardWidget::GraveyardWidget(QWidget* parent):
        CardPileWidget(parent, 1),
        mp_firstCard(0),
        mp_secondCard(0)
{
    setPocketType(POCKET_GRAVEYARD);
}

/* virtual */
GraveyardWidget::~GraveyardWidget()
{
}

/* virtual */ CardWidget*
GraveyardWidget::pop()
{
    CardWidget* result = mp_firstCard;
    mp_firstCard = mp_secondCard;
    mp_secondCard = 0;
    return result;
}

/* virtual */
CardWidget* GraveyardWidget::peek()
{
    return mp_firstCard;
}

/* virtual */ void
GraveyardWidget::push(CardWidget* card)
{
    CardPocket::push(card);
    mp_secondCard->deleteLater();
    mp_secondCard = 0;
    mp_firstCard = card;
    card->setParent(this);
    card->setCardSizeRole(m_cardSizeRole);
    card->updatePixmap();
    card->move(newCardPosition());
    card->raise();
    card->show();
}

/* virtual */ void
GraveyardWidget::clear()
{
    if (mp_firstCard) {
        mp_firstCard->hide();
        mp_firstCard->deleteLater();
        mp_firstCard = 0;
    }
    if (mp_secondCard) {
        mp_secondCard->hide();
        mp_secondCard->deleteLater();
        mp_secondCard = 0;
    }
}

void
GraveyardWidget::setFirstCard(const CardData& cardData)
{
    if (cardData.id == 0)
        return;
    if (mp_firstCard) mp_firstCard->deleteLater();
    mp_firstCard = setCard(cardData);
    mp_firstCard->show();
}

void
GraveyardWidget::setSecondCard(const CardData& cardData)
{
    Q_ASSERT(mp_secondCard == 0);
    Q_ASSERT(mp_firstCard != 0);
    if (cardData.id == 0) {
        return;
    }

    mp_secondCard = setCard(cardData);
    mp_secondCard->stackUnder(mp_firstCard);
    mp_secondCard->show();
}

CardWidget*
GraveyardWidget::setCard(const CardData& cardData)
{
    CardWidget* res = new CardWidget(this);
    res->setCardSizeRole(m_cardSizeRole);
    res->setCardData(cardData);
    res->updatePixmap();
    res->move(newCardPosition());
    res->setOwnerId(0);
    res->setPocketType(POCKET_GRAVEYARD);
    return res;
}
