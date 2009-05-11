/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
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
#ifndef PARSERSTRUCTS_H
#define PARSERSTRUCTS_H

#include <QString>
#include <QList>
#include <QImage>

class XmlNode;
class QXmlStreamWriter;

struct StructServerInfo
{
    QString name, description;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
    static QString elementName;
};


enum ActionRequestType {
    REQUEST_DRAW,
    REQUEST_PLAY,
    REQUEST_RESPOND,
    REQUEST_DISCARD
};

enum PlayerRole {
    ROLE_INVALID,
    ROLE_UNKNOWN,
    ROLE_SHERIFF,
    ROLE_DEPUTY,
    ROLE_OUTLAW,
    ROLE_RENEGADE
};

enum PocketType {
    POCKET_INVALID,
    POCKET_DECK,
    POCKET_GRAVEYARD,
    POCKET_HAND,
    POCKET_TABLE,
    POCKET_PLAYED,
    POCKET_SELECTION
};

enum PlayingCardType {
    CARD_UNKNOWN,

    // TEMPORARY CARDS
    CARD_BANG,          // playWithPlayer, respond
    CARD_MISSED,        // respond (playWithPlayer for character)
    CARD_BEER,          // play, respond(last lifepoint)
    CARD_SALOON,        // play
    CARD_WELLSFARGO,    // play
    CARD_DILIGENZA,     // play
    CARD_GENERALSTORE,  // play
    CARD_PANIC,         // playWithPlayer (hand), playWithCard
    CARD_CATBALOU,      // playWithPlayer (hand), playWithCard
    CARD_INDIANS,       // play
    CARD_DUEL,          // play
    CARD_GATLING,       // play

    // PERMANENT CARDS
    CARD_MUSTANG,       // play
    CARD_APPALOSSA,     // play
    CARD_BARREL,        // play, use
    CARD_DYNAMITE,      // play, use
    CARD_JAIL,          // play, use

    // WEAPONS
    CARD_VOLCANIC,      // play
    CARD_SCHOFIELD,     // play
    CARD_REMINGTON,     // play
    CARD_CARABINE,      // play
    CARD_WINCHESTER     // play
};

enum CardSuit {
    SUIT_SPADES,
    SUIT_HEARTS,
    SUIT_DIAMONDS,
    SUIT_CLUBS
};



/**
 * Represents the rank of a card. Numeral ranks are represented with the
 * corresponding number, others are represented by following values:
 *  * jack  = 11,
 *  * queen = 12,
 *  * king  = 13,
 *  * ace   = 14
 * This represention allows convenient comparing.
 */
typedef int CardRank;

enum CharacterType {
    CHARACTER_UNKNOWN = 0,
    CHARACTER_BART_CASSIDY,
    CHARACTER_BLACK_JACK,
    CHARACTER_CALAMITY_JANET,
    CHARACTER_EL_GRINGO,
    CHARACTER_JESSE_JONES,
    CHARACTER_JOURDONNAIS,
    CHARACTER_KIT_CARLSON,
    CHARACTER_LUCKY_DUKE,
    CHARACTER_PAUL_REGRET,
    CHARACTER_PEDRO_RAMIREZ,
    CHARACTER_ROSE_DOOLAN,
    CHARACTER_SID_KETCHUM,
    CHARACTER_SLAB_THE_KILLER,
    CHARACTER_SUZY_LAFAYETTE,
    CHARACTER_VULTURE_SAM,
    CHARACTER_WILLY_THE_KID
};

enum ReactionType {
    REACTION_BANG,
    REACTION_GATLING,
    REACTION_INDIANS,
    REACTION_DUEL,
    REACTION_CHOOSECARD,
    REACTION_LASTSAVE
};

enum ClientType {
    CLIENT_PLAYER,
    CLIENT_SPECTATOR
};


struct ActionPlayCardData {
    int playedCardId;
    enum {
        PLAYCARD_SIMPLE,    // card is played solo
        PLAYCARD_PLAYER,    // card is played with target player
        PLAYCARD_CARD,      // card is played with target (revealed) card
        PLAYCARD_HAND       // card is played with target (unrevealed) card in opponent hands
    } type;
    union {
        int targetPlayerId;
        int targetCardId;
        int targetHandId;
    };
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

struct ActionUseAbilityData {
    enum {
        TypeSimple,
        TypePlayer,
        TypeCards
    } type;
    int targetPlayerId;
    QList<int> targetCardsId;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

struct CardData {
    int             id;
    PlayingCardType type;
    CardSuit        suit;
    CardRank        rank;

    CardData(): id(0), type(CARD_UNKNOWN) {}

    void read(XmlNode*);
    void write(QXmlStreamWriter*, QString elementName = QString()) const;
};

struct PublicPlayerData {
    int     id;
    QString name;

    bool    hasPassword;
    bool    hasController;
    bool    isAI;
    bool    isAlive;

    QImage avatar;
    CharacterType character;
    int lifePoints;
    bool isSheriff;
    int handSize;
    QList<CardData> table;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

struct PrivatePlayerData {
    int             id;
    PlayerRole      role;
    QList<CardData> hand;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

enum GamePlayState {
    GAMEPLAYSTATE_INVALID = 0,
    GAMEPLAYSTATE_DRAW,
    GAMEPLAYSTATE_TURN,
    GAMEPLAYSTATE_RESPONSE,
    GAMEPLAYSTATE_DISCARD
};

enum GameState {
    GAMESTATE_INVALID = 0,
    GAMESTATE_WAITINGFORPLAYERS,
    GAMESTATE_PLAYING,
    GAMESTATE_FINISHED
};

struct PlayerInfoData
{
    int     id;
    QString name;
    bool    hasPassword;
    bool    hasController;
    bool    isAI;
    bool    isAlive;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

struct CreatePlayerData
{
    QString name, password;
    QImage avatar;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

struct CreateGameData
{
    QString name, description;
    int minPlayers, maxPlayers, maxSpectators, AIPlayers;
    QString playerPassword, spectatorPassword;
    bool flagShufflePlayers;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

struct GameInfoData
{
    int id;
    QString name, description;
    int minPlayers, maxPlayers, maxSpectators;
    int alivePlayersCnt, totalPlayersCnt, spectatorsCnt, AIPlayersCnt;
    bool hasPlayerPassword, hasSpectatorPassword;
    GameState state;
    QList<PlayerInfoData> players;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

struct GameInfoListData: public QList<GameInfoData>
{
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

struct GameContextData {
    int             currentPlayerId;
    int             requestedPlayerId;
    int             turnNumber;
    GamePlayState   gamePlayState;

    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};



struct GameSyncData {
    int                     id;
    QString                 name;
    bool                    isCreator;
    QList<PublicPlayerData> players;
    PrivatePlayerData       localPlayer;
    GameContextData         gameContext;
    GameState               state;
    CardData                graveyard;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};


enum CardMovementType {
    CardMovementDrawCard,
    CardMovementDiscardCard,
    CardMovementPlayCard,
    CardMovementStealCard,
    CardMovementCancelCard
};

struct CardMovementData {
    PocketType        pocketTypeFrom;
    PocketType        pocketTypeTo;
    int               playerFrom;
    int               playerTo;
    CardData          card;
    CardData          secondCard;
    CardMovementType  type;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

struct StructClient
{
    int id;
    QString name;
};

struct StructPlayer
{
    int id;
    QString name, password;
    PlayerRole role;
    void read(XmlNode*);
    void write(QXmlStreamWriter*, bool writePassword = 0) const;
    static QString elementName;
    StructPlayer();
};


struct StructGame
{
    int id, creatorId;
    QString name, description;
    int minPlayers, maxPlayers, maxSpectators;
    QString playerPassword, spectatorPassword;
    bool hasPlayerPassword, hasSpectatorPassword;
    bool flagShufflePlayers;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
    static QString elementName;
};


PlayerRole StringToPlayerRole(const QString& s);
QString PlayerRoleToString(const PlayerRole& r);


QString GamePlayStateToString(const GamePlayState& s);
QString PlayingCardTypeToString(const PlayingCardType& c);
QString CharacterTypeToString(const CharacterType& t);

QString ClientTypeToString(const ClientType& t);
ClientType StringToClientType(const QString& s);

GameState StringToGameState(const QString& s);
QString GameStateToString(const GameState& s);

#endif
