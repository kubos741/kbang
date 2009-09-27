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

class GameStructParser
{
public:
    static QString elementName(GameStruct::Type);

    static void writeServerInfo(QXmlStreamWriter*, const ServerInfoData&);
    static void readServerInfo(XmlNode*, ServerInfoData&);

    static void writePlayerInfo(QXmlStreamWriter*, const PlayerInfoData&);
    static void readPlayerInfo(XmlNode*, PlayerInfoData&);

    static void writeGameInfo(QXmlStreamWriter*, const GameInfoData&);
    static void readGameInfo(XmlNode*, GameInfoData&);

    static void writeCardSetInfo(QXmlStreamWriter*, const CardSetInfoData&);
    static void readCardSetInfo(XmlNode*, CardSetInfoData&);

    static void writeCreatePlayer(QXmlStreamWriter*, const CreatePlayerData&);
    static void readCreatePlayer(XmlNode*, CreatePlayerData&);

    static void writeCreateGame(QXmlStreamWriter*, const CreateGameData&);
    static void readCreateGame(XmlNode*, CreateGameData&);

    static void writeCard(QXmlStreamWriter*, const CardData&);
    static void readCard(XmlNode*, CardData&);

    static void writePublicPlayer(QXmlStreamWriter*, const PublicPlayerData&);
    static void readPublicPlayer(XmlNode*, PublicPlayerData&);

    static void writePrivatePlayer(QXmlStreamWriter*, const PrivatePlayerData&);
    static void readPrivatePlayer(XmlNode*, PrivatePlayerData&);

    static void writeGameContext(QXmlStreamWriter*, const GameContextData&);
    static void readGameContext(XmlNode*, GameContextData&);

    static void writeGameSync(QXmlStreamWriter*, const GameSyncData&);
    static void readGameSync(XmlNode*, GameSyncData&);
};

#endif // GAMESTRUCTPARSER_H
