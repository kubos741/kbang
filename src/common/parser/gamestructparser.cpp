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

#include "gamestructparser.h"
#include "xmlnode.h"
#include "util.h"

/* static */
QString GameStructParser::elementName(GameStruct::Type type)
{
    switch(type) {
    case InvalidType:       return "";
        break;
    case ServerInfoType:    return "server-info";
        break;
    case PlayerInfoType:    return "player-info";
        break;
    case GameInfoType:      return "game-info";
        break;
    case CardSetInfoType:   return "cardset-info";
        break;
    case CreatePlayerType:  return "create-player";
        break;
    case CreateGameType:    return "create-game";
        break;
    case CardDataType:      return "card";
        break;
    case PublicPlayerType:  return "public-player";
        break;
    case PrivatePlayerType: return "private-player";
        break;
    case GameContextType:   return "game-context";
        break;
    case GameSyncType:      return "game-sync";
        break;
    }
}

/* static */
void GameStructParser::writeServerInfo(QXmlStreamWriter* w, const ServerInfoData& d)
{
    w->writeStartElement(elementName(d.t()));
    w->writeAttribute("name",        d.name);
    w->writeAttribute("desc",        d.desc);
    w->writeAttribute("admin-name",  d.adminName);
    w->writeAttribute("admin-email", d.adminEmail);
    w->writeAttribute("games-cnt",   intToString(d.gamesCnt));
    w->writeAttribute("players-cnt", intToString(d.playersCnt));
    w->writeAttribute("clients-cnt", intToString(d.clientsCnt));
    w->writeAttribute("start-time",  d.startTime.toUTC().toString(Qt::ISODate));
    w->writeAttribute("motd",        d.motd);
    w->writeEndElement();
}

/* static */
void GameStructParser::readServerInfo(XmlNode* n, ServerInfoData& d)
{
    d.name          = n->attribute("name");
    d.desc          = n->attribute("desc");
    d.adminName     = n->attribute("admin-name");
    d.adminEmail    = n->attribute("admin-email");
    d.gamesCnt      = stringToInt(n->attribute("games-cnt"));
    d.playersCnt    = stringToInt(n->attribute("players-cnt"));
    d.clientsCnt    = stringToInt(n->attribute("clients-cnt"));
    d.startTime     = QDateTime::fromString(n->attribute("start-time"),
                                            Qt::ISODate).toLocalTime();
    d.motd          = n->attribute("motd");
}

/* static */
void GameStructParser::writePlayerInfo(QXmlStreamWriter* w, const PlayerInfoData& d)
{
    w->writeStartElement(elementName(d.t()));
    w->writeAttribute("id",                intToString(d.id));
    w->writeAttribute("name",              d.name);
    w->writeAttribute("has-password",      boolToString(d.hasPassword));
    w->writeAttribute("has-controller",    boolToString(d.hasController));
    w->writeAttribute("is-ai",             boolToString(d.isAI));
    w->writeAttribute("is-alive",          boolToString(d.isAlive));
    w->writeEndElement();
}


/* static */
void GameStructParser::readPlayerInfo(XmlNode* n, PlayerInfoData& d)
{
    d.id              = stringToInt(n->attribute("id"));
    d.name            = n->attribute("name");
    d.hasPassword     = stringToBool(n->attribute("has-password"));
    d.hasController   = stringToBool(n->attribute("has-controller"));
    d.isAI            = stringToBool(n->attribute("is-ai"));
    d.isAlive         = stringToBool(n->attribute("is-alive"));
}

/* static */
void GameStructParser::writeGameInfo(QXmlStreamWriter* w, const GameInfoData& d)
{
    w->writeStartElement(elementName(d.t()));
    w->writeAttribute("id",                    intToString(d.id));
    w->writeAttribute("name",                  d.name);
    w->writeAttribute("desc",                  d.desc);
    w->writeAttribute("players-min",           intToString(d.playersMin));
    w->writeAttribute("players-max",           intToString(d.playersMax));
    w->writeAttribute("players-cnt",           intToString(d.playersCnt));
    w->writeAttribute("alive-players-cnt",     intToString(d.alivePlayersCnt));
    w->writeAttribute("ai-players-cnt",        intToString(d.aiPlayersCnt));
    w->writeAttribute("spectators-max",        intToString(d.spectatorsMax));
    w->writeAttribute("spectators-cnt",        intToString(d.spectatorsCnt));
    w->writeAttribute("has-player-password",   boolToString(d.hasPlayerPassword));
    w->writeAttribute("has-spectator-password",boolToString(d.hasSpectatorPassword));
    w->writeAttribute("game-state",            gameStateToString(d.gameState));
    foreach(const PlayerInfoData& playerInfo, d.players) {
        writePlayerInfo(w, playerInfo);
    }
    w->writeEndElement();
}


/* static */
void GameStructParser::readGameInfo(XmlNode* n, GameInfoData& d)
{
    d.id                   = stringToInt(n->attribute("id"));
    d.name                 = n->attribute("name");
    d.desc                 = n->attribute("desc");
    d.playersMin           = stringToInt(n->attribute("players-min"));
    d.playersMax           = stringToInt(n->attribute("players-max"));
    d.playersCnt           = stringToInt(n->attribute("players-cnt"));
    d.alivePlayersCnt      = stringToInt(n->attribute("alive-players-cnt"));
    d.aiPlayersCnt         = stringToInt(n->attribute("ai-players-cnt"));
    d.spectatorsMax        = stringToInt(n->attribute("spectators-max"));
    d.spectatorsCnt        = stringToInt(n->attribute("spectators-cnt"));
    d.hasPlayerPassword    = stringToBool(n->attribute("has-player-password"));
    d.hasSpectatorPassword = stringToBool(n->attribute("has-spectator-password"));
    d.gameState            = stringToGameState(n->attribute("game-state"));
    d.players.clear();
    foreach(XmlNode* child, n->getChildren()) {
        PlayerInfoData playerInfo;
        if (child->name() != elementName(playerInfo.t())) {
            continue;
        }
        readPlayerInfo(child, playerInfo);
        players.append(playerInfo);
    }


}


/* static */
void GameStructParser::writeCardSetInfo(QXmlStreamWriter* w, const CardSetInfoData& d)
{

}


/* static */
void GameStructParser::readCardSetInfo(XmlNode* n, CardSetInfoData& d)
{

}


/* static */
void GameStructParser::writeCreatePlayer(QXmlStreamWriter* w, const CreatePlayerData& d)
{

}


/* static */
void GameStructParser::readCreatePlayer(XmlNode* n, CreatePlayerData& d)
{

}


/* static */
void GameStructParser::writeCreateGame(QXmlStreamWriter* w, const CreateGameData& d)
{

}


/* static */
void GameStructParser::readCreateGame(XmlNode* n, CreateGameData& d)
{

}


/* static */
void GameStructParser::writeCard(QXmlStreamWriter* w, const CardData& d)
{
    w->writeAttribute("id",        intToString(d.id));
    w->writeAttribute("name",      d.name);
    w->writeAttribute("type",      cardTypeToString(d.type));
    w->writeAttribute("suit",      cardSuitToString(d.suit));
    w->writeAttribute("rank",      cardRankToString(d.rank));
    w->writeAttribute("is-ready",  boolToString(d.isReady));
}

/* static */
void GameStructParser::readCard(XmlNode* n, CardData& d)
{
    d.id          = stringToInt(n->attribute("id"));
    d.name        = n->attribute("name");
    d.type        = stringToCardType(n->attribute("type"));
    d.suit        = stringToCardSuit(n->attribute("suit"));
    d.rank        = stringToCardRank(n->attribute("rank"));
    d.isReady     = stringToBool(n->attribute("is-ready"));
}

/* static */
void GameStructParser::writePublicPlayer(QXmlStreamWriter* w, const PublicPlayerData& d)
{

}


/* static */
void GameStructParser::readPublicPlayer(XmlNode* n, PublicPlayerData& d)
{

}


/* static */
void GameStructParser::writePrivatePlayer(QXmlStreamWriter* w, const PrivatePlayerData& d)
{

}


/* static */
void GameStructParser::readPrivatePlayer(XmlNode* n, PrivatePlayerData& d)
{

}


/* static */
void GameStructParser::writeGameContext(QXmlStreamWriter* w, const GameContextData& d)
{

}


/* static */
void GameStructParser::readGameContext(XmlNode* n, GameContextData& d)
{

}


/* static */
void GameStructParser::writeGameSync(QXmlStreamWriter* w, const GameSyncData& d)
{

}


/* static */
void GameStructParser::readGameSync(XmlNode* n, GameSyncData& d)
{

}
