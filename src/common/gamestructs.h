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

/**
 * The GameStruct struct is pure abstract base for all common game structs.
 */
struct GameStruct {
    enum Type {
        InvalidType = 0,
        ServerInfoType,
        PlayerInfoType,
        GameInfoType,
        GameInfoListType,
        CardSetInfoType,
        CardSetInfoListType,
        CreatePlayerType,
        CreateGameType,
        CardDataType,
        PublicPlayerType,
        PrivatePlayerType,
        GameContextType,
        GameSyncType
    };
    GameStruct(Type type): m_type(type) {}
    inline Type t() const { return m_type; }
private:
    Type m_type;
};

/**
 * The ServerInfoData struct holds the information about the server.
 * It is used when querying for server information.
 */
struct ServerInfoData: public GameStruct {
    ServerInfoData(): GameStruct(ServerInfoType), gamesCnt(0),
                      playersCnt(0), clientsCnt(0) {}

    QString name;       /**< Name of the server. */
    QString desc;       /**< Short description of the server. */
    QString adminName;  /**< Server administrator's name. */
    QString adminEmail; /**< Server administrator's email. */
    quint16 gamesCnt;   /**< Count of games on server. */
    quint16 playersCnt; /**< Count of players on server. */
    quint16 clientsCnt; /**< Count of clients on server. */
    QDateTime startTime;/**< Time of the start of the server in ISO 8601 UTC. */
    QString motd;       /**< Message of the day. */
};

/**
 * The PlayerInfoData structure describes basic information about a player.
 * It is used to list players in join game dialog.
 */
struct PlayerInfoData: public GameStruct {
    PlayerInfoData(): GameStruct(PlayerInfoType), id(0), hasPassword(0),
                      hasController(0), isAI(0), isAlive(0) {}

    PlayerId    id;             /**< Player id. */
    QString     name;           /**< Player name. */
    bool        hasPassword;    /**< Whether player has password. */
    bool        hasController;  /**< Whether player has an attached controller. */
    bool        isAI;           /**< Whether is controlled by AI. */
    bool        isAlive;        /**< Whether is alive. */
};
typedef QList<PlayerInfoData> PlayerInfoDataList;


/**
 * The GameInfoData structure describes basic information about a game.
 * It is used to list games in join game dialog.
 */
struct GameInfoData: public GameStruct {
    GameInfoData(): GameStruct(GameInfoType), id(0), playersMin(0),
                    playersMax(0), playersCnt(0), alivePlayersCnt(0),
                    aiPlayersCnt(0), spectatorsMax(0), spectatorsCnt(0),
                    hasPlayerPassword(0), hasSpectatorPassword(0),
                    gameState(GAMESTATE_INVALID) {}

    GameId      id;                  /**< Game id. */
    QString     name;                /**< Game name. */
    QString     desc;                /**< Game description. */
    quint8      playersMin;          /**< Minimal count of players. */
    quint8      playersMax;          /**< Maximal count of players. */
    quint8      playersCnt;          /**< Count of all players. */
    quint8      alivePlayersCnt;     /**< Count of alive players. */
    quint8      aiPlayersCnt;        /**< Count of AI players. */
    qint16      spectatorsMax;       /**< Maximal number of spectators. */
    quint16     spectatorsCnt;       /**< Count of spectators. */
    bool        hasPlayerPassword;   /**< Whether has player password. */
    bool        hasSpectatorPassword;/**< Whether has spectator password. */
    GameState   gameState;           /**< State of the game. */
    PlayerInfoDataList players;      /**< List of players. */
};

struct GameInfoListData: public GameStruct, public QList<GameInfoData> {
    GameInfoListData(): GameStruct(GameInfoListType) {}
};

/**
 * The CardSetInfoData structure describes cardset information that is
 * advertised by server to clients.
 */
struct CardSetInfoData: public GameStruct {
    CardSetInfoData(): GameStruct(CardSetInfoType), formatVersion(0),
    revision(0) {}

    QString         id;                 /**< Unique id of cardset. */
    QString         name;               /**< English name of cardset. */
    QList<QLocale>  locales;            /**< Locales of the cardset. */
    QString         slotId;             /**< Id of the slot. */
    quint16         formatVersion;      /**< Version of used cardset format. */
    quint16         revision;           /**< Revision of the cardset. */
    QStringList     downloadLinks;      /**< List of download links. */
};

struct CardSetInfoListData: public GameStruct, public QList<CardSetInfoData> {
    CardSetInfoListData(): GameStruct(CardSetInfoListType) {}
};

/**
 * The NewPlayerData structure holds information needed to create a player.
 * This is used when creating and/or joining games.
 */
struct CreatePlayerData: public GameStruct {
    CreatePlayerData(): GameStruct(CreatePlayerType) {}

    QString     name;     /**< Player's name. */
    QString     password; /**< Player's password. Empty string disables password. */
    QByteArray  avatar;   /**< Player's avatar. */
};

/**
 * This structure holds all information that is necessary to create a game.
 * This is used when creating a game.
 * \todo add items to determine game type and parameters
 */
struct CreateGameData: public GameStruct {
    CreateGameData(): GameStruct(CreateGameType), playersMin(0), playersMax(0),
                      spectatorsMax(0), aiPlayersCnt(0) {}

    QString name;               /**< Game name. */
    QString desc;               /**< Game description. */
    quint8  playersMin;         /**< Minimal count of players. */
    quint8  playersMax;         /**< Maximal count of players. */
    qint16  spectatorsMax;      /**< Maximal number of spectators. */
    quint8  aiPlayersCnt;       /**< Count of AI players. */
    QString playerPassword;     /**< Player password, empty string = no pass. */
    QString spectatorPassword;  /**< Spectator password, empty string = no pass. */
    QMap<QString, QVariant> options;
};

/**
 * This structure holds information about a card.
 */
struct CardData: public GameStruct {
    CardData(): GameStruct(CardDataType), id(0), type(CARDTYPE_UNKNOWN),
                suit(SUIT_INVALID), rank(0), isReady(1) {}

    CardId      id;         /**< Card id.   @see CardId. */
    CardName    name;       /**< Card name. @see CardName. */
    CardType    type;       /**< Card type. @see CardType. */
    CardSuit    suit;       /**< Card suit. @see CardSuit. */
    CardRank    rank;       /**< Card rank. @see CardRank. */
    bool        isReady;    /**< Whether card is ready - this is related to green-bordered cards */
};
typedef QList<CardData> CardDataList;

/**
 * This structure holds all public information about a player.
 */
struct PublicPlayerData: public GameStruct {
    PublicPlayerData(): GameStruct(PublicPlayerType), id(0), hasPassword(0),
                        hasController(0), isAI(0), isAlive(0), isWinner(0),
                        isSheriff(0), lifePoints(0), handSize(0),
                        role(ROLE_INVALID) {}

    PlayerId        id;             /**< Player id. */
    QString         name;           /**< Player name. */
    bool            hasPassword;    /**< Whether player has password. */
    bool            hasController;  /**< Whether player has an attached controller. */
    bool            isAI;           /**< Whether is controlled by AI. */
    bool            isAlive;        /**< Whether is alive. */
    bool            isWinner;       /**< Whether is a winner. */
    bool            isSheriff;      /**< Whether is sheriff. */
    QByteArray      avatar;         /**< Player's avatar. */
    QString         character;      /**< Player's character. */
    QString         takenCharacter; /**< Used for Vera Custer. */
    qint8           lifePoints;     /**< Player's life points. */
    quint8          handSize;       /**< Number of cards in player's hand. */
    QList<CardData> table;          /**< List of cards on table. */
    PlayerRole      role;           /**< Player's role (if is known) */
};
typedef QList<PublicPlayerData> PublicPlayerDataList;

/**
 * This structure holds player id and all private information about a player.
 */
struct PrivatePlayerData: public GameStruct {
    PrivatePlayerData(): GameStruct(PrivatePlayerType), id(0),
                         role(ROLE_INVALID) {}

    PlayerId        id;             /**< Player id. */
    PlayerRole      role;           /**< Player's role. */
    QList<CardData> hand;           /**< List of cards in player's hand. */
};

/**
 * This structure holds information about game context.
 */
struct GameContextData: public GameStruct {
    GameContextData(): GameStruct(GameContextType), currentPlayerId(0),
                       requestedPlayerId(0), turnNumber(0),
                       gamePlayState(GAMEPLAYSTATE_INVALID),
                       reactionType(REACTION_NONE),
                       causedBy(0) {}

    PlayerId        currentPlayerId;    /**< Id of current player (Player on turn). */
    PlayerId        requestedPlayerId;  /**< Id of requested player. */
    quint32         turnNumber;         /**< Turn number. */
    GamePlayState   gamePlayState;      /**< GamePlay state. */
    ReactionType    reactionType;       /**< Reaction type. */
    PlayerId        causedBy;           /**< Id of player that caused reaction. */
};

/**
 * This structure is used to synchronize client with server. It contains all
 * information about a game that a client needs to reconstuct it from scratch.
 * Note, that this structure is created on demand for concrete player (client).
 */
struct GameSyncData: public GameStruct {
    GameSyncData(): GameStruct(GameSyncType), id(0), isCreator(0) {}

    GameId               id;         /**< Game id. */
    QString              name;       /**< Game name. */
    bool                 isCreator;  /**< Whether the client is creator. */
    PublicPlayerDataList players;    /**< List of PublicPlayerData. */
    PrivatePlayerData    localPlayer;/**< Local player information (if not spectator). */
    GameContextData      gameContext;/**< The GameContext */
    GameState            gameState;  /**< The GameState */
    CardData             graveyard;  /**< The top card in graveyard. */
    CardDataList         selection;  /**< The content of selection pocket. */
};

#if 0

/**
 * This structure holds information about PlayCard game action.
 */
struct ActionPlayCardData {
    ActionPlayCardData(): playedCardId(0), targetCardId(0),
                          discardCardId(0), targetPlayerId(0) {}
    CardId      playedCardId;   /**< The id of card to be played. */
    CardId      targetCardId;   /**< The id of target card. */
    CardId      discardCardId;  /**< The id of card to be discarded. */
    PlayerId    targetPlayerId; /**< The id of target player. */

    /**
     * Reads the given XML tree and writes data into this object.
     */
    bool read(XmlNode*);

    /**
     * Writes data from this object into XML stream using given writer.
     */
    void write(QXmlStreamWriter*) const;

    static QString elementName; /**< Name of corresponding XML element. */
};


/**
 * This structure holds information about UseAbility game action.
 */
struct ActionUseAbilityData {
    ActionUseAbilityData(): targetPlayerId(0) {}
    PlayerId        targetPlayerId; /**< The id of target player. */
    QList<CardId>   targetCardsId;  /**< The list of target cards. */

    /**
     * Reads the given XML tree and writes data into this object.
     */
    bool read(XmlNode*);

    /**
     * Writes data from this object into XML stream using given writer.
     */
    void write(QXmlStreamWriter*) const;

    static QString elementName; /**< Name of corresponding XML element. */
};

#endif

#endif // GAMESTRUCTS_H
