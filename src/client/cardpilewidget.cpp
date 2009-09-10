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
#include "cardpilewidget.h"
#include "cardwidget.h"

using namespace client;

CardPileWidget::CardPileWidget(QWidget *parent):
        CardPocket(parent),
        m_padding(4, 4)
{
    setCardSizeRole(CARD_SIZE_NORMAL);
}

/* virtual */
CardPileWidget::~CardPileWidget()
{
}

/* virtual */ QPoint
CardPileWidget::newCardPosition() const
{
    return QPoint(m_padding.width(), m_padding.height());
}

/* virtual */ void
CardPileWidget::push(CardWidget* card)
{
    CardPocket::push(card);
    m_cards.push(card);
    card->setParent(this);
    card->setCardSizeRole(m_cardSizeRole);
    card->updatePixmap();
    card->move(CardPileWidget::newCardPosition());
    card->raise();
    card->show();
}

/* virtual */ CardWidget*
CardPileWidget::peek()
{
    return m_cards.top();
}

/* virtual */ CardWidget*
CardPileWidget::pop()
{
    return m_cards.pop();
}

/* virtual */ void
CardPileWidget::clear()
{
    foreach (CardWidget* cardWidget, m_cards) {
        cardWidget->hide();
        cardWidget->deleteLater();
    }
    m_cards.clear();
}

/* virtual */ void
CardPileWidget::updateWidgetSize()
{
    QSize cardSize(CardWidgetSizeManager::instance().size(m_cardSizeRole));
    QSize widgetSize(cardSize + (2 * m_padding));
    setMinimumSize(widgetSize);
    setMaximumSize(widgetSize);
    resize(widgetSize);
}
