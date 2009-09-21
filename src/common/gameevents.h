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

/**
 * @file gameevents.h
 * The definition of structs for game events.
 */

#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

#include "gametypes.h"
#include "gamestructs.h"
#include <QList>
#include <QMap>
#include <QSharedPointer>

struct GameEventCmdData;
typedef QSharedPointer<GameEventCmdData> GameEventCmdDataPtr;

/**
 * The GameEventData struct serves to describe a <i>game event</i>.
 *
 * A <i>game event</i> is a structured information that represents a thing that
 * that has happened in a Bang! game on the server. <i>Game events</i> are used
 * to inform clients about this things and therefore keep them synchronized.
 *
 * KBang protocol also defines <i>server event</i>. Even though <i>server
 * events</i> may also represent certain things related to Bang! games, they
 * never describe a change in gameplay. For example <i>server events</i>
 * describe entering and leaving players into game, but it cannot describe
 * playing a card. In other words, the set if <i>game events</i> is the minimal
 * subset of events, that is needed to record a Bang! game, for example for
 * later replaying or analysis.
 *
 * A <i>game event</i> is composed of two components. It has a semantic
 * information and a list of commands that change the state of the game.
 * The semantic information provides a description of the event and clients
 * use this information to display a log message associated with the <i>game
 * event</i>. On the another hand, the commands tell client what is to be
 * changed.
 *
 * The semantic information contains the type of <i>game event</i> and some
 * other attributes, depending on the type.
 *
 * The commands are stored as a list of GameEventCmdData instances.
 *
 * The GameEventData instances cannot be copied. Use GameEventDataPtr.
 */
struct GameEventData
{
    /**
     * Constructs an empty <i>game event</i>.
     */
    GameEventData(): type(UnknownType), gameId(0), targetPlayerId(0),
    useAbility(0), success(0) {}

    ~GameEventData() {}

    /**
     * This enum describes the different types of <i>game events</i>.
     */
    enum Type {
        UnknownType = 0,        /**< Unknown (invalid) type. */
        StartGameType,
        FinishGameType,
        DealCardsType,
        StartTurnType,
        CheckDeckType,
        DrawCardType,
        PlayCardType,
        PlayCardOnTableType,
        PlayCardOnPlayerType,
        PlayCardOnCardType,
        ReactionPlayCardType,
        ReactionPassType,
        ShuffleDeckType,
        KillPlayerType
    };

    /**
     * Some types of <i>game events</i> contain one or more cards as part of
     * the semantic information. This enum describes possible semantic
     * meanings.
     */
    enum CardMeaning {
        NoCard = 0,
        PlayedCard,
        TargetCard,
        CausedByCard,
        CheckedCard
    };


    /**
     * Type of the <i>game event</i>.
     */
    Type type;

    /**
     * List of commands.
     */
    QList<GameEventCmdDataPtr> cmds;

    /**
     * Id of the game.
     */
    GameId gameId;

    /**
     * Id of the player.
     * This attribute is used only by some types of game events.
     */
    PlayerId playerId;

    /**
     * Id of the target player.
     * This attribute is used only by some types of game events.
     */
    PlayerId targetPlayerId;

    /**
     * Whether the character's ability was used.
     * This attribute is used only by some types of game events.
     */
    bool useAbility;

    /**
     * The result of deck checking in CheckDeckType type.
     */
    bool success;

    /**
     * The map (associative array) of cards that are part of the semantic
     * information of the <i>game event</i>.
     */
    QMap<CardMeaning, CardData> cards;

    /**
     * Converts a type of <i>game event</i> to string.
     */
    static QString typeToString(Type);

    /**
     * Converts a string to type of <i>game event</i>.
     */
    static Type stringToType(const QString&);

    /**
     * Converts a GameEventData::CardMeaning to string.
     */
    static QString cardMeaningToString(CardMeaning);

    /**
     * Converts a string to GameEventData::CardMeaning.
     */
    static CardMeaning stringToCardMeaning(const QString&);

private:
    Q_DISABLE_COPY(GameEventData);
};

/**
 * \typedef GameEventDataPtr
 * A typedef for shared pointer to GameEventData object. GameEventData objects
 * should be passed around only through this typedef.
 *
 * @see QSharedPointer
 */
typedef QSharedPointer<GameEventData> GameEventDataPtr;

/**
 * The GameEventCmdData struct is base struct for game event commands.
 */
struct GameEventCmdData
{
    /**
     * This enum describes the different types of commands.
     */
    enum Type {
        CardMovementType,
        UpdatePlayerType,
        GameContextType,
        SetPlayersType
    };

    /**
     * The default base constructor.
     */
    GameEventCmdData() {}

    /**
     * The default base destructor.
     */
    virtual ~GameEventCmdData() {}

    /**
     * Returns the type of the command. This method is to be replaced
     * in derived classes.
     */
    virtual Type type() = 0;
};

/**
 * The CardMovementCmdData struct describes a <i>card movement<i> command.
 * <i>Card movement</i> commands are used to describe the movement of a card
 * from one pocket to another.
 *
 * The source pocket is described by #pocketTypeFrom and #playerFrom and
 * the target pocket is described by #pocketTypeTo and #playerTo.
 * The #card member describes the moved card. If the moved card is not revealed
 * for the event receiver, a default-constructed CardData is used.
 * The #secondCard member is used for special cases. At the moment, it is only
 * used when a card from the top of the graveyard is moved. #secondCard then
 * describes the card under the moved card.
 */
struct CardMovementCmdData: GameEventCmdData
{
    PocketType  pocketTypeFrom; /**< The source pocket type. */
    PocketType  pocketTypeTo;   /**< The target pocket type. */
    PlayerId    playerFrom;     /**< The source player id. */
    PlayerId    playerTo;       /**< The target player id. */
    CardData    card;           /**< The moved card. */
    CardData    secondCard;     /**< This card is used in special cases. */
    virtual Type type() { return CardMovementType; }
};
typedef QSharedPointer<CardMovementCmdData> CardMovementCmdDataPtr;

/**
 * The UpdatePlayerCmdData struct describes a <i>update-player<i> command.
 * <i>Update plater</i> commands are used to change some attributes of a
 * player. The #playerId member contains the id of the player to be updated
 * and using setFlag() and hasFlag() methods you can set or determine which
 * attributes are meant to be updated.
 */
struct UpdatePlayerCmdData: GameEventCmdData
{
    enum {
        NoAttr              = 0,
        IsAliveAttr         = 1,
        IsWinnerAttr        = 2,
        TakenCharacterAttr  = 4,
        LifePointsAttr      = 8,
        RoleAttr            = 16
    };
    UpdatePlayerCmdData(): m_flags(NoAttr) {}
    virtual ~UpdatePlayerCmdData() {}

    PlayerId    playerId;
    bool        isAlive;        /**< Whether is alive. */
    bool        isWinner;       /**< Whether is a winner. */
    QString     takenCharacter; /**< Used for Vera Custer. */
    qint8       lifePoints;     /**< Player's life points. */
    PlayerRole  role;           /**< Player's role (if is known) */

    bool hasFlag(int flag) const { return (m_flags & flag) != 0; }
    void setFlag(int flag) { m_flags |= flag; }
    virtual Type type() { return UpdatePlayerType; }
private:
    qint8       m_flags;
};
typedef QSharedPointer<UpdatePlayerCmdData> UpdatePlayerCmdDataPtr;

/**
 * The GameContextCmdData struct describes a <i>game-context</i> command that
 * serves for updating the game context.
 */
struct GameContextCmdData: GameEventCmdData
{
    GameContextCmdData() {}
    virtual ~GameContextCmdData() {}

    GameContextData gameContext;
    virtual Type type() { return GameContextType; }
};
typedef QSharedPointer<GameContextCmdData> GameContextCmdDataPtr;

/**
 * The SetPlayersCmdData struct describes a <i>set-players</i> command that
 * is used for initial setting of the order of players and their characters
 * and roles. This role is only set in the first (<i>start-game<i>) game event.
 */
struct SetPlayersCmdData: GameEventCmdData
{
    struct PlayerData {
        PlayerId    id;
        QString     name;
        PlayerRole  role;
        QString     character;
    };

    SetPlayersCmdData() {}
    virtual ~SetPlayersCmdData() {}

    QList<PlayerData> players;
    virtual Type type() { return SetPlayersType; }
};
typedef QSharedPointer<SetPlayersCmdData> SetPlayersCmdDataPtr;

#endif // GAMEEVENTS_H
