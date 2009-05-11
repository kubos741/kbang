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

#include <stdlib.h>

#include <QSize>
#include <QPainter>
#include <QPaintEvent>


using namespace client;

CardList::CardList(QWidget *parent):
        CardPocket(parent),
        m_cardSize(CardWidget::SIZE_SMALL),
        m_hPadding(3),
        m_vPadding(3)
{
    //setStyleSheet("client--CardList { padding: 4px; background-color: rgba(0, 0, 0, 64); }");
}

CardList::~CardList()
{
}

void CardList::setCardSize(const CardWidget::Size& cardSize)
{
    m_cardSize = cardSize;
    QSize cardS = CardWidget::qSize(cardSize);
    QSize widgetSize(cardS.width() * 3 + 2 * m_hPadding, cardS.height() + 2 * m_vPadding);
    m_moveFactor = cardS.width() / 2 + cardS.width() / 5;
    setMinimumWidth((int)(cardS.width() * 3.5));
    setMinimumHeight(cardS.height() + 2 * m_vPadding);
    updateGeometry();
}

void CardList::push(CardWidget* card)
{
    CardPocket::push(card);
    card->move(newCardPosition());
    card->setParent(this);
    m_cards.push_back(card);
    card->setSize(m_cardSize);
    card->validate();
    card->raise();
    reorder();
    card->show();
}

QPoint CardList::newCardPosition() const
{
    //return QPoint(m_hPadding + m_cards.size() * m_moveFactor, m_vPadding);
    return QPoint(cardX(m_cards.size(), 1), m_vPadding);
}


CardWidget* CardList::take(int cardId)
{
    if (m_cards.size() == 0) {
        qCritical("Trying to take from empty card list.");
        return 0;
    }
    if (cardId != 0) {
        foreach (CardWidget* card, m_cards) {
            if (card->cardData().id == cardId) {
                m_cards.removeAll(card);
                reorder();
                return card;
            }
        }
        qCritical("Cannot find card id %d in CardList. Taking random card.", cardId);
    }
    int cardIndex = (int)random() % (int)m_cards.size();
    CardWidget* res = m_cards.takeAt(cardIndex);
    reorder();
    return res;
}

CardWidget* CardList::pop()
{
    CardWidget* res = m_cards.takeLast();
    reorder();
    return res;
}

void CardList::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(event->rect().intersect(contentsRect()), QColor(0, 0, 0, 16));
}

void CardList::clear()
{
    foreach(CardWidget* card, m_cards)
        card->deleteLater();
    m_cards.clear();
}

void CardList::reorder()
{
    for(int i = 0; i < m_cards.size(); ++i) {
        m_cards[i]->move(cardX(i), m_vPadding);
    }
}

/*
int CardList::cardX(int i, bool newCard) const
{
    int cardCount = m_cards.size();
    if (newCard)
        cardCount++;
    int moveFactor;
    if (m_cards.size() >= 2)
        moveFactor = (int)((width() - 2 * m_hPadding - CardWidget::qSize(m_cardSize).width())) / (int)(cardCount - 1);
    else
        moveFactor = m_moveFactor;
    return m_hPadding + i * moveFactor;
}
*/

int CardList::cardX(int i, bool newCard) const
{
    int cardCount = m_cards.size();
    if (newCard)
        cardCount++;
    int cSize = cardCount * m_moveFactor + CardWidget::qSize(m_cardSize).width();
    if (cSize <= width() - 2 * m_hPadding) {
        return m_hPadding + i * m_moveFactor;
    } else {
        int newMoveFactor = (int)((width() - 2 * m_hPadding - CardWidget::qSize(m_cardSize).width())) / (int)(cardCount - 1);
        //i * NF = todoWidth - 2*hpadding - width
        return m_hPadding + i * newMoveFactor;
    }
}


