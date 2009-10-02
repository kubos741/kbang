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

#ifndef GAMEEVENTPARSER_H
#define GAMEEVENTPARSER_H

#include "gameevents.h"
#include "xmlnode.h"

#include <QXmlStreamWriter>
#include <QSharedPointer>

/**
 * The GameEventParser class provides static methods for writing GameEvents into
 * XML streams and reading GameEvents from XML streams.
 * @author MacJariel
 */
class GameEventParser
{
public:
    /**
     * Writes GameEventData into XML stream using QXmlStreamWriter.
     */
    static void write(QXmlStreamWriter*, GameEventDataPtr);
    /**
     * Reads the GameEventData from XML stream and returns it.
     */
    static GameEventDataPtr read(XmlNode*);

private:
    static void writeCmdData(QXmlStreamWriter*, GameEventCmdDataPtr);
    static void writeCardMovementCmdData(QXmlStreamWriter*, CardMovementCmdDataPtr);
    static void writeUpdatePlayerCmdData(QXmlStreamWriter*, UpdatePlayerCmdDataPtr);
    static void writeGameContextCmdData(QXmlStreamWriter*, GameContextCmdDataPtr);
    static void writeSetPlayersCmdData(QXmlStreamWriter*, SetPlayersCmdDataPtr);
    static GameEventCmdDataPtr readCmdData(XmlNode*);
    static GameEventCmdDataPtr readCardMovementCmdData(XmlNode*);
    static GameEventCmdDataPtr readUpdatePlayerCmdData(XmlNode*);
    static GameEventCmdDataPtr readGameContextCmdData(XmlNode*);
    static GameEventCmdDataPtr readSetPlayersCmdData(XmlNode*);
};

#endif // GAMEEVENTPARSER_H
