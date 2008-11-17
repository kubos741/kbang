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
#ifndef PARSERSTRUCTS_H
#define PARSERSTRUCTS_H

#include <QString>
#include <QList>

class XmlNode;
class QXmlStreamWriter;

struct StructServerInfo
{
    QString name, description;
    void read(XmlNode*);
    void write(QXmlStreamWriter*) const;
    static QString elementName;
};


struct StructClient
{
    int id;
    QString name;
};

struct StructPlayer
{
    int id;
    QString name, password;
    void read(XmlNode*);
    void write(QXmlStreamWriter*, bool writePassword = 0) const;
    static QString elementName;
};

typedef QList<StructPlayer> StructPlayerList;

struct StructGame
{
    int id, creatorId;
    QString name, description;
    int minPlayers, maxPlayers, maxSpectators;
    QString playerPassword, spectatorPassword;
    bool hasPlayerPassword, hasSpectatorPassword;
    bool flagShufflePlayers;
    void read(XmlNode*);
    void write(QXmlStreamWriter*, const StructPlayerList* playerlist = 0) const;
    static QString elementName;
};

typedef QList<StructGame> StructGameList;


#endif
