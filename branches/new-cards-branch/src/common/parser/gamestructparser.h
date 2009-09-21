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

#include "gamestructs.h"

class GameStructParser
{
public:
    static void writeCard(QXmlStreamWriter*, const CardData&);
    static void readCard(XmlNode*, CardData&);
    static CardData readCard(XmlNode*);
    static void writePublicPlayer(QXmlStreamWriter*, const PublicPlayerData&);
    static void readPublicPlayer(XmlNode*, PublicPlayerData&);
    static PublicPlayerData readPublicPlayer(XmlNode*);
    static void writePrivatePlayer(QXmlStreamWriter*, const PrivatePlayerData&);
    static void readPrivatePlayer(XmlNode*, PrivatePlayerData&);
    static PrivatePlayerData readPrivatePlayer(XmlNode*);
};

#endif // GAMESTRUCTPARSER_H
