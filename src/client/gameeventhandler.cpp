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

#include "gameeventhandler.h"
#include "gameeventqueue.h"
#include "game.h"

#include "cardmovementevent.h"
#include "gamecontextchangeevent.h"
#include "gamesyncevent.h"
#include "lifepointschangeevent.h"
#include "playerdiedevent.h"
#include "playerevent.h"
#include "gamemessageevent.h"

using namespace client;

GameEventHandler::GameEventHandler(Game* game):
        QObject(game),
        mp_game(game)
{
}

void GameEventHandler::connectSlots(QObject* signalEmitter)
{
    connect(signalEmitter,      SIGNAL(sigEventCardMovement(const CardMovementData&)),
            this,               SLOT(onCardMovementEvent(const CardMovementData&)));
    connect(signalEmitter,      SIGNAL(sigEventGameContextChange(const GameContextData&)),
            this,               SLOT(onGameContextChangeEvent(const GameContextData&)));
    connect(signalEmitter,      SIGNAL(sigEventGameSync(const GameSyncData&)),
            this,               SLOT(onGameSyncEvent(const GameSyncData&)));
    connect(signalEmitter,      SIGNAL(sigEventLifePointsChange(int, int)),
            this,               SLOT(onLifePointsChangeEvent(int, int)));
    connect(signalEmitter,      SIGNAL(sigEventPlayerDied(int, PlayerRole)),
            this,               SLOT(onPlayerDiedEvent(int, PlayerRole)));
    connect(signalEmitter,      SIGNAL(sigEventPlayerJoinedGame(const PublicPlayerData&)),
            this,               SLOT(onPlayerJoinedEvent(const PublicPlayerData&)));
    connect(signalEmitter,      SIGNAL(sigEventPlayerLeavedGame(int)),
            this,               SLOT(onPlayerLeavedEvent(int)));
    connect(signalEmitter,      SIGNAL(sigEventPlayerUpdate(const PublicPlayerData&)),
            this,               SLOT(onPlayerUpdateEvent(const PublicPlayerData&)));
    connect(signalEmitter,      SIGNAL(sigEventGameMessage(const GameMessage&)),
            this,               SLOT(onGameMessageEvent(const GameMessage&)));
}


void GameEventHandler::onCardMovementEvent(const CardMovementData& cardMovementData)
{
    mp_game->eventQueue()->add(new CardMovementEvent(mp_game, cardMovementData));
}

void GameEventHandler::onGameContextChangeEvent(const GameContextData& gameContextData)
{
    mp_game->eventQueue()->add(new GameContextChangeEvent(mp_game, gameContextData));
}

void GameEventHandler::onGameSyncEvent(const GameSyncData& gameSyncData)
{
    mp_game->eventQueue()->add(new GameSyncEvent(mp_game, gameSyncData));
}

void GameEventHandler::onLifePointsChangeEvent(int playerId, int lifePoints)
{
    mp_game->eventQueue()->add(new LifePointsChangeEvent(mp_game, playerId, lifePoints));
}

void GameEventHandler::onPlayerDiedEvent(int playerId, PlayerRole role)
{
    mp_game->eventQueue()->add(new PlayerDiedEvent(mp_game, playerId, role));
}

void GameEventHandler::onPlayerJoinedEvent(const PublicPlayerData& player)
{
    mp_game->eventQueue()->add((new PlayerEvent(mp_game))->playerJoined(player));
}

void GameEventHandler::onPlayerLeavedEvent(int playerId)
{
    mp_game->eventQueue()->add((new PlayerEvent(mp_game))->playerLeaved(playerId));
}
void GameEventHandler::onPlayerUpdateEvent(const PublicPlayerData& player)
{
    mp_game->eventQueue()->add((new PlayerEvent(mp_game))->playerUpdate(player));
}

void GameEventHandler::onGameMessageEvent(const GameMessage& gameMessage)
{
    mp_game->eventQueue()->add(new GameMessageEvent(mp_game, gameMessage));
}
