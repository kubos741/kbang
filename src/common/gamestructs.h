/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
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
 * The definition of structures common for both server and client.
 */

#include <QString>
#include <QList>
#include <QImage>
#include <QXmlStreamWriter> // We cannot forward declare QXmlStreamWriter,
                            // because Qt redefines the class name to
                            // QCoreXmlStreamWriter on some archs.

#include "gametypes.h"

class XmlNode;

/**
 * Describes the information about the server. This structure
 * is used when querying for server information.
 */
struct ServerInfoData
{
    QString name;   /**< Name of the server. */
    QString desc;   /**< Short description of the server. */

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
 * This structure describes basic information about a Player. This
 * structure is used to list players in "join game" dialog.
 */
struct PlayerInfoData
{
    PlayerId    id;             /**< Player id. */
    QString     name;           /**< Player name. */
    bool        hasPassword;    /**< Whether player has password. */
    bool        hasController;  /**< Whether player has an attached controller. */
    bool        isAI;           /**< Whether is controlled by AI. */
    bool        isAlive;        /**< Whether is alive. */

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

typedef QList<PlayerInfoData> PlayerInfoListData;

/**
 * This structure describes basic information about a Game. This
 * structure is used to list games in "join game" dialog.
 */
struct GameInfoData
{
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
    PlayerInfoListData players;      /**< List of players. */

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

struct GameInfoListData: public QList<GameInfoData>
{
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
 * This structure holds all information that is necessary to create a player.
 * This is used when creating or joining a game.
 */
struct CreatePlayerData
{
    QString name;       /**< Player's name. */
    QString password;   /**< Player's password. Empty or Null QString disables the password. */
    QImage  avatar;     /**< Player's avatar. */

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
 * This structure holds all information that is necessary to create a game.
 * This is used when creating a game.
 * \todo add items to determine game type and parameters
 */
struct CreateGameData
{
    QString     name;           /**< Game name. */
    QString     desc;           /**< Game description. */
    quint8      playersMin;     /**< Minimal count of players. */
    quint8      playersMax;     /**< Maximal count of players. */
    qint16      spectatorsMax;  /**< Maximal number of spectators. */
    quint8      aiPlayersCnt;   /**< Count of AI players. */
    QString     playerPassword; /**< Player password. Use QString() for no password. */
    QString     spectatorPassword; /**< Spectator password. Use QString() for no password. */
    bool        flagShufflePlayers; /**< Whether shuffle players. \todo: move into generally handled parameters */

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
 * This structure holds information about a card.
 */
struct CardData {
    CardId      id;         /**< Card id. Defaults to 0. @see CardId. */
    CardName    name;       /**< Card name. @see CardName. */
    CardType    type;       /**< Card type. @see CardType. */
    CardSuit    suit;       /**< Card suit. @see CardSuit. */
    CardRank    rank;       /**< Card rank. @see CardRank. */
    bool        isReady;    /**< Whether card is ready - this is related to green-bordered cards */
    CardData(): id(0) {}

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
 * This structure holds all public information about a player.
 */
struct PublicPlayerData {
    PlayerId        id;             /**< Player id. */
    QString         name;           /**< Player name. */
    bool            hasPassword;    /**< Whether player has password. */
    bool            hasController;  /**< Whether player has an attached controller. */
    bool            isAI;           /**< Whether is controlled by AI. */
    bool            isAlive;        /**< Whether is alive. */
    bool            isWinner;       /**< Whether is a winner. */
    bool            isSheriff;      /**< Whether is sheriff. */
    QImage          avatar;         /**< Player's avatar. */
    QString         character;      /**< Player's character. */
    QString         takenCharacter; /**< Used for Vera Custer. */
    qint8           lifePoints;     /**< Player's life points. */
    quint8          handSize;       /**< Number of cards in player's hand. */
    QList<CardData> table;          /**< List of cards on table. */
    PlayerRole      role;           /**< Player's role (if is known) */

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
 * This structure holds player id and all private information about a player.
 */
struct PrivatePlayerData {
    PlayerId        id;             /**< Player id. */
    PlayerRole      role;           /**< Player's role. */
    QList<CardData> hand;           /**< List of cards in player's hand. */

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
 * This structure holds information about game context.
 */
struct GameContextData {
    PlayerId        currentPlayerId;    /**< Id of current player (Player on turn). */
    PlayerId        requestedPlayerId;  /**< Id of requested player. */
    quint32         turnNumber;         /**< Turn number. */
    GamePlayState   gamePlayState;      /**< GamePlay state. */
    ReactionType    reactionType;       /**< Reaction type. */
    PlayerId        causedBy;           /**< Id of player that caused reaction. */

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
 * This structure is used to synchronize client with server. It contains all information
 * about a game that a client needs to reconstuct it from scratch. Note, that this structure
 * is created on demand for concrete player (client).
 */
struct GameSyncData {
    GameId                  id;         /**< Game id. */
    QString                 name;       /**< Game name. */
    bool                    isCreator;  /**< Whether the client is creator. */
    QList<PublicPlayerData> players;    /**< List of PublicPlayerData. */
    PrivatePlayerData       localPlayer;/**< Local player information (if not spectator). */
    GameContextData         gameContext;/**< The GameContext */
    GameState               gameState;  /**< The GameState */
    CardData                graveyard;  /**< The top card in graveyard. */
    QList<CardData>         selection;  /**< The content of selection pocket. */

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
 * This structure holds the information about a game message.
 * @todo: I don't like how this structure looks and works - to be refactored.
 * @todo: also the generated xml looks crapy..
 */
struct GameMessage {
    GameMessage(): type(GAMEMESSAGE_INVALID), player(0), targetPlayer(0), causedBy(0) {}
    GameMessageType type;
    PlayerId player;
    PlayerId targetPlayer;
    PlayerId causedBy;
    CardData card;
    CardData targetCard;
    QList<CardData> cards;
    bool checkResult;

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
 * This structure holds information about CardMovement game event.
 */
struct CardMovementData {
    PocketType  pocketTypeFrom; /**< The source pocket type. */
    PocketType  pocketTypeTo;   /**< The target pocket type. */
    PlayerId    playerFrom;     /**< The source player id. */
    PlayerId    playerTo;       /**< The target player id. */
    CardData    card;           /**< The moved card. */
    CardData    secondCard;     /**< This card is used in special cases. */

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

#endif // GAMESTRUCTS_H
