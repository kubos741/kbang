/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
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
#include "cardpilewidget.h"

/**
 *
 * @param parent
 */
CardPileWidget::CardPileWidget(QWidget *parent)
 : CardPocket(parent)
{
    setMinimumSize(CardWidget::normalSize());
    setMaximumSize(CardWidget::normalSize());
}


CardPileWidget::~CardPileWidget()
{

}
CardWidget* CardPileWidget::peek()
{
    return m_cards.top();
}

CardWidget* CardPileWidget::pop()
{
    return m_cards.pop();
}

void CardPileWidget::push(CardWidget* card)
{
    m_cards.push(card);
    card->setParent(this);
    card->setCardSize(CardWidget::SIZE_SMALL);
    card->applyNewProperties();
    card->move(0,0);
    card->raise();
    card->show();
}

QPoint CardPileWidget::newCardPosition() const
{
    return pos();
}
