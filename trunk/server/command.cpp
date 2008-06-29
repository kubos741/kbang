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

#include "command.h"
#include "gamestate.h"
#include "gameserver.h"
#include <QtDebug>

void Command::setInvalid()
{
    m_invalid = 1;
}

void Command::processToken(const QXmlStreamReader& xml)
{
    if (xml.isStartElement()) m_xmlDepth++;
    if (xml.isEndElement()) m_xmlDepth--;
}


class CommandQuery: public Command
{
public:
    CommandQuery(const QXmlStreamReader& xml):
        Command(xml)
    {
        if (xml.attributes().value("type") != "get") this->setInvalid();  // type argument MUST be get
    }



public:
    virtual void processToken(const QXmlStreamReader& xml)
    {
        Command::processToken(xml);
        if (m_xmlDepth == 1)
        {
            if (xml.isStartElement())
            {
                if (xml.name() == "gamelisting")
                {
                    m_queries.append(GAMELISTING);
                }
            }
        }
    }
    virtual void execute(QXmlStreamWriter& xmlOut)
    {
        xmlOut.writeStartElement("query");
        xmlOut.writeAttribute("type", "result");
        xmlOut.writeAttribute("id", m_xmlId);
        xmlOut.writeCharacters("");
        foreach(int query, m_queries)
        {
            switch(query)
            {
                case GAMELISTING:
                    xmlOut.writeStartElement("gamelisting");
                    foreach(GameState* game, GameServer::instance().getGames())
                    {
                        xmlOut.writeStartElement("game");
                        xmlOut.writeAttribute("id", QString::number(game->gameId()));
                        xmlOut.writeAttribute("name", game->name());
                        xmlOut.writeAttribute("description", game->description());
                        xmlOut.writeAttribute("creatorId", QString::number(game->creatorId()));
                        xmlOut.writeAttribute("minPlayers", QString::number(game->minPlayers()));
                        xmlOut.writeAttribute("maxPlayers", QString::number(game->maxPlayers()));
                        xmlOut.writeAttribute("maxObservers", QString::number(game->maxObservers()));
                        xmlOut.writeAttribute("playerPassword", QString::number(game->hasPlayerPassword()));
                        xmlOut.writeAttribute("observerPassword", QString::number(game->hasObserverPassword()));
                        xmlOut.writeAttribute("shufflePlayers", QString::number(game->hasShufflePlayers()));
                        xmlOut.writeEndElement();
                    }
                    xmlOut.writeEndElement();
                break;
            }

        }
        xmlOut.writeEndElement();
    }

private:
    enum QueryTypes { GAMELISTING };
    QVector<QueryTypes> m_queries;
};

class CommandInvalid: public Command
{
public:
    CommandInvalid(const QXmlStreamReader& xml):
        Command(xml)
    {
    }



public:
    virtual void processToken(const QXmlStreamReader&)
    {
    }

    virtual void execute(QXmlStreamWriter&)
    {
        /*        QTextStream out;
        out << "<query type=\"result\" id=\"" << m_xmlId << "\">\n";
        foreach(int query, m_queries)
        {
            switch(query)
            {
            case GAMELISTING:
                break;
            }

        }
        out << "</query>\n";
        return out.readAll();*/
    }
};



Command *Command::create(const QXmlStreamReader& xml)
{
    Q_ASSERT(xml.isStartElement());
    if (xml.name() == "query")
    {
        return new CommandQuery(xml);
    }
    return new CommandInvalid(xml);
}







