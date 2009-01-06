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

void StructCardMovement::read(XmlNode* node)
{
    pocketTypeFrom = stringToPocketType(node->attribute("pocketTypeFrom"));
    pocketTypeTo   = stringToPocketType(node->attribute("pocketTypeTo"));
    playerFrom     = node->attribute("playerFrom").toInt();
    playerTo       = node->attribute("playerTo").toInt();
    cardDetails.cardId   = node->attribute("cardId").toInt();
    cardDetails.cardType = node->attribute("cardType");
}

void StructCardMovement::write(QXmlStreamWriter* writer) const
{
    writer->writeStartElement("card-movement");
    writer->writeAttribute("pocketTypeFrom", pocketTypeToString(pocketTypeFrom));
    writer->writeAttribute("pocketTypeTo", pocketTypeToString(pocketTypeTo));
    if (playerFrom != 0)
        writer->writeAttribute("playerFrom", QString::number(playerFrom));
    if (playerTo != 0)
        writer->writeAttribute("playerTo", QString::number(playerTo));
    if (cardDetails.cardId != 0)
    {
        writer->writeAttribute("cardId", QString::number(cardDetails.cardId));
        writer->writeAttribute("cardType", cardDetails.cardType);
    }
    writer->writeEndElement();
}


