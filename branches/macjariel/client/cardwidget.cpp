/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
 *   echo "dmailet@gbalt.dob" | tr "edibmlt" "ecrmjil"                   *
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
#include <QtCore>
#include <QtDebug>
#include <QPainter>

#include "card.h"
#include "cardwidget.h"

using namespace client;


//const QSize CardWidget::sm_qsizeSmall(48, 78 );
const QSize CardWidget::sm_qsizeSmall(50, 80);
const QSize CardWidget::sm_qsizeNormal(70, 113);
const QSize CardWidget::sm_qsizeBig(200, 320);

CardWidget::CardWidget(QWidget* parent):
        QLabel(parent),
        m_cardId(0),
        m_shadowMode(0),
        m_qsize(sm_qsizeSmall)
{
}

CardWidget::~ CardWidget()
{
}

void CardWidget::paintEvent(QPaintEvent *event)
{
    if (!m_shadowMode) {
        QLabel::paintEvent(event);
    } else {
        QPainter painter(this);
        painter.fillRect(this->rect(), QBrush(QColor(0,0,0,128)));
    }
}

void CardWidget::setCardClass(const QString& cardClassId)
{
    m_cardClassId = cardClassId;
}

void CardWidget::setCardId(int cardId)
{
    m_cardId = cardId;
}


QSize CardWidget::qSize(Size size)
{
    switch(size) {
        case SIZE_SMALL:  return sm_qsizeSmall;  break;
        case SIZE_NORMAL: return sm_qsizeNormal; break;
        case SIZE_BIG:    return sm_qsizeBig;    break;
    }
    Q_ASSERT(0);
    return QSize(); // avoid warning
}


void CardWidget::setSize(Size size)
{
    m_size = size;
    m_qsize = qSize(size);
}

void CardWidget::applyNewProperties()
{
    /* TODO: spot for optimalization */
    CardPointer card = Card::findCard(m_cardClassId);
    if (card == 0)
    {
        qWarning(qPrintable(QString("Cannot find card id %1.").arg(m_cardClassId)));
        return;
    }
    setPixmap(card->image().scaled(m_qsize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setMinimumSize(m_qsize);
    setMaximumSize(m_qsize);
    resize(m_qsize);
}



