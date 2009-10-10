/***************************************************************************7
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

#include "gamestructparser.h"
#include "parser/simpletypeparser.h"
#include "xmlnode.h"
#include "util.h"

/*[[[cog
import cog
from gamestructdefs import *
]]]
[[[end]]]*/

/* static */
void GameStructParser::write(QXmlStreamWriter* w, const GameStruct& d)
{
    switch(d.t()) {
    /*[[[cog
    for s in GameStructs:
        cog.outl("case GameStruct::%(gameStructType)s: write(w, static_cast<const %(structName)s&>(d));" % s)
        cog.outl("    break;")
    ]]]*/
    case GameStruct::ServerInfoDataType: write(w, static_cast<const ServerInfoData&>(d));
        break;
    case GameStruct::PlayerInfoDataType: write(w, static_cast<const PlayerInfoData&>(d));
        break;
    case GameStruct::PlayerInfoListDataType: write(w, static_cast<const PlayerInfoListData&>(d));
        break;
    case GameStruct::GameInfoDataType: write(w, static_cast<const GameInfoData&>(d));
        break;
    case GameStruct::GameInfoListDataType: write(w, static_cast<const GameInfoListData&>(d));
        break;
    case GameStruct::UrlListDataType: write(w, static_cast<const UrlListData&>(d));
        break;
    case GameStruct::CardSetInfoDataType: write(w, static_cast<const CardSetInfoData&>(d));
        break;
    case GameStruct::CardSetInfoListDataType: write(w, static_cast<const CardSetInfoListData&>(d));
        break;
    case GameStruct::CreatePlayerDataType: write(w, static_cast<const CreatePlayerData&>(d));
        break;
    case GameStruct::CreateGameDataType: write(w, static_cast<const CreateGameData&>(d));
        break;
    case GameStruct::CardDataType: write(w, static_cast<const CardData&>(d));
        break;
    case GameStruct::CardListDataType: write(w, static_cast<const CardListData&>(d));
        break;
    case GameStruct::PublicPlayerDataType: write(w, static_cast<const PublicPlayerData&>(d));
        break;
    case GameStruct::PublicPlayerListDataType: write(w, static_cast<const PublicPlayerListData&>(d));
        break;
    case GameStruct::PrivatePlayerDataType: write(w, static_cast<const PrivatePlayerData&>(d));
        break;
    case GameStruct::GameContextDataType: write(w, static_cast<const GameContextData&>(d));
        break;
    case GameStruct::GameSyncDataType: write(w, static_cast<const GameSyncData&>(d));
        break;
    case GameStruct::CardIdListDataType: write(w, static_cast<const CardIdListData&>(d));
        break;
    //[[[end]]]
    }
}

/* static */
GameStruct* GameStructParser::read(XmlNode* n)
{
    /*[[[cog
    cog.outl("GameStruct* res = 0;")
    for s in GameStructs:
        cog.outl("if (n->name() == %(elemName)s) {" % s)
        cog.outl("    %(structName)s* data = new %(structName)s();" % s)
        cog.outl("    read(n, *data);")
        cog.outl("    res = data;")
        cog.out("} else ")
    cog.outl("{\n}")
    cog.outl("return res;")
    ]]]*/
    GameStruct* res = 0;
    if (n->name() == "server-info") {
        ServerInfoData* data = new ServerInfoData();
        read(n, *data);
        res = data;
    } else if (n->name() == "player-info") {
        PlayerInfoData* data = new PlayerInfoData();
        read(n, *data);
        res = data;
    } else if (n->name() == "player-info-list") {
        PlayerInfoListData* data = new PlayerInfoListData();
        read(n, *data);
        res = data;
    } else if (n->name() == "game-info") {
        GameInfoData* data = new GameInfoData();
        read(n, *data);
        res = data;
    } else if (n->name() == "game-info-list") {
        GameInfoListData* data = new GameInfoListData();
        read(n, *data);
        res = data;
    } else if (n->name() == "url-list") {
        UrlListData* data = new UrlListData();
        read(n, *data);
        res = data;
    } else if (n->name() == "card-set-info") {
        CardSetInfoData* data = new CardSetInfoData();
        read(n, *data);
        res = data;
    } else if (n->name() == "card-set-info-list") {
        CardSetInfoListData* data = new CardSetInfoListData();
        read(n, *data);
        res = data;
    } else if (n->name() == "create-player") {
        CreatePlayerData* data = new CreatePlayerData();
        read(n, *data);
        res = data;
    } else if (n->name() == "create-game") {
        CreateGameData* data = new CreateGameData();
        read(n, *data);
        res = data;
    } else if (n->name() == "card") {
        CardData* data = new CardData();
        read(n, *data);
        res = data;
    } else if (n->name() == "card-list") {
        CardListData* data = new CardListData();
        read(n, *data);
        res = data;
    } else if (n->name() == "public-player") {
        PublicPlayerData* data = new PublicPlayerData();
        read(n, *data);
        res = data;
    } else if (n->name() == "public-player-list") {
        PublicPlayerListData* data = new PublicPlayerListData();
        read(n, *data);
        res = data;
    } else if (n->name() == "private-player-list") {
        PrivatePlayerData* data = new PrivatePlayerData();
        read(n, *data);
        res = data;
    } else if (n->name() == "game-context") {
        GameContextData* data = new GameContextData();
        read(n, *data);
        res = data;
    } else if (n->name() == "game-sync") {
        GameSyncData* data = new GameSyncData();
        read(n, *data);
        res = data;
    } else if (n->name() == "card-id-list") {
        CardIdListData* data = new CardIdListData();
        read(n, *data);
        res = data;
    } else {
    }
    return res;
    //[[[end]]]
}

/*[[[cog
for s in GameStructs:
    cog.outl("void GameStructParser::write(QXmlStreamWriter* w, const %(structName)s& d, const char* elemName)" % s)
    cog.outl(s.genWriter("w", "d", False, "elemName"))
    cog.outl("")
    cog.outl("void GameStructParser::read(XmlNode* n, %(structName)s& d)" % s)
    cog.outl(s.genReader1())
    cog.outl("")
]]]*/
void GameStructParser::write(QXmlStreamWriter* w, const ServerInfoData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "server-info");
    w->writeAttribute("name", toString(d.name));
    w->writeAttribute("desc", toString(d.desc));
    w->writeAttribute("admin-name", toString(d.adminName));
    w->writeAttribute("admin-email", toString(d.adminEmail));
    w->writeAttribute("games-cnt", toString(d.gamesCnt));
    w->writeAttribute("players-cnt", toString(d.playersCnt));
    w->writeAttribute("clients-cnt", toString(d.clientsCnt));
    w->writeAttribute("start-time", toString(d.startTime));
    w->writeAttribute("motd", toString(d.motd));
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, ServerInfoData& d)
{
    fromString(n->attribute("name"), d.name);
    fromString(n->attribute("desc"), d.desc);
    fromString(n->attribute("admin-name"), d.adminName);
    fromString(n->attribute("admin-email"), d.adminEmail);
    fromString(n->attribute("games-cnt"), d.gamesCnt);
    fromString(n->attribute("players-cnt"), d.playersCnt);
    fromString(n->attribute("clients-cnt"), d.clientsCnt);
    fromString(n->attribute("start-time"), d.startTime);
    fromString(n->attribute("motd"), d.motd);
}

void GameStructParser::write(QXmlStreamWriter* w, const PlayerInfoData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "player-info");
    w->writeAttribute("id", toString(d.id));
    w->writeAttribute("name", toString(d.name));
    w->writeAttribute("has-password", toString(d.hasPassword));
    w->writeAttribute("has-controller", toString(d.hasController));
    w->writeAttribute("is-ai", toString(d.isAI));
    w->writeAttribute("is-alive", toString(d.isAlive));
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, PlayerInfoData& d)
{
    fromString(n->attribute("id"), d.id);
    fromString(n->attribute("name"), d.name);
    fromString(n->attribute("has-password"), d.hasPassword);
    fromString(n->attribute("has-controller"), d.hasController);
    fromString(n->attribute("is-ai"), d.isAI);
    fromString(n->attribute("is-alive"), d.isAlive);
}

void GameStructParser::write(QXmlStreamWriter* w, const PlayerInfoListData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "player-info-list");
    foreach (const PlayerInfoData& item, d) {
        GameStructParser::write(w, item);
    }
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, PlayerInfoListData& d)
{
    d.clear();
    foreach (XmlNode* ch, n->getChildren()) {
        PlayerInfoData item;
        GameStructParser::read(ch, item);
        d.append(item);
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const GameInfoData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "game-info");
    w->writeAttribute("id", toString(d.id));
    w->writeAttribute("name", toString(d.name));
    w->writeAttribute("desc", toString(d.desc));
    w->writeAttribute("players-min", toString(d.playersMin));
    w->writeAttribute("players-max", toString(d.playersMax));
    w->writeAttribute("players-cnt", toString(d.playersCnt));
    w->writeAttribute("alive-players-cnt", toString(d.alivePlayersCnt));
    w->writeAttribute("ai-players-cnt", toString(d.aiPlayersCnt));
    w->writeAttribute("spectators-max", toString(d.spectatorsMax));
    w->writeAttribute("spectators-cnt", toString(d.spectatorsCnt));
    w->writeAttribute("has-player-password", toString(d.hasPlayerPassword));
    w->writeAttribute("has-spectator-password", toString(d.hasSpectatorPassword));
    w->writeAttribute("game-state", toString(d.gameState));
    GameStructParser::write(w, d.players, "players");
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, GameInfoData& d)
{
    fromString(n->attribute("id"), d.id);
    fromString(n->attribute("name"), d.name);
    fromString(n->attribute("desc"), d.desc);
    fromString(n->attribute("players-min"), d.playersMin);
    fromString(n->attribute("players-max"), d.playersMax);
    fromString(n->attribute("players-cnt"), d.playersCnt);
    fromString(n->attribute("alive-players-cnt"), d.alivePlayersCnt);
    fromString(n->attribute("ai-players-cnt"), d.aiPlayersCnt);
    fromString(n->attribute("spectators-max"), d.spectatorsMax);
    fromString(n->attribute("spectators-cnt"), d.spectatorsCnt);
    fromString(n->attribute("has-player-password"), d.hasPlayerPassword);
    fromString(n->attribute("has-spectator-password"), d.hasSpectatorPassword);
    fromString(n->attribute("game-state"), d.gameState);
    foreach (XmlNode* ch, n->getChildren()) {
        if (ch->name() == "players") {
            GameStructParser::read(ch, d.players);
            continue;
        }
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const GameInfoListData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "game-info-list");
    foreach (const GameInfoData& item, d) {
        GameStructParser::write(w, item);
    }
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, GameInfoListData& d)
{
    d.clear();
    foreach (XmlNode* ch, n->getChildren()) {
        GameInfoData item;
        GameStructParser::read(ch, item);
        d.append(item);
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const UrlListData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "url-list");
    foreach (const QString& item, d) {
        w->writeTextElement("url", toString(item));
    }
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, UrlListData& d)
{
    d.clear();
    foreach (XmlNode* ch, n->getChildren()) {
        QString item;
        fromString(ch->text(), item);
        d.append(item);
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const CardSetInfoData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "card-set-info");
    w->writeAttribute("id", toString(d.id));
    w->writeAttribute("name", toString(d.name));
    w->writeAttribute("locales", toString(d.locales));
    w->writeAttribute("slot-id", toString(d.slotId));
    w->writeAttribute("format-version", toString(d.formatVersion));
    w->writeAttribute("revision", toString(d.revision));
    GameStructParser::write(w, d.downloadLinks, "download-links");
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, CardSetInfoData& d)
{
    fromString(n->attribute("id"), d.id);
    fromString(n->attribute("name"), d.name);
    fromString(n->attribute("locales"), d.locales);
    fromString(n->attribute("slot-id"), d.slotId);
    fromString(n->attribute("format-version"), d.formatVersion);
    fromString(n->attribute("revision"), d.revision);
    foreach (XmlNode* ch, n->getChildren()) {
        if (ch->name() == "download-links") {
            GameStructParser::read(ch, d.downloadLinks);
            continue;
        }
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const CardSetInfoListData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "card-set-info-list");
    foreach (const CardSetInfoData& item, d) {
        GameStructParser::write(w, item);
    }
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, CardSetInfoListData& d)
{
    d.clear();
    foreach (XmlNode* ch, n->getChildren()) {
        CardSetInfoData item;
        GameStructParser::read(ch, item);
        d.append(item);
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const CreatePlayerData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "create-player");
    w->writeAttribute("name", toString(d.name));
    w->writeAttribute("password", toString(d.password));
    GameStructParser::write(w, d.avatar, "avatar");
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, CreatePlayerData& d)
{
    fromString(n->attribute("name"), d.name);
    fromString(n->attribute("password"), d.password);
    foreach (XmlNode* ch, n->getChildren()) {
        if (ch->name() == "avatar") {
            GameStructParser::read(ch, d.avatar);
            continue;
        }
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const CreateGameData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "create-game");
    w->writeAttribute("name", toString(d.name));
    w->writeAttribute("desc", toString(d.desc));
    w->writeAttribute("players-min", toString(d.playersMin));
    w->writeAttribute("players-max", toString(d.playersMax));
    w->writeAttribute("spectators-max", toString(d.spectatorsMax));
    w->writeAttribute("ai-players-cnt", toString(d.aiPlayersCnt));
    w->writeAttribute("player-password", toString(d.playerPassword));
    w->writeAttribute("spectator-password", toString(d.spectatorPassword));
    GameStructParser::write(w, d.options, "options");
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, CreateGameData& d)
{
    fromString(n->attribute("name"), d.name);
    fromString(n->attribute("desc"), d.desc);
    fromString(n->attribute("players-min"), d.playersMin);
    fromString(n->attribute("players-max"), d.playersMax);
    fromString(n->attribute("spectators-max"), d.spectatorsMax);
    fromString(n->attribute("ai-players-cnt"), d.aiPlayersCnt);
    fromString(n->attribute("player-password"), d.playerPassword);
    fromString(n->attribute("spectator-password"), d.spectatorPassword);
    foreach (XmlNode* ch, n->getChildren()) {
        if (ch->name() == "options") {
            GameStructParser::read(ch, d.options);
            continue;
        }
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const CardData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "card");
    w->writeAttribute("id", toString(d.id));
    w->writeAttribute("name", toString(d.name));
    w->writeAttribute("type", toString(d.type));
    w->writeAttribute("suit", toString(d.suit));
    w->writeAttribute("rank", toString(d.rank));
    w->writeAttribute("is-ready", toString(d.isReady));
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, CardData& d)
{
    fromString(n->attribute("id"), d.id);
    fromString(n->attribute("name"), d.name);
    fromString(n->attribute("type"), d.type);
    fromString(n->attribute("suit"), d.suit);
    fromString(n->attribute("rank"), d.rank);
    fromString(n->attribute("is-ready"), d.isReady);
}

void GameStructParser::write(QXmlStreamWriter* w, const CardListData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "card-list");
    foreach (const CardData& item, d) {
        GameStructParser::write(w, item);
    }
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, CardListData& d)
{
    d.clear();
    foreach (XmlNode* ch, n->getChildren()) {
        CardData item;
        GameStructParser::read(ch, item);
        d.append(item);
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const PublicPlayerData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "public-player");
    w->writeAttribute("id", toString(d.id));
    w->writeAttribute("name", toString(d.name));
    w->writeAttribute("has-password", toString(d.hasPassword));
    w->writeAttribute("has-controller", toString(d.hasController));
    w->writeAttribute("is-ai", toString(d.isAI));
    w->writeAttribute("is-alive", toString(d.isAlive));
    w->writeAttribute("is-winner", toString(d.isWinner));
    w->writeAttribute("is-sheriff", toString(d.isSheriff));
    w->writeAttribute("character", toString(d.character));
    w->writeAttribute("takenCharacter", toString(d.takenCharacter));
    w->writeAttribute("life-points", toString(d.lifePoints));
    w->writeAttribute("hand-size", toString(d.handSize));
    w->writeAttribute("role", toString(d.role));
    GameStructParser::write(w, d.avatar, "avatar");
    GameStructParser::write(w, d.table, "table");
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, PublicPlayerData& d)
{
    fromString(n->attribute("id"), d.id);
    fromString(n->attribute("name"), d.name);
    fromString(n->attribute("has-password"), d.hasPassword);
    fromString(n->attribute("has-controller"), d.hasController);
    fromString(n->attribute("is-ai"), d.isAI);
    fromString(n->attribute("is-alive"), d.isAlive);
    fromString(n->attribute("is-winner"), d.isWinner);
    fromString(n->attribute("is-sheriff"), d.isSheriff);
    fromString(n->attribute("character"), d.character);
    fromString(n->attribute("takenCharacter"), d.takenCharacter);
    fromString(n->attribute("life-points"), d.lifePoints);
    fromString(n->attribute("hand-size"), d.handSize);
    fromString(n->attribute("role"), d.role);
    foreach (XmlNode* ch, n->getChildren()) {
        if (ch->name() == "avatar") {
            GameStructParser::read(ch, d.avatar);
            continue;
        }
        if (ch->name() == "table") {
            GameStructParser::read(ch, d.table);
            continue;
        }
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const PublicPlayerListData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "public-player-list");
    foreach (const PublicPlayerData& item, d) {
        GameStructParser::write(w, item);
    }
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, PublicPlayerListData& d)
{
    d.clear();
    foreach (XmlNode* ch, n->getChildren()) {
        PublicPlayerData item;
        GameStructParser::read(ch, item);
        d.append(item);
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const PrivatePlayerData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "private-player-list");
    w->writeAttribute("id", toString(d.id));
    w->writeAttribute("role", toString(d.role));
    GameStructParser::write(w, d.hand, "hand");
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, PrivatePlayerData& d)
{
    fromString(n->attribute("id"), d.id);
    fromString(n->attribute("role"), d.role);
    foreach (XmlNode* ch, n->getChildren()) {
        if (ch->name() == "hand") {
            GameStructParser::read(ch, d.hand);
            continue;
        }
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const GameContextData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "game-context");
    w->writeAttribute("current-player-id", toString(d.currentPlayerId));
    w->writeAttribute("requested-player-id", toString(d.requestedPlayerId));
    w->writeAttribute("turn-number", toString(d.turnNumber));
    w->writeAttribute("game-play-state", toString(d.gamePlayState));
    w->writeAttribute("reaction-type", toString(d.reactionType));
    w->writeAttribute("caused-by", toString(d.causedBy));
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, GameContextData& d)
{
    fromString(n->attribute("current-player-id"), d.currentPlayerId);
    fromString(n->attribute("requested-player-id"), d.requestedPlayerId);
    fromString(n->attribute("turn-number"), d.turnNumber);
    fromString(n->attribute("game-play-state"), d.gamePlayState);
    fromString(n->attribute("reaction-type"), d.reactionType);
    fromString(n->attribute("caused-by"), d.causedBy);
}

void GameStructParser::write(QXmlStreamWriter* w, const GameSyncData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "game-sync");
    w->writeAttribute("id", toString(d.id));
    w->writeAttribute("name", toString(d.name));
    w->writeAttribute("is-creator", toString(d.isCreator));
    w->writeAttribute("game-state", toString(d.gameState));
    GameStructParser::write(w, d.players, "players");
    GameStructParser::write(w, d.localPlayer, "local-player");
    GameStructParser::write(w, d.gameContext, "game-context");
    GameStructParser::write(w, d.graveyard, "graveyard");
    GameStructParser::write(w, d.selection, "selection");
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, GameSyncData& d)
{
    fromString(n->attribute("id"), d.id);
    fromString(n->attribute("name"), d.name);
    fromString(n->attribute("is-creator"), d.isCreator);
    fromString(n->attribute("game-state"), d.gameState);
    foreach (XmlNode* ch, n->getChildren()) {
        if (ch->name() == "players") {
            GameStructParser::read(ch, d.players);
            continue;
        }
        if (ch->name() == "local-player") {
            GameStructParser::read(ch, d.localPlayer);
            continue;
        }
        if (ch->name() == "game-context") {
            GameStructParser::read(ch, d.gameContext);
            continue;
        }
        if (ch->name() == "graveyard") {
            GameStructParser::read(ch, d.graveyard);
            continue;
        }
        if (ch->name() == "selection") {
            GameStructParser::read(ch, d.selection);
            continue;
        }
    }
}

void GameStructParser::write(QXmlStreamWriter* w, const CardIdListData& d, const char* elemName)
{
    w->writeStartElement(elemName ? elemName : "card-id-list");
    foreach (const CardId& item, d) {
        w->writeTextElement("card-id", toString(item));
    }
    w->writeEndElement();
}


void GameStructParser::read(XmlNode* n, CardIdListData& d)
{
    d.clear();
    foreach (XmlNode* ch, n->getChildren()) {
        CardId item;
        fromString(ch->text(), item);
        d.append(item);
    }
}

//[[[end]]]

void GameStructParser::write(QXmlStreamWriter* w, const QByteArray& d, const char* elemName)
{
    w->writeTextElement(elemName, d.toBase64());
}

void GameStructParser::read(XmlNode* n, QByteArray& d)
{
    d.clear();
    d = QByteArray::fromBase64(n->text().toAscii());
}

void GameStructParser::write(QXmlStreamWriter* w, const QMap<QString, QVariant>& d, const char* elemName)
{
    w->writeStartElement(elemName);
    foreach (const QString& key, d.keys()) {
        const QVariant& value = d[key];
        w->writeStartElement("element");
        w->writeAttribute("name", key);
        w->writeAttribute("type", value.typeName());
        w->writeAttribute("value", value.toString());
        w->writeEndElement();
    }
    w->writeEndElement();
}
void GameStructParser::read(XmlNode*n, QMap<QString, QVariant>& d)
{
    d.clear();
    foreach (const XmlNode* ch, n->getChildren()) {
        const QString& name = ch->attribute("name");
        const QString& type = ch->attribute("type");
        const QString& value = ch->attribute("value");
        /// @todo convert string to QVariant
    }
}


