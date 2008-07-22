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
#include "common.h"
#include "gameserver.h"
#include "game.h"
#include "client.h"
#include "stanzaquery.h"


QHash<QString, StanzaQuery::ExecuteMethod> StanzaQuery::sm_methods;
bool StanzaQuery::sm_initialized = 0;


StanzaQuery::StanzaQuery(const QXmlStreamReader& xmlIn)
 : Stanza(xmlIn)
{
    if (!sm_initialized) StanzaQuery::initializeMethods();

    if (m_id.isEmpty())                            m_state = STATE_MISSING_ID;
    if (xmlIn.attributes().value("type") != "get") m_state = STATE_INVALID_TYPE;
}

void StanzaQuery::processToken(const QXmlStreamReader& xmlIn)
{
    Stanza::processToken(xmlIn);
    if (m_state != STATE_OK && m_state != STATE_VOID) return;
    if (xmlIn.isEndElement()) return;
    if ((m_xmlDepth == 1) && xmlIn.isStartElement())
    {
        qDebug() << "Here: " << xmlIn.name().toString();
        if (!m_elementName.isNull() || !sm_methods.contains(xmlIn.name().toString()))
        {
            m_state = STATE_BAD_QUERY;
            return;
        }
        m_elementName = xmlIn.name().toString();
        m_attributes  = xmlIn.attributes();
        m_state       = STATE_OK;
    }
    else
    {
        m_state = STATE_BAD_QUERY;
        return;
    }
}

void StanzaQuery::execute(QXmlStreamWriter& xmlOut)
{
    Stanza::execute(xmlOut);
    if (m_state == STATE_VOID) m_state = STATE_BAD_QUERY;
    if (m_state != STATE_OK)
    {
        writeStanzaStartElement(xmlOut);
        writeErrorElement(xmlOut);
        writeStanzaEndElement(xmlOut);
    }
    else
    {
        Q_ASSERT(sm_methods.contains(m_elementName));
        CALL_MEMBER_FN(*this,sm_methods[m_elementName])(xmlOut);
    }
}


void StanzaQuery::writeStanzaStartElement(QXmlStreamWriter& xmlOut)
{
        xmlOut.writeStartElement("query");
        xmlOut.writeAttribute("type", (m_state == STATE_OK) ? "result" : "error");
        if (!m_id.isEmpty()) xmlOut.writeAttribute("id", m_id);
}


void StanzaQuery::writeStanzaEndElement(QXmlStreamWriter& xmlOut)
{
    xmlOut.writeEndElement();
}

void StanzaQuery::initializeMethods()
{
    sm_methods["gamelist"]   = &StanzaQuery::getGameList;
    sm_methods["game"]       = &StanzaQuery::getGame;
    sm_methods["clientlist"] = &StanzaQuery::getClientList;
    sm_methods["serverinfo"] = &StanzaQuery::getServerInfo;
    sm_initialized = 1;
}



void StanzaQuery::getGameList(QXmlStreamWriter& xmlOut)
{
    writeStanzaStartElement(xmlOut);
    xmlOut.writeStartElement("gamelist");
    foreach(Game* game, GameServer::instance().gameList())
    {
        game->writeXml(xmlOut);
    }
    xmlOut.writeEndElement();
    writeStanzaEndElement(xmlOut);
}

void StanzaQuery::getGame(QXmlStreamWriter& xmlOut)
{
    int gameId = m_attributes.value("id").toString().toInt();
    Game* game = 0;
    if (gameId)
    {
        game = GameServer::instance().game(gameId);
    }
    if (!game) m_state = STATE_NOT_EXIST;
    writeStanzaStartElement(xmlOut);
    if (game) game->writeXml(xmlOut, 1);
    else writeErrorElement(xmlOut);
    writeStanzaEndElement(xmlOut);
}

void StanzaQuery::getClientList(QXmlStreamWriter& xmlOut)
{
    writeStanzaStartElement(xmlOut);
    xmlOut.writeStartElement("clientlist");
    foreach(Client* client, GameServer::instance().clientList())
    {
        client->writeXml(xmlOut);
    }
    xmlOut.writeEndElement();
    writeStanzaEndElement(xmlOut);
}

void StanzaQuery::getServerInfo(QXmlStreamWriter& xmlOut)
{
    writeStanzaStartElement(xmlOut);
    GameServer::instance().writeXml(xmlOut);
    writeStanzaEndElement(xmlOut);
}


StanzaQuery::~StanzaQuery()
{
}




