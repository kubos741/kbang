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

#ifndef GAMEMESSAGEEVENT_H
#define GAMEMESSAGEEVENT_H

#include "gameevent.h"
#include "gamestructs.h"

namespace client
{
/**
 * The GameMessageEvent class represents the game-message game event.
 * @author MacJariel
 */
class GameMessageEvent: public GameEvent
{
Q_OBJECT;
public:
    /**
     * Constructs a GameMessageEvent related to <i>game</i>, according to
     * given GameMessage.
     */
    GameMessageEvent(Game* game, const GameMessage&);

    /**
     * Destroys the GameMessageEvent.
     */
    virtual ~GameMessageEvent();

    /**
     * Runs the event. Changes the state of the game and sends
     * a new log message to LogWidget, if suitable.
     * @note This method is currently responsible for formating of log messages.
     *       We should consider moving this functionality into LogWidget.
     */
    virtual void run();

private:
    QString cardToString(const CardData&, bool withRankAndSuit = 0);
    QString cardListWidgetToString(QList<CardData>);
    QString decoratePlayerName(const QString& playerName, bool isTarget = 0);

    GameMessage m_gameMessage;
};
}

#endif // GAMEMESSAGEEVENT_H
