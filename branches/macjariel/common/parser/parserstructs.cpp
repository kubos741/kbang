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
#include "xmlnode.h"
#include <QXmlStreamWriter>

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
    writer->writeAttribute("id", QString::number(id));
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

void StructPlayer::read(XmlNode* node)
{
    id = node->attribute("id").toInt();
    name = node->attribute("name");
    password = node->attribute("password");
}

void StructPlayer::write(QXmlStreamWriter* writer, bool writePassword) const
{
    writer->writeStartElement("player");
    writer->writeAttribute("id", QString::number(id));
    writer->writeAttribute("name", name);
    if (writePassword)
        writer->writeAttribute("password", password);
    writer->writeEndElement();
}


