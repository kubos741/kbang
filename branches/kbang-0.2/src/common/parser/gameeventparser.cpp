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

#include "gameeventparser.h"
#include "parser/gamestructparser.h"
#include "gametypes.h"
#include "util.h"

#include "debug/debugblock.h"

#include <QMapIterator>

/* static */
void GameEventParser::write(QXmlStreamWriter* w, GameEventDataPtr e)
{
    DEBUG_BLOCK;
    w->writeStartElement("game-event");
    w->writeAttribute("game-id", intToString(e->gameId));
    w->writeAttribute("type", GameEventData::typeToString(e->type));
    if (e->playerId != 0) {
        w->writeAttribute("player-id", intToString(e->playerId));
    }
    if (e->targetPlayerId != 0) {
        w->writeAttribute("target-player-id", intToString(e->targetPlayerId));
    }
    if (e->type == GameEventData::CheckDeckType) {
        w->writeAttribute("success", boolToString(e->success));
    }
    if (e->useAbility) {
        w->writeAttribute("use-ability", boolToString(e->useAbility));
    }
    QMapIterator<GameEventData::CardMeaning, CardData> it(e->cards);
    while (it.hasNext()) {
        it.next();
        w->writeStartElement(GameEventData::cardMeaningToString(it.key()));
        GameStructParser::writeCard(w, it.value());
        w->writeEndElement();
    }
    foreach (GameEventCmdDataPtr CmdData, e->cmds) {
        writeCmdData(w, CmdData);
    }
    w->writeEndElement();
}

/* static */
GameEventDataPtr GameEventParser::read(XmlNode* node)
{
    DEBUG_BLOCK;
    GameEventDataPtr e(new GameEventData());
    if (node->name() != "game-event") {
        return GameEventDataPtr();
    }
    e->gameId           = stringToInt(node->attribute("game-id"));
    e->type             = GameEventData::stringToType(node->attribute("type"));
    e->playerId         = stringToInt(node->attribute("player-id"));
    e->targetPlayerId   = stringToInt(node->attribute("target-player-id"));
    e->success          = stringToBool(node->attribute("success"));
    e->useAbility       = stringToBool(node->attribute("use-ability"));
    GameEventData::CardMeaning cardMeaning;
    foreach (XmlNode* CmdData, node->getChildren()) {
        cardMeaning = GameEventData::stringToCardMeaning(CmdData->name());
         if (cardMeaning != GameEventData::NoCard) {
             GameStructParser::readCard(CmdData, e->cards[cardMeaning]);
         } else {
             e->cmds.append(readCmdData(CmdData));
         }
    }
    return e;
}



/* static */
void GameEventParser::writeCmdData(QXmlStreamWriter* w, GameEventCmdDataPtr a)
{
    DEBUG_BLOCK;
    switch(a->type()) {
    case GameEventCmdData::CardMovementType:
        writeCardMovementCmdData(w, a.staticCast<CardMovementCmdData>());
        break;
    case GameEventCmdData::UpdatePlayerType:
        writeUpdatePlayerCmdData(w, a.staticCast<UpdatePlayerCmdData>());
        break;
    case GameEventCmdData::GameContextType:
        writeGameContextCmdData(w, a.staticCast<GameContextCmdData>());
        break;
    case GameEventCmdData::SetPlayersType:
        writeSetPlayersCmdData(w, a.staticCast<SetPlayersCmdData>());
    }
}


/* static */ void
GameEventParser::writeCardMovementCmdData(QXmlStreamWriter* writer, CardMovementCmdDataPtr a)
{
    DEBUG_BLOCK;
    writer->writeStartElement("card-movement");
    writer->writeAttribute("pocket-type-from", pocketTypeToString(a->pocketTypeFrom));
    writer->writeAttribute("pocket-type-to", pocketTypeToString(a->pocketTypeTo));
    if (a->playerFrom != 0) {
        writer->writeAttribute("player-from", intToString(a->playerFrom));
    }
    if (a->playerTo != 0) {
        writer->writeAttribute("player-to", intToString(a->playerTo));
    }
    if (a->card.id != 0) {
        writer->writeStartElement("card");
        GameStructParser::writeCard(writer, a->card);
        writer->writeEndElement();
    }
    if (a->secondCard.id != 0) {
        writer->writeStartElement("second-card");
        GameStructParser::writeCard(writer, a->secondCard);
        writer->writeEndElement();
    }
    writer->writeEndElement();
}

/* static */ void
GameEventParser::writeUpdatePlayerCmdData(QXmlStreamWriter* writer, UpdatePlayerCmdDataPtr a)
{
    DEBUG_BLOCK;
    writer->writeStartElement("update-player");
    writer->writeAttribute("player-id", intToString(a->playerId));
    if (a->hasFlag(UpdatePlayerCmdData::IsAliveAttr)) {
        writer->writeAttribute("is-alive", boolToString(a->isAlive));
    }
    if (a->hasFlag(UpdatePlayerCmdData::IsWinnerAttr)) {
        writer->writeAttribute("is-winner", boolToString(a->isWinner));
    }
    if (a->hasFlag(UpdatePlayerCmdData::TakenCharacterAttr)) {
        writer->writeAttribute("taken-character", a->takenCharacter);
    }
    if (a->hasFlag(UpdatePlayerCmdData::LifePointsAttr)) {
        writer->writeAttribute("life-points", intToString(a->lifePoints));
    }
    if (a->hasFlag(UpdatePlayerCmdData::RoleAttr)) {
        writer->writeAttribute("role", playerRoleToString(a->role));
    }
    writer->writeEndElement();
}

/* static */ void
GameEventParser::writeGameContextCmdData(QXmlStreamWriter* writer, GameContextCmdDataPtr a)
{
    DEBUG_BLOCK;
    writer->writeStartElement("game-context");
    writer->writeAttribute("current-player-id",   intToString(a->gameContext.currentPlayerId));
    writer->writeAttribute("requested-player-id", intToString(a->gameContext.requestedPlayerId));
    writer->writeAttribute("turn-number",         intToString(a->gameContext.turnNumber));
    writer->writeAttribute("game-play-state",     gamePlayStateToString(a->gameContext.gamePlayState));
    writer->writeAttribute("reaction-type",       reactionTypeToString(a->gameContext.reactionType));
    writer->writeAttribute("caused-by",           intToString(a->gameContext.causedBy));
    writer->writeEndElement();
}

/* static */
void GameEventParser::writeSetPlayersCmdData(QXmlStreamWriter* writer,
                                             SetPlayersCmdDataPtr cmd)
{
    DEBUG_BLOCK;
    writer->writeStartElement("set-players");
    foreach (const SetPlayersCmdData::PlayerData& player, cmd->players) {
        writer->writeStartElement("player");
        writer->writeAttribute("id", intToString(player.id));
        writer->writeAttribute("name", player.name);
        writer->writeAttribute("character", player.character);
        writer->writeAttribute("role", playerRoleToString(player.role));
        writer->writeEndElement();
    }
    writer->writeEndDocument();
}

/* static */
GameEventCmdDataPtr GameEventParser::readCmdData(XmlNode* node)
{
    DEBUG_BLOCK;
    if (node->name() == "card-movement") {
        return readCardMovementCmdData(node);
    } else if (node->name() == "update-player") {
        return readUpdatePlayerCmdData(node);
    } else if (node->name() == "game-context") {
        return readGameContextCmdData(node);
    } else if (node->name() == "set-players") {
        return readSetPlayersCmdData(node);
    }
    return GameEventCmdDataPtr();
}

/* static */
GameEventCmdDataPtr GameEventParser::readCardMovementCmdData(XmlNode* node)
{
    DEBUG_BLOCK;
    CardMovementCmdDataPtr a(new CardMovementCmdData());
    a->pocketTypeFrom = stringToPocketType(node->attribute("pocket-type-from"));
    a->pocketTypeTo   = stringToPocketType(node->attribute("pocket-type-to"));
    a->playerFrom     = stringToInt(node->attribute("player-from"));
    a->playerTo       = stringToInt(node->attribute("player-to"));
    foreach(XmlNode* child, node->getChildren()) {
        if (child->name() == "card") {
            GameStructParser::readCard(child, a->card);
        } else if (child->name() == "second-card") {
            GameStructParser::readCard(child, a->secondCard);
        }
    }
    return a;
}

/* static */
GameEventCmdDataPtr GameEventParser::readUpdatePlayerCmdData(XmlNode* node)
{
    DEBUG_BLOCK;
    UpdatePlayerCmdDataPtr a(new UpdatePlayerCmdData());
    a->playerId = stringToInt(node->attribute("id"));
    if (!node->attribute("is-alive").isEmpty()) {
        a->isAlive = stringToBool(node->attribute("is-alive"));
        a->setFlag(UpdatePlayerCmdData::IsAliveAttr);
    }
    if (!node->attribute("is-winner").isEmpty()) {
        a->isWinner = stringToBool(node->attribute("is-winner"));
        a->setFlag(UpdatePlayerCmdData::IsWinnerAttr);
    }
    if (!node->attribute("taken-character").isEmpty()) {
        a->takenCharacter = node->attribute("taken-character");
        a->setFlag(UpdatePlayerCmdData::TakenCharacterAttr);
    }
    if (!node->attribute("life-points").isEmpty()) {
        a->lifePoints = stringToInt(node->attribute("life-points"));
        a->setFlag(UpdatePlayerCmdData::LifePointsAttr);
    }
    if (!node->attribute("role").isEmpty()) {
        a->role = stringToPlayerRole(node->attribute("role"));
        a->setFlag(UpdatePlayerCmdData::RoleAttr);
    }
    return a;
}

/* static */
GameEventCmdDataPtr GameEventParser::readGameContextCmdData(XmlNode* node)
{
    DEBUG_BLOCK;
    GameContextCmdDataPtr a(new GameContextCmdData());
    a->gameContext.currentPlayerId = stringToInt(node->attribute("current-player-id"));
    a->gameContext.requestedPlayerId = stringToInt(node->attribute("requested-player-id"));
    a->gameContext.turnNumber = stringToInt(node->attribute("turn-number"));
    a->gameContext.gamePlayState = stringToGamePlayState(node->attribute("game-play-state"));
    a->gameContext.reactionType = stringToReactionType(node->attribute("reaction-type"));
    a->gameContext.causedBy = stringToInt(node->attribute("caused-by"));
    return a;
}

/* static */
GameEventCmdDataPtr GameEventParser::readSetPlayersCmdData(XmlNode* node)
{
    DEBUG_BLOCK;
    SetPlayersCmdDataPtr a(new SetPlayersCmdData());
    foreach (XmlNode* child, node->getChildren()) {
        SetPlayersCmdData::PlayerData player;
        player.id = stringToInt(child->attribute("id"));
        player.name = child->attribute("name");
        player.character = child->attribute("character");
        player.role = stringToPlayerRole(child->attribute("role"));
        a->players.append(player);
    }
    return a;
}
