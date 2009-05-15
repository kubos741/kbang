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
#include <QBuffer>
#include <QtDebug>

CardSuit StringToCardSuit(const QString& s)
{
    if (s == "spades")      return SUIT_SPADES;
    if (s == "hearts")      return SUIT_HEARTS;
    if (s == "diamonds")    return SUIT_DIAMONDS;
    if (s == "clubs")       return SUIT_CLUBS;
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

ReactionType StringToReactionType(const QString& s)
{
    if (s == "bang")            return REACTION_BANG;
    if (s == "gatling")         return REACTION_GATLING;
    if (s == "indians")         return REACTION_INDIANS;
    if (s == "duel")            return REACTION_DUEL;
    if (s == "general-store")   return REACTION_GENERALSTORE;
    if (s == "last-save")       return REACTION_LASTSAVE;
    if (s == "lucky-duke")      return REACTION_LUCKYDUKE;
    if (s == "kit-carlson")     return REACTION_KITCARLSON;
    return REACTION_NONE;
}

QString ReactionTypeToString(const ReactionType& r)
{
    switch(r) {
    case REACTION_BANG:         return "bang";
    case REACTION_GATLING:      return "gatling";
    case REACTION_INDIANS:      return "indians";
    case REACTION_DUEL:         return "duel";
    case REACTION_GENERALSTORE: return "general-store";
    case REACTION_LASTSAVE:     return "last-save";
    case REACTION_LUCKYDUKE:    return "lucky-duke";
    case REACTION_KITCARLSON:   return "kit-carlson";
    case REACTION_NONE:         return "";
    }
    return "";
}

void readAvatar(XmlNode* node, QImage& avatar)
{
    QByteArray bytes = QByteArray::fromBase64(node->getFirstChild()->text().toAscii());
    if (!avatar.loadFromData(bytes)) {
        qWarning("Cannot load image from network.");
    }

}

void writeAvatar(QXmlStreamWriter* writer, const QImage& avatar)
{
    if (!avatar.isNull()) {
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        avatar.save(&buffer, "PNG");
        writer->writeStartElement("avatar");
        writer->writeCharacters(bytes.toBase64());
        writer->writeEndElement();
     }
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
    id          = node->attribute("id").toInt();
    type        = StringToPlayingCardType(node->attribute("type"));
    suit        = StringToCardSuit(node->attribute("suit"));
    rank        = node->attribute("rank").toInt();
}

void CardData::write(QXmlStreamWriter* writer, QString elementName) const
{
    if (elementName.isNull())
        writer->writeStartElement("card");
    else
        writer->writeStartElement(elementName);
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
    id              = node->attribute("id").toInt();
    name            = node->attribute("name");
    character       = StringToCharacterType(node->attribute("character"));
    lifePoints      = node->attribute("lifePoints").toInt();
    isSheriff       = (node->attribute("isSheriff") == "true");
    handSize        = node->attribute("handSize").toInt();
    hasPassword     = node->attribute("hasPassword") == "true";
    hasController   = node->attribute("hasController") == "true";
    isAI            = node->attribute("isAI") == "true";
    isAlive         = node->attribute("isAlive") == "true";
    role            = StringToPlayerRole(node->attribute("role"));
    foreach(XmlNode* child, node->getChildren()) {
        if (child->name() == "cards-table") {
            table.clear();
            foreach(XmlNode* card, child->getChildren()) {
                CardData cardData;
                cardData.read(card);
                table.append(cardData);
            }
        } else if (child->name() == "avatar") {
            readAvatar(child, avatar);
        }
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
    writer->writeAttribute("hasPassword",       hasPassword ? "true" : "false");
    writer->writeAttribute("hasController",     hasController ? "true" : "false");
    writer->writeAttribute("isAI",              isAI ? "true" : "false");
    writer->writeAttribute("isAlive",           isAlive ? "true" : "false");
    writer->writeAttribute("role",              PlayerRoleToString(role));
    writer->writeStartElement("cards-table");
    foreach(const CardData& cardData, table)
        cardData.write(writer);
    writer->writeEndElement();
    writeAvatar(writer, avatar);
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
    reactionType        = StringToReactionType(node->attribute("reaction-type"));
    causedBy            = node->attribute("caused-by").toInt();
}

void GameContextData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("game-context");
    writer->writeAttribute("currentPlayerId",   QString::number(currentPlayerId));
    writer->writeAttribute("requestedPlayerId", QString::number(requestedPlayerId));
    writer->writeAttribute("turnNumber",        QString::number(turnNumber));
    writer->writeAttribute("gamePlayState",     GamePlayStateToString(gamePlayState));
    writer->writeAttribute("reaction-type",     ReactionTypeToString(reactionType));
    writer->writeAttribute("caused-by",         QString::number(causedBy));
    writer->writeEndElement();
}

void GameSyncData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "game-sync");
    Q_ASSERT(node->getChildren()[0]->name() == "players");
    id = node->attribute("id").toInt();
    name = node->attribute("name");
    isCreator = node->attribute("is-creator") == "true";
    state = StringToGameState(node->attribute("state"));
    players.clear();
    foreach(XmlNode* player, node->getFirstChild()->getChildren()) {
        PublicPlayerData publicPlayerData;
        publicPlayerData.read(player);
        players.append(publicPlayerData);
    }
    localPlayer.read(node->getChildren()[1]);
    gameContext.read(node->getChildren()[2]);
    graveyard.read(node->getChildren()[3]);

    selection.clear();
    foreach(XmlNode* cardNode, node->getChildren()[4]->getChildren()) {
        CardData card;
        card.read(cardNode);
        selection.append(card);
    }

}

void GameSyncData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("game-sync");

    writer->writeAttribute("id", QString::number(id));
    writer->writeAttribute("name", name);
    writer->writeAttribute("is-creator", isCreator ? "true" : "false");
    writer->writeAttribute("state", GameStateToString(state));

    writer->writeStartElement("players");
    foreach (const PublicPlayerData& p, players)
        p.write(writer);
    writer->writeEndElement();

    localPlayer.write(writer);

    gameContext.write(writer);

    graveyard.write(writer, "graveyard");

    writer->writeStartElement("selection");
    foreach (const CardData& c, selection)
        c.write(writer);
    writer->writeEndElement();

    writer->writeEndElement();
}

PocketType stringToPocketType(const QString& s)
{
    if (s == "deck")      return POCKET_DECK;
    if (s == "graveyard") return POCKET_GRAVEYARD;
    if (s == "hand")      return POCKET_HAND;
    if (s == "table")     return POCKET_TABLE;
    if (s == "selection") return POCKET_SELECTION;
    return POCKET_INVALID;
}

QString pocketTypeToString(const PocketType& p)
{
    if (p == POCKET_DECK)       return "deck";
    if (p == POCKET_GRAVEYARD)  return "graveyard";
    if (p == POCKET_HAND)       return "hand";
    if (p == POCKET_TABLE)      return "table";
    if (p == POCKET_SELECTION)  return "selection";
    return "";
}


GameState StringToGameState(const QString& s)
{
    if (s == "WaitingForPlayers")   return GAMESTATE_WAITINGFORPLAYERS;
    if (s == "Playing")             return GAMESTATE_PLAYING;
    if (s == "Finished")            return GAMESTATE_FINISHED;
    return GAMESTATE_INVALID;
}

QString GameStateToString(const GameState& s)
{
    switch(s) {
    case GAMESTATE_WAITINGFORPLAYERS:   return "WaitingForPlayers";
    case GAMESTATE_PLAYING:             return "Playing";
    case GAMESTATE_FINISHED:            return "Finished";
    default:                            break;
    }
    return "Invalid";
}

ClientType StringToClientType(const QString& s) {
    if (s == "player") return CLIENT_PLAYER;
    else return CLIENT_SPECTATOR;
}

QString ClientTypeToString(const ClientType& t) {
    switch(t) {
    case CLIENT_PLAYER:     return "player";
    case CLIENT_SPECTATOR:  return "spectator";
    }
    return "";
}

GameMessageType StringToGameMessageType(const QString& s) {
    if (s == "game-started")                return GAMEMESSAGE_GAMESTARTED;
    if (s == "player-draw-from-deck")       return GAMEMESSAGE_PLAYERDRAWFROMDECK;
    if (s == "player-draw-from-graveyard")  return GAMEMESSAGE_PLAYERDRAWFROMGRAVEYARD;
    if (s == "player-discard-card")         return GAMEMESSAGE_PLAYERDISCARDCARD;
    if (s == "player-play-card")            return GAMEMESSAGE_PLAYERPLAYCARD;
    if (s == "player-respond-with-card")    return GAMEMESSAGE_PLAYERRESPONDWITHCARD;
    if (s == "player-pass")                 return GAMEMESSAGE_PLAYERPASS;
    if (s == "player-pick-from-selection")  return GAMEMESSAGE_PLAYERPICKFROMSELECTION;
    if (s == "player-check-deck")           return GAMEMESSAGE_PLAYERCHECKDECK;
    if (s == "player-steal-card")           return GAMEMESSAGE_PLAYERSTEALCARD;
    if (s == "player-cancel-card")          return GAMEMESSAGE_PLAYERCANCELCARD;
    if (s == "deck-regenerate")             return GAMEMESSAGE_DECKREGENERATE;
    if (s == "player-died")                 return GAMEMESSAGE_PLAYERDIED;
    return GAMEMESSAGE_INVALID;
}

QString GameMessageTypeToString(const GameMessageType& g) {
    switch(g) {
    case GAMEMESSAGE_GAMESTARTED:               return "game-started";
    case GAMEMESSAGE_PLAYERDRAWFROMDECK:        return "player-draw-from-deck";
    case GAMEMESSAGE_PLAYERDRAWFROMGRAVEYARD:   return "player-draw-from-graveyard";
    case GAMEMESSAGE_PLAYERDISCARDCARD:         return "player-discard-card";
    case GAMEMESSAGE_PLAYERPLAYCARD:            return "player-play-card";
    case GAMEMESSAGE_PLAYERRESPONDWITHCARD:     return "player-respond-with-card";
    case GAMEMESSAGE_PLAYERPASS:                return "player-pass";
    case GAMEMESSAGE_PLAYERPICKFROMSELECTION:   return "player-pick-from-selection";
    case GAMEMESSAGE_PLAYERCHECKDECK:           return "player-check-deck";
    case GAMEMESSAGE_PLAYERSTEALCARD:           return "player-steal-card";
    case GAMEMESSAGE_PLAYERCANCELCARD:          return "player-cancel-card";
    case GAMEMESSAGE_DECKREGENERATE:            return "deck-regenerate";
    case GAMEMESSAGE_PLAYERDIED:                return "player-died";
    case GAMEMESSAGE_INVALID:                   return "";
    }
    return "";
}

void GameMessage::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "game-message");
    type            = StringToGameMessageType(node->attribute("type"));
    player          = node->attribute("player").toInt();
    targetPlayer    = node->attribute("targetPlayer").toInt();
    causedBy        = node->attribute("causedBy").toInt();
    checkResult     = node->attribute("checkResult") == "true";
    cards.clear();
    foreach(XmlNode* child, node->getChildren()) {
        if (child->name() == "card")
            card.read(child);
        else if (child->name() == "targetCard")
            targetCard.read(child);
        else if (child->name() == "cards") {
            foreach (XmlNode* cardNode, child->getChildren()) {
                CardData cardData;
                cardData.read(cardNode);
                cards.append(cardData);
            }
        }
    }
}

void GameMessage::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("game-message");
    writer->writeAttribute("type", GameMessageTypeToString(type));
    if (player)
        writer->writeAttribute("player", QString::number(player));
    if (targetPlayer)
        writer->writeAttribute("targetPlayer", QString::number(targetPlayer));
    if (causedBy)
        writer->writeAttribute("causedBy", QString::number(causedBy));
    if (type == GAMEMESSAGE_PLAYERCHECKDECK)
        writer->writeAttribute("checkResult", checkResult ? "true" : "false");
    if (card.id)
        card.write(writer, "card");
    if (targetCard.id)
        targetCard.write(writer, "targetCard");
    if (cards.size() > 0) {
        writer->writeStartElement("cards");
        foreach(const CardData& cardData, cards)
            cardData.write(writer);
        writer->writeEndElement();
    }
    writer->writeEndElement();
}



void PlayerInfoData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "player");
    id              = node->attribute("id").toInt();
    name            = node->attribute("name");
    hasPassword     = node->attribute("hasPassword") == "true";
    hasController   = node->attribute("hasController") == "true";
    isAI            = node->attribute("isAI") == "true";
}

void PlayerInfoData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("player");
    writer->writeAttribute("id",            QString::number(id));
    writer->writeAttribute("name",          name);
    writer->writeAttribute("hasPassword",   hasPassword ? "true" : "false");
    writer->writeAttribute("hasController", hasController ? "true" : "false");
    writer->writeAttribute("isAI",          isAI ? "true" : "false");
    writer->writeEndElement();
}

void CreatePlayerData::read(XmlNode* node)
{
    name        = node->attribute("name");
    password    = node->attribute("password");
    XmlNode* avatarNode = node->getFirstChild();
    if (avatarNode && avatarNode->name() == "avatar") {
        readAvatar(avatarNode, avatar);
    }
}

void CreatePlayerData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("player");
    writer->writeAttribute("name", name);
    if (!password.isNull())
        writer->writeAttribute("password", password);
    writeAvatar(writer, avatar);
    writer->writeEndElement();
}

void CreateGameData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "game");
    name                = node->attribute("name");
    description         = node->attribute("description");
    minPlayers          = node->attribute("minPlayers").toInt();
    maxPlayers          = node->attribute("maxPlayers").toInt();
    maxSpectators       = node->attribute("maxSpectators").toInt();
    AIPlayers           = node->attribute("AIPlayers").toInt();
    playerPassword      = node->attribute("playerPassword");
    spectatorPassword   = node->attribute("spectatorPassword");
    flagShufflePlayers  = node->attribute("shufflePlayers") == "true";
}

void CreateGameData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("game");
    writer->writeAttribute("name",                  name);
    writer->writeAttribute("description",           description);
    writer->writeAttribute("minPlayers",            QString::number(minPlayers));
    writer->writeAttribute("maxPlayers",            QString::number(maxPlayers));
    writer->writeAttribute("maxSpectators",         QString::number(maxSpectators));
    writer->writeAttribute("AIPlayers",             QString::number(AIPlayers));
    if (!playerPassword.isNull())
        writer->writeAttribute("playerPassword",        playerPassword);
    if (!spectatorPassword.isNull())
        writer->writeAttribute("spectatorPassword",     spectatorPassword);
    writer->writeAttribute("shufflePlayers",        flagShufflePlayers ? "true" : "false");
    writer->writeEndElement();
}


void GameInfoData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "game-info");
    id                  = node->attribute("id").toInt();
    name                = node->attribute("name");
    description         = node->attribute("description");
    minPlayers          = node->attribute("minPlayers").toInt();
    maxPlayers          = node->attribute("maxPlayers").toInt();
    maxSpectators       = node->attribute("maxSpectators").toInt();
    alivePlayersCnt     = node->attribute("alivePlayersCnt").toInt();
    totalPlayersCnt     = node->attribute("totalPlayersCnt").toInt();
    spectatorsCnt       = node->attribute("spectatorsCnt").toInt();
    AIPlayersCnt        = node->attribute("AIPlayersCnt").toInt();
    hasPlayerPassword   = node->attribute("hasPlayerpassword") == "true";
    hasSpectatorPassword= node->attribute("hasSpectatorPassword") == "true";
    state               = StringToGameState(node->attribute("state"));
    players.clear();
    foreach(XmlNode* child, node->getChildren()) {
        PlayerInfoData playerInfo;
        if (child->name() != "player") continue;
        playerInfo.read(child);
        players.append(playerInfo);
    }
}

void GameInfoData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("game-info");
    writer->writeAttribute("id",                    QString::number(id));
    writer->writeAttribute("name",                  name);
    writer->writeAttribute("description",           description);
    writer->writeAttribute("minPlayers",            QString::number(minPlayers));
    writer->writeAttribute("maxPlayers",            QString::number(maxPlayers));
    writer->writeAttribute("maxSpectators",         QString::number(maxSpectators));
    writer->writeAttribute("alivePlayersCnt",       QString::number(alivePlayersCnt));
    writer->writeAttribute("totalPlayersCnt",       QString::number(totalPlayersCnt));
    writer->writeAttribute("spectatorsCnt",         QString::number(spectatorsCnt));
    writer->writeAttribute("AIPlayersCnt",          QString::number(AIPlayersCnt));
    writer->writeAttribute("hasPlayerPassword",     hasPlayerPassword ? "true" : "false");
    writer->writeAttribute("hasSpectatorPassword",  hasPlayerPassword ? "true" : "false");
    writer->writeAttribute("state",                 GameStateToString(state));
    foreach(const PlayerInfoData& playerInfo, players) {
        playerInfo.write(writer);
    }
    writer->writeEndElement();
}

void GameInfoListData::read(XmlNode* node)
{
    Q_ASSERT(node->name() == "games-info");
    clear();
    foreach(XmlNode* child, node->getChildren()) {
        GameInfoData gameInfoData;
        if (child->name() != "game-info")
            continue;
        gameInfoData.read(child);
        append(gameInfoData);
    }
}

void GameInfoListData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("games-info");
    foreach(const GameInfoData& gameInfoData, *this) {
        gameInfoData.write(writer);
    }
    writer->writeEndElement();
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

void StructGame::read(XmlNode* node)
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
    /*
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
    */
}

void StructGame::write(QXmlStreamWriter* writer) const
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
    /*
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
    */
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
    foreach(XmlNode* child, node->getChildren()) {
        if (child->name() == "card")
            card.read(child);
        else if (child->name() == "second-card")
            secondCard.read(child);
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
    if (secondCard.id != 0)
        secondCard.write(writer, "second-card");

    writer->writeEndElement();
}


