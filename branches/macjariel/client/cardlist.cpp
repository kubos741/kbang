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
#include "cardlist.h"
#include "cardwidget.h"

#include <QSize>

using namespace client;

CardList::CardList(QWidget *parent, const CardWidget::Size& cardSize)
: CardPocket(parent), m_cardSize(cardSize), m_hPadding(3), m_vPadding(3)
{
    setStyleSheet("client--CardList { padding: 4px; background-color: rgba(0, 0, 0, 64); }");
    //setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSize cardS = CardWidget::size(cardSize);
    QSize widgetSize(cardS.width() * 3 + 2 * m_hPadding, cardS.height() + 2 * m_vPadding);
    m_moveFactor = cardS.width() / 2;
    setMinimumSize(widgetSize);
    setMaximumSize(widgetSize);
    resize(widgetSize);
}

CardList::~CardList()
{
}

void CardList::push(CardWidget* card)
{
    card->move(newCardPosition());
    card->setParent(this);
    m_cards.push_back(card);
    card->setCardSize(m_cardSize);
    card->applyNewProperties();
    card->raise();
    card->show();
    // todo
}

QPoint CardList::newCardPosition() const
{
    return QPoint(m_hPadding + m_cards.size() * m_moveFactor, m_vPadding);
}

CardWidget* CardList::get(int)
{
    return m_cards.takeLast();
}

CardWidget* CardList::pop()
{
    return m_cards.takeLast();
}

