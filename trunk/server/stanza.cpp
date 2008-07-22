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
#include "stanza.h"
#include "stanzaquery.h"
#include "stanzaaction.h"
#include "game.h"
#include "gameserver.h"
#include <QXmlAttributes>



Stanza::Stanza(const QXmlStreamReader& xmlIn):
    m_state(STATE_VOID),
    m_xmlDepth(0),
    m_complete(0)
{
    Q_ASSERT(xmlIn.isStartElement());
    m_id = xmlIn.attributes().value("id").toString();
}

void Stanza::processToken(const QXmlStreamReader& xmlIn)
{
    Q_ASSERT(!m_complete);
    if (xmlIn.isStartElement()) m_xmlDepth++;
    if (xmlIn.isEndElement()) m_xmlDepth--;
    if (xmlIn.isEndElement() && m_xmlDepth == -1)
    {
        m_complete = 1;
    }
}

void Stanza::execute(QXmlStreamWriter&)
{
    Q_ASSERT(m_complete);
}

void Stanza::writeErrorElement(QXmlStreamWriter& xmlOut)
{
    switch(m_state)
    {
        case STATE_INVALID_TYPE:   xmlOut.writeEmptyElement("invalid-type");   break;
        case STATE_BAD_QUERY:      xmlOut.writeEmptyElement("bad-query");      break;
        case STATE_NOT_EXIST:      xmlOut.writeEmptyElement("not-exist");      break;
        case STATE_NOT_AVAILABLE:  xmlOut.writeEmptyElement("not-available");  break;
        case STATE_NOT_COMPLETE:   xmlOut.writeEmptyElement("not-complete");   break;
        case STATE_ACCESS_DENIED:  xmlOut.writeEmptyElement("access-denied");  break;
        default:                   NOT_REACHED();                              break;
    }
}


inline void Stanza::setClient(Client* client)
{
    mp_client = client;
}

Stanza* Stanza::construct(Client* client, const QXmlStreamReader& xmlIn)
{
    Q_ASSERT(xmlIn.isStartElement());
    Stanza* stanza = 0;
    if (xmlIn.name() == "query")
    {
        stanza = new StanzaQuery(xmlIn);
    }
    else if (xmlIn.name() == "action")
    {
        stanza = new StanzaAction(xmlIn);
    }
    else
    {
        stanza = new Stanza(xmlIn);
    }
    Q_ASSERT(stanza);
    stanza->setClient(client);
    return stanza;
}
