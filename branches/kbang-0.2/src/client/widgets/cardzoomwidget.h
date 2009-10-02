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

#ifndef CARDZOOMWIDGET_H
#define CARDZOOMWIDGET_H

#include <QTime>
#include "cardwidget.h"

namespace client {

class Game;

/**
 * The CardZoomWidget provides a zoomed view to a CardWidget.
 * @author MacJariel
 */
class CardZoomWidget: public CardWidget
{
Q_OBJECT;
public:
    /**
     * Constructs a zoomed version of <i>cardWidget</i>.
     * @param game The current game.
     */
    CardZoomWidget(Game* game, CardWidget* cardWidget);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual void mouseMoveEvent(QMouseEvent *ev);

private slots:
    void terminate();

private:
    void onRelease();

    Game*       mp_game;
    QTime       m_time;
    static int  sm_minZoomTime;
};
}
#endif // CARDZOOMWIDGET_H
