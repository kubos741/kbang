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

#include "servereventparser.h"
#include "gamestructparser.h"
#include "util.h"

/* static */
void ServerEventParser::write(QXmlStreamWriter* w, ServerEventDataPtr e)
{
    w->writeStartElement("server-event");
    switch (e->type()) {
    case ServerEventData::EnterGameType: writeEnterGame(w, e.staticCast<EnterGameEventData>());
        break;
    case ServerEventData::ExitGameType: writeExitGame(w, e.staticCast<ExitGameEventData>());
        break;
    case ServerEventData::CreatePlayerType: writeCreatePlayer(w, e.staticCast<CreatePlayerEventData>());
        break;
    case ServerEventData::RemovePlayerType: writeRemovePlayer(w, e.staticCast<RemovePlayerEventData>());
        break;
    case ServerEventData::ChatMessageType: writeChatMessage(w, e.staticCast<ChatMessageEventData>());
        break;
    case ServerEventData::GameUpdateType: writeGameUpdate(w, e.staticCast<GameUpdateEventData>());
        break;
    }
    w->writeEndElement();
}

/* static */
ServerEventDataPtr ServerEventParser::read(XmlNode* node)
{
    if (node->name() != "server-event" || node->getFirstChild() == 0) {
        return ServerEventDataPtr();
    }
    node = node->getFirstChild();
    if (node->name() == "enter-game") {
        return readEnterGame(node);
    } else if (node->name() == "exit-game") {
        return readExitGame(node);
    } else if (node->name() == "create-player") {
        return readCreatePlayer(node);
    } else if (node->name() == "remove-player") {
        return readRemovePlayer(node);
    } else if (node->name() == "chat-message") {
        return readChatMessage(node);
    } else if (node->name() == "game-update") {
        return readGameUpdate(node);
    }
    return ServerEventDataPtr();
}

/* static */
void ServerEventParser::writeEnterGame(QXmlStreamWriter* w, EnterGameEventDataPtr e)
{
    const GameSyncData& g = e->gameSyncData;
    w->writeStartElement("enter-game");
    w->writeAttribute("game-id", intToString(g.id));
    w->writeAttribute("game-name", g.name);
    w->writeAttribute("game-state", gameStateToString(g.gameState));
    if (g.localPlayer.id != 0) {
        w->writeAttribute("player-id", intToString(g.localPlayer.id));
    }
    ///@todo last-event-id
    w->writeStartElement("players");
    foreach (const PublicPlayerData& p, g.players) {
        p.write(w);
    }
    g.localPlayer.write(w);
    w->writeEndElement();
    g.gameContext.write(w);

    w->writeStartElement("graveyard");
    GameStructParser::writeCard(w, g.graveyard);
    w->writeEndElement();

    w->writeStartElement("selection");
    foreach (const CardData& c, g.selection) {
        w->writeStartElement("card");
        GameStructParser::writeCard(w, c);;
        w->writeEndElement();
    }
    w->writeEndElement();
    w->writeEndElement();
}

/* static */
ServerEventDataPtr ServerEventParser::readEnterGame(XmlNode* node)
{
    EnterGameEventDataPtr res(new EnterGameEventData());
    GameSyncData& g = res->gameSyncData;
    g.id        = stringToInt(node->attribute("game-id"));
    g.name      = node->attribute("game-name");
    g.gameState = stringToGameState(node->attribute("game-state"));
    foreach (XmlNode* child, node->getChildren()) {
        if (child->name() == "players") {
            foreach (XmlNode* plr, child->getChildren()) {
                if (plr->name() == "public-player") {
                    g.players.append(GameStructParser::readPublicPlayer(plr));
                } else if (plr->name() == "private-player") {
                    GameStructParser::readPrivatePlayer(plr, g.localPlayer);
                }
            }
        } else if (child->name() == "game-context") {
            g.gameContext.read(child);
        } else if (child->name() == "graveyard") {
            GameStructParser::readCard(child, g.graveyard);
        } else if (child->name() == "selection") {
            foreach (XmlNode* crd, child->getChildren()) {
                g.selection.append(GameStructParser::readCard(crd));
            }
        }
    }
    return res;
}

/* static */
void ServerEventParser::writeExitGame(QXmlStreamWriter* w, ExitGameEventDataPtr e)
{
    w->writeStartElement("exit-game");
    w->writeAttribute("game-id", intToString(e->gameId));
    w->writeEndElement();
}

/* static */
ServerEventDataPtr ServerEventParser::readExitGame(XmlNode*)
{
///@todo
}

/* static */
void ServerEventParser::writeCreatePlayer(QXmlStreamWriter* w, CreatePlayerEventDataPtr e)
{
    w->writeStartElement("create-player");
    w->writeAttribute("game-id", intToString(e->gameId));
    GameStructParser::writePublicPlayer(w, e->publicPlayerData);
    w->writeEndElement();
}

/* static */
ServerEventDataPtr ServerEventParser::readCreatePlayer(XmlNode*)
{
///@todo
}

/* static */
void ServerEventParser::writeRemovePlayer(QXmlStreamWriter* w, RemovePlayerEventDataPtr e)
{
    w->writeStartElement("remove-player");
    w->writeAttribute("game-id", intToString(e->gameId));
    w->writeAttribute("player-id", intToString(e->playerId));
    w->writeEndElement();
}

/* static */
ServerEventDataPtr ServerEventParser::readRemovePlayer(XmlNode*)
{
///@todo
}

/* static */
void ServerEventParser::writeChatMessage(QXmlStreamWriter* w, ChatMessageEventDataPtr e)
{
    w->writeStartElement("chat-message");
    w->writeAttribute("game-id", intToString(e->gameId));
    w->writeAttribute("client-id", intToString(e->clientId));
    w->writeAttribute("player-id", intToString(e->playerId));
    w->writeAttribute("sender-name", e->senderName);
    w->writeCharacters(e->text);
    w->writeEndElement();
}

/* static */
ServerEventDataPtr ServerEventParser::readChatMessage(XmlNode*)
{
///@todo
}

/* static */
void ServerEventParser::writeGameUpdate(QXmlStreamWriter* w, GameUpdateEventDataPtr e)
{
    w->writeStartElement("game-update");
    w->writeAttribute("game-id", intToString(e->gameId));
    if (e->hasFlag(GameUpdateEventData::IsStartableAttr)) {
        w->writeAttribute("is-startable", boolToString(e->isStartable));
    }
    w->writeEndElement();
}

/* static */
ServerEventDataPtr ServerEventParser::readGameUpdate(XmlNode*)
{
///@todo
}
