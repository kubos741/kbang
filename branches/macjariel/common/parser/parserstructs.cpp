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

#include "parserstructs.h"
#include "../util.h"
#include "xmlnode.h"
#include <QXmlStreamWriter>
#include <QtDebug>

CardSuit StringToCardSuit(const QString& s)
{
    if (s == "spades")      return SUIT_SPADES;
    if (s == "hearts")      return SUIT_HEARTS;
    if (s == "diamonds")    return SUIT_DIAMONDS;
    if (s == "clubs")       return SUIT_CLUBS;
    qWarning(qPrintable(QString("Invalid suit: %1").arg(s)));
    return SUIT_SPADES;
}

QString CardSuitToString(const CardSuit& suit)
{
    switch(suit) {
        case SUIT_SPADES:   return "spades";
        case SUIT_HEARTS:   return "hearts";
        case SUIT_DIAMONDS: return "diamonds";
        case SUIT_CLUBS:    return "clubs";
    }
    return "";
}

CharacterType StringToCharacterType(const QString& s)
{
    if (s == "slab the killer") return CHARACTER_SLAB_THE_KILLER;
    if (s == "lucky duke")      return CHARACTER_LUCKY_DUKE;
    if (s == "suzy lafayette")  return CHARACTER_SUZY_LAFAYETTE;
    if (s == "vulture sam")     return CHARACTER_VULTURE_SAM;
    if (s == "black jack")      return CHARACTER_BLACK_JACK;
    if (s == "sid ketchum")     return CHARACTER_SID_KETCHUM;
    if (s == "jourdonnais")     return CHARACTER_JOURDONNAIS;
    if (s == "el gringo")       return CHARACTER_EL_GRINGO;
    if (s == "kit carlson")     return CHARACTER_KIT_CARLSON;
    if (s == "jesse jones")     return CHARACTER_JESSE_JONES;
    if (s == "pedro ramirez")   return CHARACTER_PEDRO_RAMIREZ;
    if (s == "calamity janet")  return CHARACTER_CALAMITY_JANET;
    if (s == "rose doolan")     return CHARACTER_ROSE_DOOLAN;
    if (s == "bart cassidy")    return CHARACTER_BART_CASSIDY;
    if (s == "paul regret")     return CHARACTER_PAUL_REGRET;
    if (s == "willy the kid")   return CHARACTER_WILLY_THE_KID;
    return CHARACTER_UNKNOWN;
}

QString CharacterTypeToString(const CharacterType& t)
{
    switch(t) {
    case CHARACTER_UNKNOWN:         return "unknown";
    case CHARACTER_SLAB_THE_KILLER: return "slab the killer";
    case CHARACTER_LUCKY_DUKE:      return "lucky duke";
    case CHARACTER_SUZY_LAFAYETTE:  return "suzy lafayette";
    case CHARACTER_VULTURE_SAM:     return "vulture sam";
    case CHARACTER_BLACK_JACK:      return "black jack";
    case CHARACTER_SID_KETCHUM:     return "sid ketchum";
    case CHARACTER_JOURDONNAIS:     return "jourdonnais";
    case CHARACTER_EL_GRINGO:       return "el gringo";
    case CHARACTER_KIT_CARLSON:     return "kit carlson";
    case CHARACTER_JESSE_JONES:     return "jesse jones";
    case CHARACTER_PEDRO_RAMIREZ:   return "pedro ramirez";
    case CHARACTER_CALAMITY_JANET:  return "calamity janet";
    case CHARACTER_ROSE_DOOLAN:     return "rose doolan";
    case CHARACTER_BART_CASSIDY:    return "bart cassidy";
    case CHARACTER_PAUL_REGRET:     return "paul regret";
    case CHARACTER_WILLY_THE_KID:   return "willy the kid";
    }
    return "unknown";
}

PlayingCardType StringToPlayingCardType(const QString& s)
{
    if (s == "bang")             return CARD_BANG;
    if (s == "missed")           return CARD_MISSED;
    if (s == "beer")             return CARD_BEER;
    if (s == "saloon")           return CARD_SALOON;
    if (s == "wellsfargo")       return CARD_WELLSFARGO;
    if (s == "diligenza")        return CARD_DILIGENZA;
    if (s == "generalstore")     return CARD_GENERALSTORE;
    if (s == "panic")            return CARD_PANIC;
    if (s == "catbalou")         return CARD_CATBALOU;
    if (s == "indians")          return CARD_INDIANS;
    if (s == "duel")             return CARD_DUEL;
    if (s == "gatling")          return CARD_GATLING;
    if (s == "mustang")          return CARD_MUSTANG;
    if (s == "appalossa")        return CARD_APPALOSSA;
    if (s == "barrel")           return CARD_BARREL;
    if (s == "dynamite")         return CARD_DYNAMITE;
    if (s == "jail")             return CARD_JAIL;
    if (s == "volcanic")         return CARD_VOLCANIC;
    if (s == "schofield")        return CARD_SCHOFIELD;
    if (s == "remington")        return CARD_REMINGTON;
    if (s == "carabine")         return CARD_CARABINE;
    if (s == "winchester")       return CARD_WINCHESTER;
    return CARD_UNKNOWN;
}

QString PlayingCardTypeToString(const PlayingCardType& c)
{
    switch(c) {
        case CARD_BANG:           return "bang";
        case CARD_MISSED:         return "missed";
        case CARD_BEER:           return "beer";
        case CARD_SALOON:         return "saloon";
        case CARD_WELLSFARGO:     return "wellsfargo";
        case CARD_DILIGENZA:      return "diligenza";
        case CARD_GENERALSTORE:   return "generalstore";
        case CARD_PANIC:          return "panic";
        case CARD_CATBALOU:       return "catbalou";
        case CARD_INDIANS:        return "indians";
        case CARD_DUEL:           return "duel";
        case CARD_GATLING:        return "gatling";
        case CARD_MUSTANG:        return "mustang";
        case CARD_APPALOSSA:      return "appalossa";
        case CARD_BARREL:         return "barrel";
        case CARD_DYNAMITE:       return "dynamite";
        case CARD_JAIL:           return "jail";
        case CARD_VOLCANIC:       return "volcanic";
        case CARD_SCHOFIELD:      return "schofield";
        case CARD_REMINGTON:      return "remington";
        case CARD_CARABINE:       return "carabine";
        case CARD_WINCHESTER:     return "winchester";
        case CARD_UNKNOWN:        return "";
    }
    return "";
}

PlayerRole StringToPlayerRole(const QString& s)
{
    if (s == "unknown")  return ROLE_UNKNOWN;
    if (s == "outlaw")   return ROLE_OUTLAW;
    if (s == "deputy")   return ROLE_DEPUTY;
    if (s == "sheriff")  return ROLE_SHERIFF;
    if (s == "renegade") return ROLE_RENEGADE;
    return ROLE_INVALID;
}

QString PlayerRoleToString(const PlayerRole& r)
{
    if (r == ROLE_UNKNOWN)  return "unknown";
    if (r == ROLE_OUTLAW)   return "outlaw";
    if (r == ROLE_DEPUTY)   return "deputy";
    if (r == ROLE_SHERIFF)  return "sheriff";
    if (r == ROLE_RENEGADE) return "renegade";
    if (r == ROLE_INVALID)  return "invalid";
    NOT_REACHED();
    return "invalid";
}


GamePlayState StringToGamePlayState(const QString& s)
{
    if (s == "draw")     return GAMEPLAYSTATE_DRAW;
    if (s == "turn")     return GAMEPLAYSTATE_TURN;
    if (s == "response") return GAMEPLAYSTATE_RESPONSE;
    if (s == "discard")  return GAMEPLAYSTATE_DISCARD;
    return GAMEPLAYSTATE_INVALID;
}

QString GamePlayStateToString(const GamePlayState& s)
{
    if (s == GAMEPLAYSTATE_DRAW)     return "draw";
    if (s == GAMEPLAYSTATE_TURN)     return "turn";
    if (s == GAMEPLAYSTATE_RESPONSE) return "response";
    if (s == GAMEPLAYSTATE_DISCARD)  return "discard";
    if (s == GAMEPLAYSTATE_INVALID)  return "invalid";
    NOT_REACHED();
    return "invalid";
}

//----------------------------------------------------------------------------


void ActionPlayCardData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "play-card");
    playedCardId = node->attribute("id").toInt();
    if (!node->attribute("target-player-id").isNull()) {
        type = PLAYCARD_PLAYER;
        targetPlayerId = node->attribute("target-player-id").toInt();
    } else if (!node->attribute("target-card-id").isNull()) {
        type = PLAYCARD_CARD;
        targetCardId = node->attribute("target-card-id").toInt();
    } else if (!node->attribute("target-hand-id").isNull()) {
        type = PLAYCARD_HAND;
        targetHandId = node->attribute("target-hand-id").toInt();
    } else {
        type = PLAYCARD_SIMPLE;
    }
}

void ActionPlayCardData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("play-card");
    writer->writeAttribute("id", QString::number(playedCardId));
    switch(type) {
    case PLAYCARD_SIMPLE:
        break;
    case PLAYCARD_PLAYER:
        writer->writeAttribute("target-player-id", QString::number(targetPlayerId));
        break;
    case PLAYCARD_CARD:
        writer->writeAttribute("target-card-id", QString::number(targetCardId));
        break;
    case PLAYCARD_HAND:
        writer->writeAttribute("target-hand-id", QString::number(targetHandId));
        break;
    }
    writer->writeEndElement();
}

void ActionUseAbilityData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "use-ability");
    if (!node->attribute("target-player-id").isNull()) {
        type = TypePlayer;
        targetPlayerId = node->attribute("target-player-id").toInt();
    } else if (node->getChildren().size() == 0) {
        type = TypeSimple;
    } else {
        type = TypeCards;
        foreach (XmlNode* cardNode, node->getChildren()) {
            targetCardsId.append(cardNode->attribute("id").toInt());
        }
    }
}

void ActionUseAbilityData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("use-ability");
    switch(type) {
    case TypeSimple:
        break;
    case TypePlayer:
        writer->writeAttribute("target-player-id", QString::number(targetPlayerId));
        break;
    case TypeCards:
        foreach(int cardId, targetCardsId) {
            writer->writeStartElement("card");
            writer->writeAttribute("id", QString::number(cardId));
            writer->writeEndElement();
        }
        break;
    }
    writer->writeEndElement();
}



void CardData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "card");
    id          = node->attribute("id").toInt();
    type        = StringToPlayingCardType(node->attribute("type"));
    suit        = StringToCardSuit(node->attribute("suit"));
    rank        = node->attribute("rank").toInt();
}

void CardData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("card");
    writer->writeAttribute("id",        QString::number(id));
    writer->writeAttribute("type",      PlayingCardTypeToString(type));
    writer->writeAttribute("suit",      CardSuitToString(suit));
    writer->writeAttribute("rank",      QString::number(rank));
    writer->writeEndElement();
}

void PublicPlayerData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "public-player");
    Q_ASSERT(node->getFirstChild()->name() == "cards-table");
    id          = node->attribute("id").toInt();
    name        = node->attribute("name");
    character   = StringToCharacterType(node->attribute("character"));
    lifePoints  = node->attribute("lifePoints").toInt();
    isSheriff   = (node->attribute("isSheriff") == "true");
    handSize    = node->attribute("handSize").toInt();
    XmlNode* cards = node->getFirstChild();
    table.clear();
    foreach(XmlNode* card, cards->getChildren()) {
        CardData cardData;
        cardData.read(card);
        table.append(cardData);
    }
}

void PublicPlayerData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("public-player");
    writer->writeAttribute("id",                QString::number(id));
    writer->writeAttribute("name",              name);
    writer->writeAttribute("character",         CharacterTypeToString(character));
    writer->writeAttribute("lifePoints",        QString::number(lifePoints));
    writer->writeAttribute("isSheriff",         isSheriff ? "true" : "false");
    writer->writeAttribute("handSize",          QString::number(handSize));
    writer->writeStartElement("cards-table");
    foreach(const CardData& cardData, table)
        cardData.write(writer);
    writer->writeEndElement();
    writer->writeEndElement();
}

void PrivatePlayerData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "private-player");
    Q_ASSERT(node->getFirstChild()->name() == "cards-hand");
    id      = node->attribute("id").toInt();
    role    = StringToPlayerRole(node->attribute("role"));
    XmlNode* cards = node->getFirstChild();
    hand.clear();
    foreach(XmlNode* card, cards->getChildren()) {
        CardData cardData;
        cardData.read(card);
        hand.append(cardData);
    }
}



void PrivatePlayerData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("private-player");
    writer->writeAttribute("id",                QString::number(id));
    writer->writeAttribute("role",              PlayerRoleToString(role));
    writer->writeStartElement("cards-hand");
    foreach(const CardData& cardData, hand)
        cardData.write(writer);
    writer->writeEndElement();
    writer->writeEndElement();
}




void GameContextData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "game-context");
    currentPlayerId     = node->attribute("currentPlayerId").toInt();
    requestedPlayerId   = node->attribute("requestedPlayerId").toInt();
    turnNumber          = node->attribute("turnNumber").toInt();
    gamePlayState       = StringToGamePlayState(node->attribute("gamePlayState"));
}

void GameContextData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("game-context");
    writer->writeAttribute("currentPlayerId",   QString::number(currentPlayerId));
    writer->writeAttribute("requestedPlayerId", QString::number(requestedPlayerId));
    writer->writeAttribute("turnNumber",        QString::number(turnNumber));
    writer->writeAttribute("gamePlayState",     GamePlayStateToString(gamePlayState));
    writer->writeEndElement();
}

void GameSyncData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "game-sync");
    Q_ASSERT(node->getChildren()[0]->name() == "players");
    players.clear();
    foreach(XmlNode* player, node->getFirstChild()->getChildren()) {
        PublicPlayerData publicPlayerData;
        publicPlayerData.read(player);
        players.append(publicPlayerData);
    }
    localPlayer.read(node->getChildren()[1]);
    gameContext.read(node->getChildren()[2]);
}

void GameSyncData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("game-sync");

    writer->writeStartElement("players");
    foreach (const PublicPlayerData& p, players)
        p.write(writer);
    writer->writeEndElement();

    localPlayer.write(writer);

    gameContext.write(writer);

    writer->writeEndElement();
}

PocketType stringToPocketType(const QString& s)
{
    if (s == "deck")      return POCKET_DECK;
    if (s == "graveyard") return POCKET_GRAVEYARD;
    if (s == "hand")      return POCKET_HAND;
    if (s == "table")     return POCKET_TABLE;
    if (s == "played")    return POCKET_PLAYED;
    if (s == "selection") return POCKET_SELECTION;
    return POCKET_INVALID;
}

QString pocketTypeToString(const PocketType& p)
{
    if (p == POCKET_DECK)       return "deck";
    if (p == POCKET_GRAVEYARD)  return "graveyard";
    if (p == POCKET_HAND)       return "hand";
    if (p == POCKET_TABLE)      return "table";
    if (p == POCKET_PLAYED)     return "played";
    if (p == POCKET_SELECTION)  return "selection";
    return "";
}

QString StructServerInfo::elementName("serverinfo");

void StructServerInfo::read(XmlNode* node)
{
    name = node->attribute("name");
    description = node->attribute("description");
}

void StructServerInfo::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("name", name);
    writer->writeAttribute("description", description);
    writer->writeEndElement();
}

QString StructGame::elementName("game");

void StructGame::read(XmlNode* node, StructPlayerList* playerList)
{
    id = node->attribute("id").toInt();
    creatorId = node->attribute("creatorId").toInt();
    name = node->attribute("name");
    description = node->attribute("description");
    minPlayers = node->attribute("minPlayers").toInt();
    maxPlayers = node->attribute("maxPlayers").toInt();
    maxSpectators = node->attribute("maxSpectators").toInt();
    playerPassword = node->attribute("playerPassword");
    spectatorPassword = node->attribute("spectatorPassword");
    hasPlayerPassword = (node->attribute("hasPlayerPassword") == "1");
    hasSpectatorPassword = (node->attribute("hasSpectatorPassword") == "1");
    flagShufflePlayers = (node->attribute("flagShufflePlayers") == "1");
    if (playerList)
    {
        XmlNode* players = node->getFirstChild();
        if (players && players->name() == "players")
        {
            foreach(XmlNode* playerNode, players->getChildren())
            {
                StructPlayer player;
                player.read(playerNode);
                playerList->append(player);
            }
        }
    }
}

void StructGame::write(QXmlStreamWriter* writer, const StructPlayerList* playerlist) const
{
    writer->writeStartElement("game");
    if (id != 0) writer->writeAttribute("id", QString::number(id));
    writer->writeAttribute("name", name);
    writer->writeAttribute("minPlayers", QString::number(minPlayers));
    writer->writeAttribute("maxPlayers", QString::number(maxPlayers));
    writer->writeAttribute("maxSpectators", QString::number(maxSpectators));
    writer->writeAttribute("hasPlayerPassword", hasPlayerPassword ? "1" : "0");
    writer->writeAttribute("hasSpectatorPassword", hasPlayerPassword ? "1" : "0");
    writer->writeAttribute("flagShufflePlayers", flagShufflePlayers ? "1" : "0");
    if (playerlist)
    {
        writer->writeStartElement("players");
        foreach(const StructPlayer& i, *playerlist)
        {
            writer->writeStartElement("player");
            writer->writeAttribute("id", QString::number(i.id));
            writer->writeAttribute("name", i.name);
            writer->writeAttribute("role", PlayerRoleToString(i.role));
            writer->writeEndElement();
        }
        writer->writeEndElement();
    }
    writer->writeEndElement();
}

StructPlayer::StructPlayer():
role(ROLE_INVALID)
{
}

void StructPlayer::read(XmlNode* node)
{
    id = node->attribute("id").toInt();
    name = node->attribute("name");
    password = node->attribute("password");
    role = StringToPlayerRole(node->attribute("role"));
}

void StructPlayer::write(QXmlStreamWriter* writer, bool writePassword) const
{
    writer->writeStartElement("player");
    writer->writeAttribute("id", QString::number(id));
    writer->writeAttribute("name", name);
    if (writePassword)
        writer->writeAttribute("password", password);
    if (role != ROLE_INVALID)
        writer->writeAttribute("role", PlayerRoleToString(role));
    writer->writeEndElement();
}


QString cardMovementTypeToString(const CardMovementType& c)
{
    if (c == CardMovementCancelCard)       return "cancel-card";
    if (c == CardMovementDiscardCard)      return "discard-card";
    if (c == CardMovementDrawCard)         return "draw";
    return "";
}


void CardMovementData::read(XmlNode* node)
{
    pocketTypeFrom = stringToPocketType(node->attribute("pocketTypeFrom"));
    pocketTypeTo   = stringToPocketType(node->attribute("pocketTypeTo"));
    playerFrom     = node->attribute("playerFrom").toInt();
    playerTo       = node->attribute("playerTo").toInt();
    if (node->getFirstChild() && node->getFirstChild()->name() == "card") {
        card.read(node->getFirstChild());
    }
}

void CardMovementData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("card-movement");
    writer->writeAttribute("pocketTypeFrom", pocketTypeToString(pocketTypeFrom));
    writer->writeAttribute("pocketTypeTo", pocketTypeToString(pocketTypeTo));

    if (playerFrom != 0)
        writer->writeAttribute("playerFrom", QString::number(playerFrom));

    if (playerTo != 0)
        writer->writeAttribute("playerTo", QString::number(playerTo));

    if (card.id != 0)
        card.write(writer);

    writer->writeEndElement();
}


