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


#include "parser/conversions.h"

StructGame getGameFromXml(XmlNode* node)
{
    StructGame x;
    //if (node->name() == "game")
    //{
        x.id = node->attribute("id").toInt();
        x.creatorId = node->attribute("creatorId").toInt();
        x.name = node->attribute("name");
        x.description = node->attribute("description");
        x.minPlayers = node->attribute("minPlayers").toInt();
        x.maxPlayers = node->attribute("maxPlayers").toInt();
        x.maxSpectators = node->attribute("maxSpectators").toInt();
        x.playerPassword = node->attribute("playerPassword");
        x.spectatorPassword = node->attribute("spectatorPassword");
        x.hasPlayerPassword = (node->attribute("hasPlayerPassword") == "1");
        x.hasSpectatorPassword = (node->attribute("hasSpectatorPassword") == "1");
        x.flagShufflePlayers = (node->attribute("flagShufflePlayers") == "1");
    //}
    return x;
}

StructPlayer getPlayerFromXml(XmlNode* node)
{
    StructPlayer x;
    x.id = node->attribute("id").toInt();
    x.name = node->attribute("name");
    x.password = node->attribute("password");
    return x;
}
