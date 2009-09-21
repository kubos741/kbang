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
#ifndef GAMETYPES_H
#define GAMETYPES_H

/**
 * @file gametypes.h
 * The definition of enums and typedefs common for both server and client.
 */

#include <QString>

/** \typedef ClientId
 * Type used to identify clients on server. Every client on server has unique
 * identifier. The value 0 is reserved for invalid client (or AI).
 */
typedef quint32 ClientId;

/** \typedef GameId
 * Type used to identify games on server. Every game on server has unique
 * identifier. The value 0 is reserved for invalid game.
 */
typedef quint32 GameId;

/** \typedef PlayerId
 * Type used to identify players. Players are uniquely identified by
 * combination of GameIdType and PlayerIdType. The value 0 is reserved for
 * invalid player.
 */
typedef quint32 PlayerId;

/** \typedef CardId
 * Type used to identify cards. All (playing) cards in one game have unique
 * identifiers. The value 0 is reserved for invalid/unknown card.
 */
typedef quint32 CardId;

/**
 * This enum holds player roles. The roles are represented in enum, because I
 * believe that the roles will be always fixed in all possible expansions.
 * @see QString playerRoleToString(PlayerRole)
 * @see PlayerRole stringToPlayerRole(QString)
 */
enum PlayerRole {
    ROLE_INVALID = 0,   /**< Invalid role.*/
    ROLE_UNKNOWN,       /**< Unknown role. */
    ROLE_SHERIFF,       /**< Sheriff. */
    ROLE_DEPUTY,        /**< Deputy. */
    ROLE_OUTLAW,        /**< Outlaw. */
    ROLE_RENEGADE       /**< Renegade. */
};

/**
 * Converts QString to PlayerRole. ROLE_INVALID is returned in case
 * of invalid string.
 */
PlayerRole stringToPlayerRole(const QString& s);

/**
 * Converts PlayerRole to QString.
 */
QString playerRoleToString(const PlayerRole& r);

enum ClientType {
    CLIENTTYPE_PLAYER,
    CLIENTTYPE_SPECTATOR
};

/**
 * Converts QString to ClientType.
 */
ClientType stringToClientType(const QString& s);

/**
 * Converts ClientType to QString.
 */
QString clientTypeToString(ClientType);

/**
 * This enum describes all the possible pocket types.
 * @see Pocket
 * @see QString pocketTypeToString(PocketType)
 * @see PocketType stringToPocketType(QString)
 */
enum PocketType {
    POCKET_INVALID = 0, /**< Invalid pocket type - usually signifies an error. */
    POCKET_DECK,        /**< Deck of playing cards in the middle of the table. */
    POCKET_GRAVEYARD,   /**< Graveyard (or discard pile). */
    POCKET_HAND,        /**< Player's hand. */
    POCKET_TABLE,       /**< Player's table (the cards in front of the player).*/
    POCKET_SELECTION    /**< The space for listing cards (for General Store, etc.). */
};

/**
 * Converts QString to PocketType.
 */
PocketType stringToPocketType(const QString& s);

/**
 * Converts PocketType to QString.
 */
QString pocketTypeToString(const PocketType& p);

/**
 * \typedef CardName
 * Type used to identify card names. For example: bang, missed,
 * susy-laffayete, sheriff, etc. The name can be also an empty string. In this
 * case the unknown card of given CardType is refered and the back of the card
 * should be displayed in client.
 * @see CardData for details
 */
typedef QString CardName;

/**
 * This enum describes the types of cards. The type of card can be determined by
 * its back side. All cards with the same back side are of the same CardType.
 *
 */
enum CardType {
    CARDTYPE_UNKNOWN = 0,
    CARDTYPE_PLAYING,       /**< Playing cards (Bang!, Missed, etc.) */
    CARDTYPE_CHARACTER,     /**< Character cards (El Gringo, etc.)   */
    CARDTYPE_ROLE           /**< Role cards (Shefiff, Deputy, etc.)  */
};

/**
 * Converts QString to CardType. The CARDTYPE_PLAYING value is considered
 * default and is returned in case of invalid string.
 */
CardType stringToCardType(const QString& s);

/**
 * Converts CardType to string.
 */
QString cardTypeToString(const CardType& t);


/**
 * ReactionType is currently used only to write a message to player when he or
 * she is requested a reaction. This enum is not generic enough and the method
 * to tell clients about reactions should probably change.
 * \deprecated
 */
enum ReactionType {
    REACTION_NONE,
    REACTION_BANG,
    REACTION_GATLING,
    REACTION_INDIANS,
    REACTION_DUEL,
    REACTION_GENERALSTORE,
    REACTION_LASTSAVE,
    REACTION_LUCKYDUKE,
    REACTION_KITCARLSON
};

ReactionType    stringToReactionType(const QString& s);
QString         reactionTypeToString(const ReactionType& r);


/**
 * This enum lists all the game participant types.
 * \todo A 'nice to have' feature is to implement concrete spectators, that
 *       would be able to spectate concrete player (if they know the password).
 * \todo Also it would be nice to have something like SUPERVISOR, which would
 *       be a spectator able to see everything.
 * @see QString gameParticipantTypeToString(GameParticipantType)
 * @see GameParticipantType stringToGameParticipantType(QString)
 */
enum GameParticipantType {
    GAMEPARTICIPANT_PLAYER,      /**< A player. */
    GAMEPARTICIPANT_SPECTATOR    /**< A spectator. */
};

/**
 * Converts QString to GameParticipantType.
 */
GameParticipantType stringToGameParticipantType(const QString& s);

/**
 * Converts GameParticipantType to QString.
 */
QString gameParticipantTypeToString(const GameParticipantType& t);

/**
 * This enum defines the suits of standard poker cards. The symbolic constants
 * are self-explanatory.
 * @see QString cardSuitToString(CardSuit)
 * @see CardSuit stringToCardSuit(QString)
 */
enum CardSuit {
    SUIT_INVALID = 0,
    SUIT_SPADES,
    SUIT_HEARTS,
    SUIT_DIAMONDS,
    SUIT_CLUBS
};

/**
 * Converts QString to CardSuit. In case of invalid string, unspecified
 * value of CardSuit is returned.
 */
CardSuit stringToCardSuit(const QString& s);

/**
 * Converts CardSuit to QString.
 */
QString cardSuitToString(const CardSuit& suit);

/**
 * Represents the rank of a card. Numeral ranks are represented with the
 * corresponding number, others are represented by following values:
 *  * jack  = 11,
 *  * queen = 12,
 *  * king  = 13,
 *  * ace   = 14
 * This represention allows simple comparing of card ranks.
 */
typedef quint8 CardRank;

/**
 * Converts QString to CardRank. In case of invalid string, unspecified
 * value of CardRank is returned. String should be either decimal number (2-10)
 * or one of J, Q, K and A. The case of letters does not matter.
 */
CardRank stringToCardRank(QString s);

/**
 * Converts CardRank to QString. The result is upper-case.
 */
QString cardRankToString(const CardRank& rank);

/**
 * This enum defines the states of a game.
 * @see QString gameStateToString(GameState)
 * @see GameState stringToGameState(QString)
 * @see GamePlayState
 */
enum GameState {
    GAMESTATE_INVALID = 0,          /**< Reserved for errors. */
    GAMESTATE_WAITINGFORPLAYERS,    /**< The game is waiting for players. */
    GAMESTATE_PLAYING,              /**< The game has been started and not finished yet. */
    GAMESTATE_FINISHED              /**< The game has already finished. */
};

/**
 * Converts QString to GameState.
 */
GameState stringToGameState(const QString& s);

/**
 * Converts GameState to QString.
 */
QString gameStateToString(const GameState& s);

/**
 * This enum defines the possible "GamePlayStates" of a game in playing state.
 * Every game in GAMESTATE_PLAYING state has a GamePlayState too.
 * @see QString gamePlayStateToString(GamePlayState)
 * @see GamePlayState stringToGamePlayState(QString)
 * @see GameState
 */
enum GamePlayState {
    GAMEPLAYSTATE_INVALID = 0,      /**< Reserved for errors. */
    GAMEPLAYSTATE_DRAW,             /**< Draw state. */
    GAMEPLAYSTATE_TURN,             /**< Main turn state. */
    GAMEPLAYSTATE_RESPONSE,         /**< Response state. */
    GAMEPLAYSTATE_DISCARD           /**< Discard state. */
};

/**
 * Converts QString to GamePlayState.
 */
GamePlayState stringToGamePlayState(const QString& s);

/**
 * Converts GamePlayState to QString.
 */
QString gamePlayStateToString(const GamePlayState& s);

/**
 * This enum of game-message types should be maybe changed.
 * \todo
 */
enum GameMessageType {
    GAMEMESSAGE_INVALID = 0,
    GAMEMESSAGE_GAMESTARTED,
    GAMEMESSAGE_GAMEFINISHED,
    GAMEMESSAGE_PLAYERDRAWFROMDECK,
    GAMEMESSAGE_PLAYERDRAWFROMGRAVEYARD,
    GAMEMESSAGE_PLAYERDISCARDCARD,
    GAMEMESSAGE_PLAYERPLAYCARD,
    GAMEMESSAGE_PLAYERRESPONDWITHCARD,
    GAMEMESSAGE_PLAYERPASS,
    GAMEMESSAGE_PLAYERPICKFROMSELECTION,
    GAMEMESSAGE_PLAYERCHECKDECK,
    GAMEMESSAGE_PLAYERSTEALCARD,
    GAMEMESSAGE_PLAYERCANCELCARD,
    GAMEMESSAGE_DECKREGENERATE,
    GAMEMESSAGE_PLAYERDIED,
};

/**
 * Converts QString to GameMessageType.
 */
GameMessageType stringToGameMessageType(const QString&);

/**
 * Converts GameMessageType to QString.
 */
QString gameMessageTypeToString(const GameMessageType&);

enum ClientPriviledge {
    CLIENTPRIVILEDGE_INVALID = 0,
    CLIENTPRIVILEDGE_BASIC,
    CLIENTPRIVILEDGE_CREATOR
};

#endif // GAMETYPES_H
