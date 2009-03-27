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
#ifndef CARDMOVEMENT_H
#define CARDMOVEMENT_H

#include <QObject>
#include <QPoint>
#include <QList>
#include <QQueue>
#include <QRect>
#include <QPointer>
#include <QWidget>
#include <QBasicTimer>




namespace client
{
class CardWidget;
class CardPocket;
class CardMovementParentWidget;

/**
 * This class handles the animation of cards in the game. Whenever there is a need
 * to move a card to a pocket, an instance of this class must be created. The instance
 * itself controls its lifetime, so you only need to create it with <b>new</b> operator
 * and leave it.
 *
 * \todo It may be desired to reveal yet unrevealed card sometimes. This class should
 *       handle this.
 *
 * @author MacJariel <MacJariel@gmail.com>
 */
class CardMovement : public QObject
{
Q_OBJECT
public:
    /**
     * Creates an instance of CardMovement class which starts the animation.
     * @param mainWidget The main widget of the window.
     * @param cardWidget The card widget that will be moved.
     * @param destination The target pocket.
     */
    CardMovement(CardMovementParentWidget *mainWidget, CardWidget* cardWidget, CardPocket* destination, QString cardClass);
    virtual ~CardMovement();

    /**
      * Returns the rectangle of the current position of the card in the animation.
      * This method is to be called from the paintEvent of the mainWidget
      */
    QRect cardRect();

private:
    void timerEvent(QTimerEvent* event);

private:
    void start();
    void stop();
    void enqueue();
    static void startNext();

private:
    CardPocket* mp_dest;
    CardMovementParentWidget*    mp_mainWidget;
    QPoint      m_origin;
    QPoint      m_current;
    QPoint      m_destination;
    QString     m_cardType;
    qreal       m_length;
    int         m_tick;
    CardWidget* mp_card;
    bool        m_movementInitialized;
    
    static QBasicTimer  sm_timer;

    static QQueue<CardMovement*> sm_queue;
};
}
#endif
