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

#include "queryresult.h"
#include "parser.h"
#include <QXmlStreamWriter>

QueryResult::QueryResult(QXmlStreamWriter* streamWriter, const QString& id):
mp_streamWriter(streamWriter), m_id(id), m_sent(0)
{
}

void QueryResult::sendData(const StructServerInfo& data)
{
    writeStartQuery();
    mp_streamWriter->writeStartElement("serverinfo");
    mp_streamWriter->writeAttribute("name", data.name);
    mp_streamWriter->writeAttribute("description", data.description);
    mp_streamWriter->writeEndElement();
    writeEndQuery();
}

void QueryResult::writeStartQuery()
{
    mp_streamWriter->writeStartElement("query");
    mp_streamWriter->writeAttribute("type", "result");
    mp_streamWriter->writeAttribute("id", m_id);
}

void QueryResult::writeEndQuery()
{
    mp_streamWriter->writeEndElement();
}

void QueryResult::sendData(const StructGame& game)
{
    writeStartQuery();
    writeGame(game);
    writeEndQuery();
}

void QueryResult::sendData(const StructGame& game, const StructPlayerList& playerList)
{
    writeStartQuery();
    writeGame(game, &playerList);
    writeEndQuery();
}


void QueryResult::sendData(const StructGameList& gamelist)
{
    writeStartQuery();
    mp_streamWriter->writeStartElement("gamelist");
    foreach(const StructGame& i, gamelist)
    {
        writeGame(i);
    }
    mp_streamWriter->writeEndElement();
    writeEndQuery();
}


void QueryResult::writeGame(const StructGame& game, const StructPlayerList* playerlist)
{
    mp_streamWriter->writeStartElement("game");
    mp_streamWriter->writeAttribute("id", QString::number(game.id));
    mp_streamWriter->writeAttribute("name", game.name);
    mp_streamWriter->writeAttribute("minPlayers", QString::number(game.minPlayers));
    mp_streamWriter->writeAttribute("maxPlayers", QString::number(game.maxPlayers));
    mp_streamWriter->writeAttribute("maxSpectators", QString::number(game.maxSpectators));
    mp_streamWriter->writeAttribute("hasPlayerPassword", game.hasPlayerPassword ? "1" : "0");
    mp_streamWriter->writeAttribute("hasSpectatorPassword", game.hasPlayerPassword ? "1" : "0");
    mp_streamWriter->writeAttribute("flagShufflePlayers", game.flagShufflePlayers ? "1" : "0");
    if (playerlist)
    {
        mp_streamWriter->writeStartElement("players");
        foreach(const StructPlayer& i, *playerlist)
        {
            mp_streamWriter->writeStartElement("player");
            mp_streamWriter->writeAttribute("id", QString::number(i.id));
            mp_streamWriter->writeAttribute("name", i.name);
            mp_streamWriter->writeEndElement();
        }
        mp_streamWriter->writeEndElement();
    }
    mp_streamWriter->writeEndElement();
}




