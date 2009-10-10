/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
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

#ifndef GAMESTRUCTPARSER_H
#define GAMESTRUCTPARSER_H

/**
 * @file gamestructparser.h
 * This file contains code to read and write common game structures
 * (GameStruct derivates) from or to network protocol.
 */

#include "gamestructs.h"
#include "xmlnode.h"
#include <QXmlStreamWriter>

/*[[[cog
import cog
from gamestructdefs import *
]]]
[[[end]]]*/

class GameStructParser
{
public:
    static void write(QXmlStreamWriter*, const GameStruct&);
    static GameStruct* read(XmlNode*);

    /*[[[cog
    for s in GameStructs:
        cog.outl("static void write(QXmlStreamWriter*, const %(structName)s&, const char* elemName = 0);" % s)
        cog.outl("static void read(XmlNode*, %(structName)s&);" % s)
        cog.outl("");
    ]]]*/
    static void write(QXmlStreamWriter*, const ServerInfoData&, const char* elemName = 0);
    static void read(XmlNode*, ServerInfoData&);

    static void write(QXmlStreamWriter*, const PlayerInfoData&, const char* elemName = 0);
    static void read(XmlNode*, PlayerInfoData&);

    static void write(QXmlStreamWriter*, const PlayerInfoListData&, const char* elemName = 0);
    static void read(XmlNode*, PlayerInfoListData&);

    static void write(QXmlStreamWriter*, const GameInfoData&, const char* elemName = 0);
    static void read(XmlNode*, GameInfoData&);

    static void write(QXmlStreamWriter*, const GameInfoListData&, const char* elemName = 0);
    static void read(XmlNode*, GameInfoListData&);

    static void write(QXmlStreamWriter*, const UrlListData&, const char* elemName = 0);
    static void read(XmlNode*, UrlListData&);

    static void write(QXmlStreamWriter*, const CardSetInfoData&, const char* elemName = 0);
    static void read(XmlNode*, CardSetInfoData&);

    static void write(QXmlStreamWriter*, const CardSetInfoListData&, const char* elemName = 0);
    static void read(XmlNode*, CardSetInfoListData&);

    static void write(QXmlStreamWriter*, const CreatePlayerData&, const char* elemName = 0);
    static void read(XmlNode*, CreatePlayerData&);

    static void write(QXmlStreamWriter*, const CreateGameData&, const char* elemName = 0);
    static void read(XmlNode*, CreateGameData&);

    static void write(QXmlStreamWriter*, const CardData&, const char* elemName = 0);
    static void read(XmlNode*, CardData&);

    static void write(QXmlStreamWriter*, const CardListData&, const char* elemName = 0);
    static void read(XmlNode*, CardListData&);

    static void write(QXmlStreamWriter*, const PublicPlayerData&, const char* elemName = 0);
    static void read(XmlNode*, PublicPlayerData&);

    static void write(QXmlStreamWriter*, const PublicPlayerListData&, const char* elemName = 0);
    static void read(XmlNode*, PublicPlayerListData&);

    static void write(QXmlStreamWriter*, const PrivatePlayerData&, const char* elemName = 0);
    static void read(XmlNode*, PrivatePlayerData&);

    static void write(QXmlStreamWriter*, const GameContextData&, const char* elemName = 0);
    static void read(XmlNode*, GameContextData&);

    static void write(QXmlStreamWriter*, const GameSyncData&, const char* elemName = 0);
    static void read(XmlNode*, GameSyncData&);

    static void write(QXmlStreamWriter*, const CardIdListData&, const char* elemName = 0);
    static void read(XmlNode*, CardIdListData&);

    //[[[end]]]

    static void write(QXmlStreamWriter*, const QByteArray&, const char* elemName);
    static void read(XmlNode*, QByteArray&);

    static void write(QXmlStreamWriter*, const QMap<QString, QVariant>&, const char* elemName);
    static void read(XmlNode*, QMap<QString, QVariant>&);
};

#endif // GAMESTRUCTPARSER_H
