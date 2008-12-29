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
#include <QtDebug>

#include "card.h"
#include "cardwidget.h"

CardWidget::CardWidget(QWidget* parent): QLabel(parent)
{
    setScaledContents(1);

}

CardWidget::~ CardWidget()
{
}

QPoint CardWidget::absPos() const
{
    const QWidget* w = this;
    QPoint res;
    while (w != 0)
    {
        //qDebug() << res << w->objectName() << w->metaObject()->className();
        //res += w->mapToParent(QPoint());
        qDebug() << w->objectName() << w->metaObject()->className() << w->geometry().topLeft();
        w = w->parentWidget();
    }
    qDebug() << res << "DONE";
    return res;
}
void CardWidget::setCardClass(const QString& cardClassId)
{
    m_cardClassId = cardClassId;
}

void CardWidget::setServerCardId(const QString& serverCardId)
{
    m_serverCardId = serverCardId;
}

void CardWidget::setCardSize(Size size)
{
    m_size = size;
}

QSize CardWidget::smallSize()
{
    //return QSize(40, 64);
    return QSize(60, 97);
}

QSize CardWidget::normalSize()
{
    return QSize(60, 97);
}

QSize CardWidget::bigSize()
{
    return QSize(100, 162);
}
void CardWidget::applyNewProperties()
{
    /* TODO: improve performance */
    CardPointer card = Card::findCard(m_cardClassId);
    if (card == 0)
    {
        qWarning(qPrintable(QString("Cannot find card id %1.").arg(m_cardClassId)));
        return;
    }
    if (m_size == SIZE_NORMAL)
    {
        setPixmap(card->image());
        setMinimumSize(normalSize());
        setMaximumSize(normalSize());
        resize(normalSize());
    }
    else
    {
        setPixmap(card->imageSmall());
        setMinimumSize(smallSize());
        setMaximumSize(smallSize());
        resize(smallSize());
    }
}

