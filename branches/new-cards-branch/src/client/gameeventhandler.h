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
#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <QObject>

namespace client
{
class Game;

/**
 * The GameEventHandler class receives game events from parser, encapsluates
 * them into GameEvent instances and enqueues them in GameEventQueue.
 */
class GameEventHandler: public QObject
{
Q_OBJECT;
public:
    /**
     * Constructs a GameEventHandler that handles events for <i>game</i>.
     */
    GameEventHandler(Game* game);

    /**
     * Connects parser signals to coresponding slots.
     */
    void connectSlots(QObject* signalEmitter);

public slots:
    void onCardMovementEvent(const CardMovementData&);
    void onGameContextChangeEvent(const GameContextData&);
    void onGameSyncEvent(const GameSyncData&);
    void onLifePointsChangeEvent(int playerId, int lifePoints);
    void onPlayerDiedEvent(int playerId, PlayerRole role);

    void onPlayerJoinedEvent(const PublicPlayerData&);
    void onPlayerLeavedEvent(int playerId);
    void onPlayerUpdateEvent(const PublicPlayerData&);

    void onGameMessageEvent(const GameMessage&);

private:
    Game*           mp_game;
};

}
#endif // GAMEEVENTHANDLER_H
