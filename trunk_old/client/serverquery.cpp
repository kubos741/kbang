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
#include "serverquery.h"


#include "common.h" 
#include "xmlnode.h"
#include <QtXml>


QHash<QString, ServerQuery*> ServerQuery::sm_serverQueries;
QXmlStreamWriter  *ServerQuery::smp_xmlStreamWriter;


ServerQuery::ServerQuery(QObject *parent, const QString& elementName)
 : QObject(parent), m_elementName(elementName), m_posted(0)
{
    do
    {
        m_id = randomToken(10, 10);
    }
    while (sm_serverQueries.contains(m_id));
    sm_serverQueries[m_id] = this;
}


ServerQuery::~ServerQuery()
{
    if (!m_posted)
    {
        qCritical() << "ServerQuery instance created, but not posted!";
    }
}

void ServerQuery::post()
{
    smp_xmlStreamWriter->writeStartElement("query");
    smp_xmlStreamWriter->writeAttribute("id", m_id);
    smp_xmlStreamWriter->writeAttribute("type", "get");
    smp_xmlStreamWriter->writeStartElement(m_elementName);
    smp_xmlStreamWriter->writeAttributes(m_attributes);
    smp_xmlStreamWriter->writeEndElement();
    smp_xmlStreamWriter->writeEndElement();
    m_posted = 1;
}

void ServerQuery::addAttribute(const QString& name, const QString& value)
{
    m_attributes.append(name, value);
}

void ServerQuery::processResultQuery(XmlNode* node)
{
    QString id = node->attribute("id");
    if (sm_serverQueries[id])
    {
        sm_serverQueries[id]->emitResponseRecieved(node);
    }

}

void ServerQuery::emitResponseRecieved(XmlNode* node)
{
    emit responseRecieved(node);
}





