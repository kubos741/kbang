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

using namespace client;

const int tickTime = 5;
const double pixelsPerTick = 16;
const int delay = 500;
QQueue<CardMovement*> CardMovement::sm_queue;


CardMovement::CardMovement(QWidget *mainWidget, CardWidget* card, CardPocket* destination)
: QObject(mainWidget), mp_dest(destination), mp_mainWidget(mainWidget),
  mp_timer(0), m_tick(0), mp_card(card), m_waitingForVisible(1)
{
    qDebug() << "Creating animation, queue size: " << sm_queue.size();
    enqueue();
    if (sm_queue.size() == 1)
    {
        start();
    }
}

CardMovement::~CardMovement()
{
}

void CardMovement::start()
{
    if (mp_timer == 0)
    {
        mp_timer = new QTimer(this);
        mp_timer->setInterval(tickTime);
        connect(mp_timer, SIGNAL(timeout()),
                this, SLOT(onTimerShot()));
        mp_timer->start();
    }
    if (!mp_dest->isVisible() || !mp_card->isVisible()) return;
    if (mp_card->parent() != parent())
    {
        QPoint pos = mp_card->mapTo(mp_mainWidget, QPoint(0,0));
        mp_card->setParent(mp_mainWidget);
        mp_card->move(pos);
    }
    mp_card->raise();
    mp_card->show();
    m_origin = mp_card->pos();
    m_destination = mp_dest->mapTo(mp_mainWidget, mp_dest->newCardPosition());
    m_length = sqrt(pow(m_destination.x() - m_origin.x(), 2) +
                    pow(m_destination.y() - m_origin.y(), 2));
    m_waitingForVisible = 0;
}

void CardMovement::onTimerShot()
{
    if (m_waitingForVisible)
    {
        start();
        return;
    }
    m_tick++;
    qreal progress = (m_tick* pixelsPerTick) / m_length;
    if (progress > 1)
    {
        stop();
        return;
    }
    QPoint pos = m_origin + (m_destination - m_origin) * progress;
    mp_card->move(pos);
}

void CardMovement::stop()
{
    mp_timer->stop();
    mp_timer->deleteLater();
    mp_dest->push(mp_card);
    if (sm_queue.size() != 0 && sm_queue.head() == this) sm_queue.dequeue();
    deleteLater();
    startNext();
}

void client::CardMovement::enqueue()
{
    sm_queue.enqueue(this);
}

void client::CardMovement::startNext()
{
    qDebug() << "Starting next...";
    if (sm_queue.size() == 0) return;
    sm_queue.head()->start();
}
