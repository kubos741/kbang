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

#include <QtCore>
#include <QtDebug>

#include "cardwidget.h"
#include "cardpocket.h"
#include "cardmovementparentwidget.h"
#include <math.h>

using namespace client;



const int tickTime = 20;
const double pixelsPerTick = 24;
//const int delay = 500;
QBasicTimer CardMovement:: sm_timer;
QQueue<CardMovement*> CardMovement::sm_queue;


CardMovement::CardMovement(CardMovementParentWidget *mainWidget, CardWidget* card, CardPocket* destination, QString cardType)
: QObject(mainWidget), mp_dest(destination), mp_mainWidget(mainWidget), m_cardType(cardType),
  m_tick(0), mp_card(card), m_movementInitialized(0)
{
    enqueue();
    if (sm_queue.size() == 1) {
        start();
    }
}

CardMovement::~CardMovement()
{
}

void CardMovement::start()
{
    Q_ASSERT(sm_timer.isActive() == 0);
    sm_timer.start(tickTime, this);
}

void CardMovement::timerEvent(QTimerEvent* event)
{
    if (!m_movementInitialized) {
        if (!mp_dest->isVisible() || !mp_card->isVisible()) return;
        if (mp_card->parent() != parent())
        {
            QPoint pos = mp_card->mapTo(mp_mainWidget, QPoint(0,0));
            mp_card->setParent(mp_mainWidget);
            mp_card->move(pos);
        }
        mp_card->raise();
        mp_card->show();
        m_current = m_origin = mp_card->pos();
        m_destination = mp_dest->mapTo(mp_mainWidget, mp_dest->newCardPosition());
        m_length = sqrt(pow(m_destination.x() - m_origin.x(), 2) + pow(m_destination.y() - m_origin.y(), 2));
        m_movementInitialized = 1;
        mp_card->setShadowMode();
    }

    m_tick++;
    qreal progress = (m_tick* pixelsPerTick) / m_length;
    if (progress > 1)
    {
        stop();
        return;
    }
    m_current = m_origin + (m_destination - m_origin) * progress;
    mp_card->move(m_current);
}

void CardMovement::stop()
{
    sm_timer.stop();
    if (!m_cardType.isEmpty()) {
        mp_card->setCardClass(m_cardType);
        mp_card->applyNewProperties();
        //mp_card->setServerCardId
    }
    mp_card->unsetShadowMode();

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
    if (sm_queue.size() == 0) return;
    sm_queue.head()->start();
}

QRect client::CardMovement::cardRect()
{
    return QRect(m_current, mp_card->qsize());
}
