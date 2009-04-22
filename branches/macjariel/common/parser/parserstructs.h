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
    CHARACTER_UNKNOWN
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


struct CardData {
    int             id;
    PlayingCardType type;
    CardSuit        suit;
    CardRank        rank;

    CardData(): id(0), type(CARD_UNKNOWN) {}

    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

struct PublicPlayerData {
    int id;
    QString name;
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

struct GameContextData {
    int             currentPlayerId;
    int             requestedPlayerId;
    int             turnNumber;
    GamePlayState   gamePlayState;

    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};

struct GameSyncData {
    QList<PublicPlayerData> players;
    PrivatePlayerData       localPlayer;
    GameContextData         gameContext;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
};


struct CardMovementData {
    PocketType        pocketTypeFrom;
    PocketType        pocketTypeTo;
    int               playerFrom;
    int               playerTo;
    CardData          card;
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

typedef QList<StructPlayer> StructPlayerList;

struct StructGame
{
    int id, creatorId;
    QString name, description;
    int minPlayers, maxPlayers, maxSpectators;
    QString playerPassword, spectatorPassword;
    bool hasPlayerPassword, hasSpectatorPassword;
    bool flagShufflePlayers;
    void read(XmlNode*, StructPlayerList* playerList = 0);
    void write(QXmlStreamWriter*, const StructPlayerList* playerlist = 0) const;
    static QString elementName;
};

typedef QList<StructGame> StructGameList;

PlayerRole StringToPlayerRole(const QString& s);
QString PlayerRoleToString(const PlayerRole& r);



#endif
