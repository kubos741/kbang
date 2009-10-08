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
#ifndef CARDMOVEMENTCMD_H
#define CARDMOVEMENTCMD_H

#include <QPoint>
#include <QTime>

#include "gameeventcmd.h"
#include "gamestructs.h"

namespace client
{
class CardPocket;
class CardWidget;

/**
 * The CardMovementCmd class provides the animated translation of cards in
 * the game. As soon as a card-movement event is received and dequeued from
 * GameEvent queue, the translation specified by CardMovementData is executed.
 *
 * @author MacJariel
 */
class CardMovementCmd: public GameEventCmd
{
    Q_OBJECT
public:
    /**
     * Constructs a CardMovementCmd instance related to <i>game</i> according
     * to given CardMovementData.
     */
    CardMovementCmd(GameEvent* game, CardMovementCmdDataPtr);

    /**
     * Destroys the CardMovement instance.
     */
    virtual ~CardMovementCmd();

public slots:
    /**
     * Runs the translation.
     */
    virtual void doEventCmd(GameEvent::ExecutionMode);

    virtual void undoEventCmd(GameEvent::ExecutionMode);

    virtual void finish();
private:
    /**
     * Reads the stored CardMovementData and determines the CardWidget for
     * translation and the destination CardPocket.
     */
    void setCardAndPocket(const CardMovementCmdDataPtr&);

    /**
     * Progress the translation.
     */
    virtual void timerEvent(QTimerEvent*);

    /**
     * Stops the translation.
     */
    void stopTransition();

private slots:
    /**
     * Starts the translation.
     */
    void startTransition();

    /**
     * Unreveals the moved card.
     */
    void unrevealCard();

private:
    CardMovementCmdDataPtr  mp_doCmd;
    CardMovementCmdDataPtr  mp_undoCmd;
    CardWidget*             mp_card;
    CardPocket*             mp_destPocket;
    CardData*               mp_cardData;
    QPoint                  m_srcPos;
    QPoint                  m_destPos;
    qreal                   m_length;
    int                     m_tick;
    int                     m_animationTimer;
    QTime                   m_time;
};
}
#endif // CARDMOVEMENTCMD_H
