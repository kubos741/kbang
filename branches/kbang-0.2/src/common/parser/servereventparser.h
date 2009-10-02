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

#ifndef SERVEREVENTPARSER_H
#define SERVEREVENTPARSER_H

#include "serverevents.h"
#include "xmlnode.h"

#include <QXmlStreamWriter>

/**
 * The ServerEventParser class provides static methods for writing ServerEvents into
 * XML streams and reading ServerEvents from XML streams.
 * @author MacJariel
 */
class ServerEventParser
{
public:
    /**
     * Writes ServerEvent into XML stream using QXmlStreamWriter.
     */
    static void write(QXmlStreamWriter*, ServerEventDataPtr);
    /**
     * Reads the ServerEvent from XML stream and returns it.
     */
    static ServerEventDataPtr read(XmlNode*);

private:
    static void writeEnterGame(QXmlStreamWriter*, EnterGameEventDataPtr);
    static ServerEventDataPtr readEnterGame(XmlNode*);
    static void writeExitGame(QXmlStreamWriter*, ExitGameEventDataPtr);
    static ServerEventDataPtr readExitGame(XmlNode*);
    static void writeCreatePlayer(QXmlStreamWriter*, CreatePlayerEventDataPtr);
    static ServerEventDataPtr readCreatePlayer(XmlNode*);
    static void writeRemovePlayer(QXmlStreamWriter*, RemovePlayerEventDataPtr);
    static ServerEventDataPtr readRemovePlayer(XmlNode*);
    static void writeChatMessage(QXmlStreamWriter*, ChatMessageEventDataPtr);
    static ServerEventDataPtr readChatMessage(XmlNode*);
    static void writeGameUpdate(QXmlStreamWriter*, GameUpdateEventDataPtr);
    static ServerEventDataPtr readGameUpdate(XmlNode*);
};


#endif // SERVEREVENTPARSER_H
