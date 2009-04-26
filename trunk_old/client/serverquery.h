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
#ifndef SERVERQUERY_H
#define SERVERQUERY_H

#include <QObject>
#include <QHash>
#include <QXmlStreamAttributes>
#include "serverconnection.h"

class XmlNode;

/**
 * 
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class ServerQuery : public QObject
{
Q_OBJECT
friend class ServerConnection;
private:
    ServerQuery(QObject *parent, const QString& elementName );
    ~ServerQuery();

public:
    
    void addAttribute(const QString& name, const QString& value);
    /**
     * You shouldn't keep pointer after calling post(). As soon as response from
     * server is gotten, signal is emited and instance is destroyed.
     */
    void post();

signals:
    void responseRecieved(XmlNode* node);


private:
    static QXmlStreamWriter  *smp_xmlStreamWriter;
    static QHash<QString, ServerQuery*> sm_serverQueries;
    static QString sm_lock;
    
    
    
    QString                         m_elementName;
    QXmlStreamAttributes            m_attributes;
    QString                         m_id;
    bool                            m_posted;
    
    
    
private:
    inline void emitResponseRecieved(XmlNode* node);
    static void processResultQuery(XmlNode* node);

};

#endif
