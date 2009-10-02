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

#include <QPainter>
#include <QPaintEvent>

#include "cardlistwidget.h"
#include "cardwidget.h"
#include "cardwidgetsizemanager.h"

#include "debug/debugblock.h"

using namespace client;

CardListWidget::CardListWidget(QWidget *parent, bool isRevealed):
        CardPocket(parent, isRevealed),
        m_hasBox(1),
        m_hPadding(3),
        m_vPadding(3)
{
}

/* virtual */
CardListWidget::~CardListWidget()
{
}

/* virtual */ QPoint
CardListWidget::newCardPosition() const
{
    //return QPoint(m_hPadding + m_cards.size() * m_moveFactor, m_vPadding);
    return QPoint(cardX(m_cards.size(), 1), m_vPadding);
}

/* virtual */
void CardListWidget::push(CardWidget* card)
{
    DEBUG_BLOCK;
    CardPocket::push(card);
    card->move(newCardPosition());
    card->setParent(this);
    m_cards.push_back(card);
    card->setCardSizeRole(m_cardSizeRole);
    card->updatePixmap();
    card->raise();
    reorder();
    card->show();
}

/* virtual */ CardWidget*
CardListWidget::take(CardId cardId)
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
        qCritical("Cannot find card id %d in CardListWidget. Taking random card.", cardId);
    }
    int cardIndex = (int)qrand() % (int)m_cards.size();
    CardWidget* res = m_cards.takeAt(cardIndex);
    reorder();
    return res;
}

/* virtual */ CardWidget*
CardListWidget::pop()
{
    CardWidget* res = m_cards.takeLast();
    reorder();
    return res;
}

void
CardListWidget::setHasBox(bool hasBox)
{
    m_hasBox = hasBox;
}

void
CardListWidget::clear()
{
    foreach(CardWidget* card, m_cards) {
        card->hide();
        card->deleteLater();
    }
    m_cards.clear();
}

/* virtual */ void
CardListWidget::updateWidgetSize()
{
    QSize cardSize = CardWidgetSizeManager::instance().cardSize(m_cardSizeRole);
    QSize widgetSize(cardSize.width() * 3 + 2 * m_hPadding,
                     cardSize.height() + 2 * m_vPadding);
    m_moveFactor = cardSize.width() / 2 + cardSize.width() / 5;
    setMinimumWidth((int)(cardSize.width() * 3.8));
    setMinimumHeight(cardSize.height() + 2 * m_vPadding);
    updateGeometry();
    reorder();
}

/* virtual */ void
CardListWidget::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    reorder();
}

/* virtual */ void
CardListWidget::paintEvent(QPaintEvent* event)
{
    if (m_hasBox) {
        QPainter painter(this);
        painter.fillRect(event->rect(), QColor(0, 0, 0, 16));
    }
}

void
CardListWidget::reorder()
{
    for(int i = 0; i < m_cards.size(); ++i) {
        m_cards[i]->move(cardX(i), m_vPadding);
    }
}

#if 0   // old implementation of cardX - to be removed later
int
CardListWidget::cardX(int i, bool newCard) const
{
    int cardCount = m_cards.size();
    if (newCard)
        cardCount++;
    int moveFactor;
    if (m_cards.size() >= 2)
        moveFactor = (int)((width() - 2 * m_hPadding -
                            CardWidget::qSize(m_cardSize).width())) / (int)(cardCount - 1);
    else
        moveFactor = m_moveFactor;
    return m_hPadding + i * moveFactor;
}
#endif

int
CardListWidget::cardX(int i, bool newCard) const
{
    const QSize& cardSize = CardWidgetSizeManager::instance().cardSize(m_cardSizeRole);
    int cardCount = m_cards.size();
    if (newCard)
        cardCount++;
    int cSize = (cardCount - 1) * m_moveFactor + cardSize.width();
    if (cSize <= width() - 2 * m_hPadding) {
        return m_hPadding + i * m_moveFactor +
                (int)((width() - 2 * m_hPadding) / 2 - (cSize / 2));
    } else {
        int newMoveFactor = (int)((width() - 2 * m_hPadding -
                                   cardSize.width())) / (int)(cardCount - 1);
        return m_hPadding + i * newMoveFactor;
    }
}
