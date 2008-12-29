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
#include "cardmovement.h"

#include <QTimer>
#include <QWidget>
#include <QtDebug>

#include "cardwidget.h"
#include "cardpocket.h"
#include <math.h>

const int tickTime = 5;
const double pixelsPerTick = 16;

CardMovement::CardMovement(QWidget *mainWidget, CardWidget* card, CardPocket* destination)
: QObject(mainWidget), mp_dest(destination), m_tick(0), mp_card(card)
{
    if (card->parent() != parent())
    {
        QPoint pos = card->mapTo(mainWidget, QPoint(0,0));
        card->setParent(mainWidget);
        card->move(pos);
    }
    card->raise();
    card->show();

    m_origin = card->pos();
    m_destination = destination->newCardPosition();
    m_length = sqrt(pow(m_destination.x() - m_origin.x(), 2) +
                    pow(m_destination.y() - m_origin.y(), 2));
    mp_timer = new QTimer(this);
    mp_timer->setInterval(tickTime);
    connect(mp_timer, SIGNAL(timeout()),
            this, SLOT(onTimerShot()));
    mp_timer->start();
}

CardMovement::~CardMovement()
{
}

void CardMovement::onTimerShot()
{
    m_tick++;
    qreal progress = (m_tick* pixelsPerTick) / m_length;
    if (progress > 1)
    {
        finished();
        return;
    }
    QPoint pos = m_origin + (m_destination - m_origin) * progress;
    mp_card->move(pos);
}

void CardMovement::finished()
{
    mp_timer->stop();
    mp_timer->deleteLater();
    mp_dest->push(mp_card);
    deleteLater();
}

