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

#ifndef SERVEREVENTS_H
#define SERVEREVENTS_H

#include "gametypes.h"
#include "gamestructs.h"
#include <QList>
#include <QSharedPointer>

/**
 * The ServerEventData class is base class for all server events.
 * @author MacJariel
 */
class ServerEventData
{
    Q_DISABLE_COPY(ServerEventData);
public:
    enum Type {
        EnterGameType,
        ExitGameType,
        CreatePlayerType,
        RemovePlayerType,
        ChatMessageType,
        GameUpdateType
    };

    ServerEventData() {}

    virtual Type type() const = 0;

    static QString typeToString(Type);
    static Type stringToType(const QString&);
};

typedef QSharedPointer<ServerEventData> ServerEventDataPtr;

struct EnterGameEventData: public ServerEventData
{
    virtual Type type() const { return EnterGameType; }
    GameSyncData gameSyncData;
};

typedef QSharedPointer<EnterGameEventData> EnterGameEventDataPtr;

struct ExitGameEventData: public ServerEventData
{
    virtual Type type() const { return ExitGameType; }
    GameId gameId;
};
typedef QSharedPointer<ExitGameEventData> ExitGameEventDataPtr;

struct CreatePlayerEventData: public ServerEventData
{
    virtual Type type() const { return CreatePlayerType; }
    GameId gameId;
    PublicPlayerData publicPlayerData;
};
typedef QSharedPointer<CreatePlayerEventData> CreatePlayerEventDataPtr;

struct RemovePlayerEventData: public ServerEventData
{
    virtual Type type() const { return CreatePlayerType; }
    GameId   gameId;
    PlayerId playerId;
};
typedef QSharedPointer<RemovePlayerEventData> RemovePlayerEventDataPtr;

struct ChatMessageEventData: public ServerEventData
{
    virtual Type type() const { return ChatMessageType; }
    GameId   gameId;
    ClientId clientId;
    PlayerId playerId;
    QString  senderName;
    QString  text;
};
typedef QSharedPointer<ChatMessageEventData> ChatMessageEventDataPtr;

struct GameUpdateEventData: public ServerEventData
{
    GameUpdateEventData(): m_flags(0) {}
    enum {
        IsStartableAttr = 1
    };
    virtual Type type() const { return GameUpdateType; }
    GameId gameId;
    bool isStartable;


    bool hasFlag(int flag) const { return (m_flags & flag) != 0; }
    void setFlag(int flag) { m_flags |= flag; }
private:
    int m_flags;
};
typedef QSharedPointer<GameUpdateEventData> GameUpdateEventDataPtr;

#endif // SERVEREVENTS_H
