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

/**
 * @file gamestructs.cpp
 * The implementation of game structures' read and write methods.
 */

#include <QBuffer>

#include "gamestructs.h"
#include "parser/xmlnode.h"
#include "util.h"           // stringToBool() and boolToString() functions

#define READ_ELEMENT_NAME_CHECK { if (node->name() != elementName) { return 0; } }

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

QString ServerInfoData::elementName("server-info");

bool
ServerInfoData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    name = node->attribute("name");
    desc = node->attribute("desc");
    return 1;
}

void
ServerInfoData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("name", name);
    writer->writeAttribute("desc", desc);
    writer->writeEndElement();
}

QString PlayerInfoData::elementName("player-info");

bool
PlayerInfoData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    id              = stringToInt(node->attribute("id"));
    name            = node->attribute("name");
    hasPassword     = stringToBool(node->attribute("has-password"));
    hasController   = stringToBool(node->attribute("has-controller"));
    isAI            = stringToBool(node->attribute("is-ai"));
    isAlive         = stringToBool(node->attribute("is-alive"));
    return 1;
}

void
PlayerInfoData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("id",                intToString(id));
    writer->writeAttribute("name",              name);
    writer->writeAttribute("has-password",      boolToString(hasPassword));
    writer->writeAttribute("has-controller",    boolToString(hasController));
    writer->writeAttribute("is-ai",             boolToString(isAI));
    writer->writeAttribute("is-alive",          boolToString(isAlive));
    writer->writeEndElement();
}

QString GameInfoData::elementName("game-info");

bool
GameInfoData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    id                   = stringToInt(node->attribute("id"));
    name                 = node->attribute("name");
    desc                 = node->attribute("desc");
    playersMin           = stringToInt(node->attribute("players-min"));
    playersMax           = stringToInt(node->attribute("players-max"));
    playersCnt           = stringToInt(node->attribute("players-cnt"));
    alivePlayersCnt      = stringToInt(node->attribute("alive-players-cnt"));
    aiPlayersCnt         = stringToInt(node->attribute("ai-players-cnt"));
    spectatorsMax        = stringToInt(node->attribute("spectators-max"));
    spectatorsCnt        = stringToInt(node->attribute("spectators-cnt"));
    hasPlayerPassword    = stringToBool(node->attribute("has-player-password"));
    hasSpectatorPassword = stringToBool(node->attribute("has-spectator-password"));
    gameState            = stringToGameState(node->attribute("game-state"));
    players.clear();
    foreach(XmlNode* child, node->getChildren()) {
        PlayerInfoData playerInfo;
        if (child->name() != PlayerInfoData::elementName) {
            continue;
        }
        playerInfo.read(child);
        players.append(playerInfo);
    }
    return 1;
}

void
GameInfoData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("id",                    intToString(id));
    writer->writeAttribute("name",                  name);
    writer->writeAttribute("desc",                  desc);
    writer->writeAttribute("players-min",           intToString(playersMin));
    writer->writeAttribute("players-max",           intToString(playersMax));
    writer->writeAttribute("players-cnt",           intToString(playersCnt));
    writer->writeAttribute("alive-players-cnt",     intToString(alivePlayersCnt));
    writer->writeAttribute("ai-players-cnt",        intToString(aiPlayersCnt));
    writer->writeAttribute("spectators-max",        intToString(spectatorsMax));
    writer->writeAttribute("spectators-cnt",        intToString(spectatorsCnt));
    writer->writeAttribute("has-player-password",   boolToString(hasPlayerPassword));
    writer->writeAttribute("has-spectator-password",boolToString(hasSpectatorPassword));
    writer->writeAttribute("game-state",            gameStateToString(gameState));
    foreach(const PlayerInfoData& playerInfo, players) {
        playerInfo.write(writer);
    }
    writer->writeEndElement();
}

QString GameInfoListData::elementName("game-info-list");

bool
GameInfoListData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    clear();
    foreach(XmlNode* child, node->getChildren()) {
        GameInfoData gameInfoData;
        if (child->name() != GameInfoData::elementName) {
            continue;
        }
        gameInfoData.read(child);
        append(gameInfoData);
    }
    return 1;
}

void
GameInfoListData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    foreach(const GameInfoData& gameInfoData, *this) {
        gameInfoData.write(writer);
    }
    writer->writeEndElement();
}

QString CreatePlayerData::elementName("create-player");

bool
CreatePlayerData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    name        = node->attribute("name");
    password    = node->attribute("password");
    XmlNode* avatarNode = node->getFirstChild();
    if (avatarNode && avatarNode->name() == "avatar") {
        readAvatar(avatarNode, avatar);
    }
    return 1;
}

void
CreatePlayerData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("name", name);
    if (!password.isNull()) {
        writer->writeAttribute("password", password);
    }
    writeAvatar(writer, avatar);
    writer->writeEndElement();
}

QString CreateGameData::elementName("create-game");

bool
CreateGameData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    name                = node->attribute("name");
    desc                = node->attribute("desc");
    playersMin          = stringToInt(node->attribute("players-min"));
    playersMax          = stringToInt(node->attribute("players-max"));
    spectatorsMax       = stringToInt(node->attribute("spectators-max"));
    aiPlayersCnt        = stringToInt(node->attribute("ai-players-cnt"));
    playerPassword      = node->attribute("player-password");
    spectatorPassword   = node->attribute("spectator-password");
    flagShufflePlayers  = stringToBool(node->attribute("shuffle-players"));
    return 1;
}

void
CreateGameData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("name",              name);
    writer->writeAttribute("desc",              desc);
    writer->writeAttribute("players-min",       intToString(playersMin));
    writer->writeAttribute("players-max",       intToString(playersMax));
    writer->writeAttribute("spectators-max",    intToString(spectatorsMax));
    writer->writeAttribute("ai-players-cnt",    intToString(aiPlayersCnt));
    if (!playerPassword.isEmpty()) {
        writer->writeAttribute("player-password", playerPassword);
    }
    if (!spectatorPassword.isEmpty()) {
        writer->writeAttribute("spectator-password", spectatorPassword);
    }
    writer->writeAttribute("shuffle-players", boolToString(flagShufflePlayers));
    writer->writeEndElement();
}

QString CardData::elementName("card");

bool
CardData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    id          = stringToInt(node->attribute("id"));
    name        = node->attribute("name");
    type        = stringToCardType(node->attribute("type"));
    suit        = stringToCardSuit(node->attribute("suit"));
    rank        = stringToCardRank(node->attribute("rank"));
    isReady     = stringToBool(node->attribute("is-ready"));
    return 1;
}

void
CardData::write(QXmlStreamWriter* writer) const
{

    writer->writeStartElement(elementName);
    writer->writeAttribute("id",        intToString(id));
    writer->writeAttribute("name",      name);
    writer->writeAttribute("type",      cardTypeToString(type));
    writer->writeAttribute("suit",      cardSuitToString(suit));
    writer->writeAttribute("rank",      cardRankToString(rank));
    writer->writeAttribute("is-ready",  boolToString(isReady));
    writer->writeEndElement();
}

QString PublicPlayerData::elementName("public-player");

bool
PublicPlayerData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    id              = stringToInt(node->attribute("id"));
    name            = node->attribute("name");
    hasPassword     = stringToBool(node->attribute("has-password"));
    hasController   = stringToBool(node->attribute("has-controller"));
    isAI            = stringToBool(node->attribute("is-ai"));
    isAlive         = stringToBool(node->attribute("is-alive"));
    isWinner        = stringToBool(node->attribute("is-winner"));
    isSheriff       = stringToBool(node->attribute("is-sheriff"));
    character       = node->attribute("character");
    takenCharacter  = node->attribute("taken-character");
    lifePoints      = stringToInt(node->attribute("life-points"));
    handSize        = stringToInt(node->attribute("hand-size"));
    role            = stringToPlayerRole(node->attribute("role"));

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
    return 1;
}

void
PublicPlayerData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("id",                intToString(id));
    writer->writeAttribute("name",              name);
    writer->writeAttribute("has-password",      boolToString(hasPassword));
    writer->writeAttribute("has-controller",    boolToString(hasController));
    writer->writeAttribute("is-ai",             boolToString(isAI));
    writer->writeAttribute("is-alive",          boolToString(isAlive));
    writer->writeAttribute("is-winner",         boolToString(isWinner));
    writer->writeAttribute("is-sheriff",        boolToString(isSheriff));
    writer->writeAttribute("character",         character);
    if (!takenCharacter.isEmpty()) {
        writer->writeAttribute("taken-character", takenCharacter);
    }
    writer->writeAttribute("life-points",       intToString(lifePoints));
    writer->writeAttribute("hand-size",         intToString(handSize));
    writer->writeAttribute("role",              playerRoleToString(role));
    writer->writeStartElement("cards-table");
    foreach(const CardData& cardData, table)
        cardData.write(writer);
    writer->writeEndElement();
    writeAvatar(writer, avatar);
    writer->writeEndElement();
}

QString PrivatePlayerData::elementName("private-player");

bool
PrivatePlayerData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    id      = stringToInt(node->attribute("id"));
    role    = stringToPlayerRole(node->attribute("role"));
    XmlNode* cards = node->getFirstChild();
    if (cards && cards->name() == "cards-hand") {
        hand.clear();
        foreach(XmlNode* card, cards->getChildren()) {
            CardData cardData;
            cardData.read(card);
            hand.append(cardData);
        }
    }
    return 1;
}

void
PrivatePlayerData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("id",                intToString(id));
    writer->writeAttribute("role",              playerRoleToString(role));
    writer->writeStartElement("cards-hand");
    foreach(const CardData& cardData, hand)
        cardData.write(writer);
    writer->writeEndElement();
    writer->writeEndElement();
}

QString GameContextData::elementName("game-context");

bool
GameContextData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    currentPlayerId     = stringToInt(node->attribute("current-player-id"));
    requestedPlayerId   = stringToInt(node->attribute("requested-player-id"));
    turnNumber          = stringToInt(node->attribute("turn-number"));
    gamePlayState       = stringToGamePlayState(node->attribute("game-play-state"));
    reactionType        = stringToReactionType(node->attribute("reaction-type"));
    causedBy            = stringToInt(node->attribute("caused-by"));
    return 1;
}

void
GameContextData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("current-player-id",   intToString(currentPlayerId));
    writer->writeAttribute("requested-player-id", intToString(requestedPlayerId));
    writer->writeAttribute("turn-number",         intToString(turnNumber));
    writer->writeAttribute("game-play-state",     gamePlayStateToString(gamePlayState));
    writer->writeAttribute("reaction-type",       reactionTypeToString(reactionType));
    writer->writeAttribute("caused-by",           intToString(causedBy));
    writer->writeEndElement();
}

QString GameSyncData::elementName("game-sync");

bool
GameSyncData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    id          = stringToInt(node->attribute("id"));
    name        = node->attribute("name");
    isCreator   = stringToBool(node->attribute("is-creator"));
    gameState   = stringToGameState(node->attribute("game-state"));
    players.clear();
    selection.clear();
    foreach (XmlNode* child, node->getChildren()) {
        if (child->name() == "players") {            
            foreach(XmlNode* player, child->getChildren()) {
                PublicPlayerData publicPlayerData;
                publicPlayerData.read(player);
                players.append(publicPlayerData);
            }
        } else if (child->name() == "graveyard" && child->getFirstChild() != 0) {
            graveyard.read(child->getFirstChild());
        } else if (child->name() == "selection") {
            foreach(XmlNode* cardNode, child->getChildren()) {
                CardData card;
                card.read(cardNode);
                selection.append(card);
            }
        } else if (child->name() == PrivatePlayerData::elementName) {
            localPlayer.read(child);
        } else if (child->name() == GameContextData::elementName) {
            gameContext.read(child);
        }
    }
    return 1;
}

void
GameSyncData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);

    writer->writeAttribute("id",            intToString(id));
    writer->writeAttribute("name",          name);
    writer->writeAttribute("is-creator",    boolToString(isCreator));
    writer->writeAttribute("game-state",    gameStateToString(gameState));

    writer->writeStartElement("players");
    foreach (const PublicPlayerData& p, players)
        p.write(writer);
    writer->writeEndElement();
    localPlayer.write(writer);
    gameContext.write(writer);

    writer->writeStartElement("graveyard");
    graveyard.write(writer);
    writer->writeEndElement();

    writer->writeStartElement("selection");
    foreach (const CardData& c, selection)
        c.write(writer);
    writer->writeEndElement();

    writer->writeEndElement();
}

QString GameMessage::elementName("game-message");

bool
GameMessage::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    type            = stringToGameMessageType(node->attribute("type"));
    player          = stringToInt(node->attribute("player"));
    targetPlayer    = stringToInt(node->attribute("target-player"));
    causedBy        = stringToInt(node->attribute("caused-by"));
    checkResult     = stringToBool(node->attribute("check-result"));
    cards.clear();
    foreach(XmlNode* child, node->getChildren()) {
        if (child->name() == "card")
            card.read(child);
        else if (child->name() == "target-card")
            targetCard.read(child->getFirstChild());
        else if (child->name() == "cards") {
            foreach (XmlNode* cardNode, child->getChildren()) {
                CardData cardData;
                cardData.read(cardNode);
                cards.append(cardData);
            }
        }
    }
    return 1;
}

void
GameMessage::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("type", gameMessageTypeToString(type));
    if (player) {
        writer->writeAttribute("player", intToString(player));
    }
    if (targetPlayer) {
        writer->writeAttribute("target-player", intToString(targetPlayer));
    }
    if (causedBy) {
        writer->writeAttribute("caused-by", intToString(causedBy));
    }
    if (type == GAMEMESSAGE_PLAYERCHECKDECK) {
        writer->writeAttribute("check-result", boolToString(checkResult));
    }
    if (card.id) {
        card.write(writer);
    }
    if (targetCard.id) {
        writer->writeStartElement("target-card");
        targetCard.write(writer);
        writer->writeEndElement();
    }
    if (cards.size() > 0) {
        writer->writeStartElement("cards");
        foreach(const CardData& cardData, cards)
            cardData.write(writer);
        writer->writeEndElement();
    }
    writer->writeEndElement();
}

QString CardMovementData::elementName("card-movement");

bool
CardMovementData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK
    pocketTypeFrom = stringToPocketType(node->attribute("pocket-type-from"));
    pocketTypeTo   = stringToPocketType(node->attribute("pocket-type-to"));
    playerFrom     = stringToInt(node->attribute("player-from"));
    playerTo       = stringToInt(node->attribute("player-to"));
    foreach(XmlNode* child, node->getChildren()) {
        if (child->name() == "card") {
            card.read(child);
        } else if (child->name() == "second-card") {
            secondCard.read(child->getFirstChild());
        }
    }
    return 1;
}

void
CardMovementData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("pocket-type-from", pocketTypeToString(pocketTypeFrom));
    writer->writeAttribute("pocket-type-to", pocketTypeToString(pocketTypeTo));
    if (playerFrom != 0) {
        writer->writeAttribute("player-from", intToString(playerFrom));
    }
    if (playerTo != 0) {
        writer->writeAttribute("player-to", intToString(playerTo));
    }
    if (card.id != 0) {
        card.write(writer);
    }
    if (secondCard.id != 0) {
        writer->writeStartElement("second-card");
        secondCard.write(writer);
        writer->writeEndElement();
    }
    writer->writeEndElement();
}


QString ActionPlayCardData::elementName("play-card");

bool
ActionPlayCardData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    playedCardId    = stringToInt(node->attribute("played-card-id"));
    targetCardId    = stringToInt(node->attribute("target-card-id"));
    discardCardId   = stringToInt(node->attribute("discard-card-id"));
    targetPlayerId  = stringToInt(node->attribute("target-player-id"));
    return 1;
}

void
ActionPlayCardData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    writer->writeAttribute("played-card-id",    intToString(playedCardId));
    writer->writeAttribute("target-card-id",    intToString(targetCardId));
    writer->writeAttribute("discard-card-id",   intToString(discardCardId));
    writer->writeAttribute("target-player-id",  intToString(targetPlayerId));
    writer->writeEndElement();
}

QString ActionUseAbilityData::elementName("use-ability");

bool
ActionUseAbilityData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    targetPlayerId = stringToInt(node->attribute("target-player-id"));
    targetCardsId.clear();
    if (node->getFirstChild() && node->getFirstChild()->name() == "target-cards") {
        foreach (XmlNode* cardNode, node->getFirstChild()->getChildren()) {
            targetCardsId.append(stringToInt(cardNode->attribute("id")));
        }
    }
    return 1;
}

void
ActionUseAbilityData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    if (targetPlayerId != 0) {
        writer->writeAttribute("target-player-id", intToString(targetPlayerId));
    }
    if (!targetCardsId.isEmpty()) {
        writer->writeStartElement("target-cards");
        foreach(int cardId, targetCardsId) {
            writer->writeStartElement("card");
            writer->writeAttribute("id", intToString(cardId));
            writer->writeEndElement();
        }
        writer->writeEndElement();
    }
    writer->writeEndElement();
}

QString ChatMessageData::elementName("chat-message");

bool
ChatMessageData::read(XmlNode* node)
{
    READ_ELEMENT_NAME_CHECK;
    clientId   = stringToInt(node->attribute("client-id"));
    playerId   = stringToInt(node->attribute("player-id"));
    senderName = node->attribute("sender-name");

    XmlNode* textNode = node->getFirstChild();
    if (!textNode || !textNode->isTextElement()) {
        return 0;
    }
    text = textNode->text();
    return 1;
}

void
ChatMessageData::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement(elementName);
    if (clientId != 0) {
        writer->writeAttribute("client-id", intToString(clientId));
    }
    if (playerId != 0) {
        writer->writeAttribute("player-id", intToString(playerId));
    }
    if (!senderName.isEmpty()) {
        writer->writeAttribute("sender-name", senderName);
    }
    writer->writeCharacters(text);
    writer->writeEndElement();
}
