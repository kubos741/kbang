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


using namespace client;

CardList::CardList(QWidget *parent, const QSize& cardSize)
: CardPocket(parent), m_cardSize(cardSize)
{
    setStyleSheet("client--CardList { padding: 4px; background-color: rgba(0, 0, 0, 64); }");
    //setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSize widgetSize(cardSize.width() * 3, cardSize.height() + 8);
    setMinimumSize(widgetSize);
    setMaximumSize(widgetSize);
    resize(widgetSize);
}

CardList::~CardList()
{
}

void CardList::push(CardWidget* card)
{
    m_cards.push_back(card);
    card->setParent(this);
    card->setCardSize(CardWidget::SIZE_SMALL);
    card->applyNewProperties();
    card->move(0,0);
    card->raise();
    card->show();
    // todo
}

QPoint CardList::newCardPosition() const
{
    return QPoint(0,0);
}

CardWidget* CardList::get(int)
{
    return m_cards.takeLast();
}

CardWidget* CardList::pop()
{
    return m_cards.takeLast();
}

