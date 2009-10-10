/***************************************************************************
 *   Copyright (C) 2008-2009 by MacJariel                                  *
 *   MacJariel (at) gmail.com                                              *
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
#ifndef GAMESTRUCTS_H
#define GAMESTRUCTS_H

/*[[[cog
import cog
from gamestructdefs import *
]]]
[[[end]]]*/


/**
 * @file gamestructs.h
 * The definition of structures common for both server and client. All those
 * common structures are derived from GameStruct pure abstract class. The
 * following example shows how to downcast:
 * <code>
 * GameStruct* aStruct = getAGameStructFromSomewhere();
 * if (aStruct->type() == GameStruct::ServerInfoDataType) {
 *     ServerInfoData* serverInfoData = static_cast<ServerInfoData*>(aStruct);
 * }
 * </code>
 */

#include "gametypes.h"

#include <QString>
#include <QStringList>
#include <QLocale>
#include <QList>
#include <QVariant>
#include <QByteArray>
#include <QDateTime>
#include <QSharedPointer>
#include <QMap>

/**
 * The GameStruct struct is pure abstract base for all common game structs.
 */
struct GameStruct {
    enum Type {
        InvalidType = 0,
        /*[[[cog
        cog.outl(",\n".join([s["gameStructType"] for s in GameStructs]))
        ]]]*/
        ServerInfoDataType,
        PlayerInfoDataType,
        PlayerInfoListDataType,
        GameInfoDataType,
        GameInfoListDataType,
        UrlListDataType,
        CardSetInfoDataType,
        CardSetInfoListDataType,
        CreatePlayerDataType,
        CreateGameDataType,
        CardDataType,
        CardListDataType,
        PublicPlayerDataType,
        PublicPlayerListDataType,
        PrivatePlayerDataType,
        GameContextDataType,
        GameSyncDataType,
        CardIdListDataType
        //[[[end]]]
    };
    GameStruct(Type type): m_type(type) {}
    inline Type t() const { return m_type; }
private:
    Type m_type;
};

/*[[[cog
for gameStruct in GameStructs:
    cog.outl(gameStruct.genDef())
]]]*/

/**
 * The ServerInfoData struct holds the information about the  server. It
 * is used when querying for server information.
 * @author: MacJariel
 */
struct ServerInfoData: public GameStruct {
    ServerInfoData(): GameStruct(ServerInfoDataType), gamesCnt(0),
         playersCnt(0), clientsCnt(0) {}
    QString name; ///Name of the server.
    QString desc; ///Short description of the server.
    QString adminName; ///Server administrator's name.
    QString adminEmail; ///Server administrator's email.
    quint16 gamesCnt; ///Count of games on server.
    quint16 playersCnt; ///Count of players on server.
    quint16 clientsCnt; ///Count of clients on server.
    QDateTime startTime; ///Time of the start of the server in ISO 8601 UTC.
    QString motd; ///Message of the day.
};


/**
 * The ServerInfoData structure describes basic information about a
 * player. It is used to list players in join game dialog.
 * @author: MacJariel
 */
struct PlayerInfoData: public GameStruct {
    PlayerInfoData(): GameStruct(PlayerInfoDataType), id(0),
         hasPassword(0), hasController(0), isAI(0), isAlive(0) {}
    PlayerId id; ///Player id.
    QString name; ///Player name.
    bool hasPassword; ///Whether player has password.
    bool hasController; ///Whether player has an attached controller.
    bool isAI; ///Whether is controlled by AI.
    bool isAlive; ///Whether is alive.
};


/**
 * @author: MacJariel
 */
struct PlayerInfoListData: public GameStruct, public QList<PlayerInfoData> {
    PlayerInfoListData(): GameStruct(PlayerInfoListDataType) {}
};


/**
 * The GameInfoData structure describes basic information about a game.
 * It is used to list games in join game dialog.
 * @author: MacJariel
 */
struct GameInfoData: public GameStruct {
    GameInfoData(): GameStruct(GameInfoDataType), id(0),
         playersMin(0), playersMax(0), playersCnt(0),
         alivePlayersCnt(0), aiPlayersCnt(0), spectatorsMax(-1),
         spectatorsCnt(0), hasPlayerPassword(0),
         hasSpectatorPassword(0), gameState(GAMESTATE_INVALID) {}
    GameId id; ///Game id.
    QString name; ///Game name.
    QString desc; ///Game description.
    quint8 playersMin; ///Minimal count of players.
    quint8 playersMax; ///Maximal count of players.
    quint8 playersCnt; ///Count of all players.
    quint8 alivePlayersCnt; ///Count of alive players.
    quint8 aiPlayersCnt; ///Count of AI players.
    qint16 spectatorsMax; ///Maximal number of spectators.
    quint16 spectatorsCnt; ///Count of spectators.
    bool hasPlayerPassword; ///Whether has player password.
    bool hasSpectatorPassword; ///Whether has spectator password.
    GameState gameState; ///State of the game.
    PlayerInfoListData players; ///List of players.
};


/**
 * @author: MacJariel
 */
struct GameInfoListData: public GameStruct, public QList<GameInfoData> {
    GameInfoListData(): GameStruct(GameInfoListDataType) {}
};


/**
 * @author: MacJariel
 */
struct UrlListData: public GameStruct, public QList<QString> {
    UrlListData(): GameStruct(UrlListDataType) {}
};


/**
 * The CardSetInfoData structure describes cardset information that is
 * advertised by server to clients.
 * @author: MacJariel
 */
struct CardSetInfoData: public GameStruct {
    CardSetInfoData(): GameStruct(CardSetInfoDataType), id(0),
         formatVersion(0), revision(0) {}
    QString id; ///Unique id of cardset.
    QString name; ///English name of cardset.
    QList<QLocale> locales; ///Locales of the cardset.
    QString slotId; ///Id of the slot.
    quint16 formatVersion; ///Version of used cardset format.
    quint16 revision; ///Revision of the cardset.
    UrlListData downloadLinks; ///List of download links.
};


/**
 * @author: MacJariel
 */
struct CardSetInfoListData: public GameStruct, public QList<CardSetInfoData> {
    CardSetInfoListData(): GameStruct(CardSetInfoListDataType) {}
};


/**
 * The CreatePlayerData structure holds information needed to create a
 * player. This is used when creating and/or joining games.
 * @author: MacJariel
 */
struct CreatePlayerData: public GameStruct {
    CreatePlayerData(): GameStruct(CreatePlayerDataType) {}
    QString name; ///Player's name.
    QString password; ///Player's password. Empty string disables password.
    QByteArray avatar; ///Player's avatar.
};


/**
 *     This structure holds all information that is necessary to create a
 * game. This is used when creating a game.
 *     @todo add items to determine game type and parameters
 * @author: MacJariel
 */
struct CreateGameData: public GameStruct {
    CreateGameData(): GameStruct(CreateGameDataType), playersMin(0),
         playersMax(0), spectatorsMax(0), aiPlayersCnt(0) {}
    QString name; ///Game name.
    QString desc; ///Game description.
    quint8 playersMin; ///Minimal count of players.
    quint8 playersMax; ///Maximal count of players.
    qint16 spectatorsMax; ///Maximal number of spectators.
    quint8 aiPlayersCnt; ///Count of AI players.
    QString playerPassword; ///Player password, empty string = no pass.
    QString spectatorPassword; ///Spectator password, empty string = no pass.
    QMap<QString, QVariant> options; ///
};


/**
 *     This structure holds information about a card.
 * @author: MacJariel
 */
struct CardData: public GameStruct {
    CardData(): GameStruct(CardDataType), id(0),
         type(CARDTYPE_UNKNOWN), suit(SUIT_INVALID),
         rank(RANK_INVALID), isReady(1) {}
    CardId id; ///Card id. @see CardId.
    CardName name; ///Card name. @see CardName.
    CardType type; ///Card type. @see CardType.
    CardSuit suit; ///Card suit. @see CardSuit.
    CardRank rank; ///Card rank. @see CardRank.
    bool isReady; ///Whether card is ready - this is related to green-bordered cards
};


/**
 * @author: MacJariel
 */
struct CardListData: public GameStruct, public QList<CardData> {
    CardListData(): GameStruct(CardListDataType) {}
};


/**
 * This structure holds all public information about a player.
 * @author: MacJariel
 */
struct PublicPlayerData: public GameStruct {
    PublicPlayerData(): GameStruct(PublicPlayerDataType), id(0),
         hasPassword(0), hasController(0), isAI(0), isAlive(0),
         isWinner(0), isSheriff(0), lifePoints(0), handSize(0),
         role(ROLE_INVALID) {}
    PlayerId id; ///Player id.
    QString name; ///Player name.
    bool hasPassword; ///Whether player has password.
    bool hasController; ///Whether player has an attached controller.
    bool isAI; ///Whether is controlled by AI.
    bool isAlive; ///Whether is alive.
    bool isWinner; ///Whether is a winner.
    bool isSheriff; ///Whether is sheriff.
    QString character; ///Player's character.
    QString takenCharacter; ///Used for Vera Custer.
    qint8 lifePoints; ///Player's life points.
    quint8 handSize; ///Number of cards in player's hand.
    PlayerRole role; ///Player's role (if is known)
    QByteArray avatar; ///Player's avatar.
    CardListData table; ///List of cards on table.
};


/**
 * @author: MacJariel
 */
struct PublicPlayerListData: public GameStruct, public QList<PublicPlayerData> {
    PublicPlayerListData(): GameStruct(PublicPlayerListDataType) {}
};


/**
 * This structure holds player id and all private information about a
 * player.
 * @author: MacJariel
 */
struct PrivatePlayerData: public GameStruct {
    PrivatePlayerData(): GameStruct(PrivatePlayerDataType), id(0),
         role(ROLE_INVALID) {}
    PlayerId id; ///Player id.
    PlayerRole role; ///Player's role.
    CardListData hand; ///List of cards in player's hand.
};


/**
 * This structure holds information about game context.
 * @author: MacJariel
 */
struct GameContextData: public GameStruct {
    GameContextData(): GameStruct(GameContextDataType),
         currentPlayerId(0), requestedPlayerId(0), turnNumber(0),
         gamePlayState(GAMEPLAYSTATE_INVALID),
         reactionType(REACTION_NONE), causedBy(0) {}
    PlayerId currentPlayerId; ///Id of current player (Player on turn).
    PlayerId requestedPlayerId; ///Id of requested player.
    quint32 turnNumber; ///Turn number.
    GamePlayState gamePlayState; ///GamePlay state.
    ReactionType reactionType; ///Reaction type.
    PlayerId causedBy; ///Id of player that caused reaction.
};


/**
 * This structure is used to synchronize client with server. It contains
 * allinformation about a game that a client needs to reconstuct it from
 * scratch.Note, that this structure is created on demand for concrete
 * player (client).
 * @author: MacJariel
 */
struct GameSyncData: public GameStruct {
    GameSyncData(): GameStruct(GameSyncDataType), id(0), isCreator(0),
         gameState(GAMESTATE_INVALID) {}
    GameId id; ///Game id.
    QString name; ///Game name.
    bool isCreator; ///Whether the client is creator.
    GameState gameState; ///The GameState.
    PublicPlayerListData players; ///List of PublicPlayerData.
    PrivatePlayerData localPlayer; ///Local player information (if not spectator).
    GameContextData gameContext; ///The context of the game.
    CardData graveyard; ///The top card in graveyard.
    CardListData selection; ///The content of selection pocket.
};


/**
 * @author: MacJariel
 */
struct CardIdListData: public GameStruct, public QList<CardId> {
    CardIdListData(): GameStruct(CardIdListDataType) {}
};

//[[[end]]]
#endif // GAMESTRUCTS_H
