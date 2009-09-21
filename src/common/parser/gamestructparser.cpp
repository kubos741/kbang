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

#include "gamestructparser.h"
#include "xmlnode.h"
#include "util.h"

void GameStructParser::writeCard(QXmlStreamWriter* writer, const CardData& card)
{
    writer->writeAttribute("id",        intToString(card.id));
    writer->writeAttribute("name",      card.name);
    writer->writeAttribute("type",      cardTypeToString(card.type));
    writer->writeAttribute("suit",      cardSuitToString(card.suit));
    writer->writeAttribute("rank",      cardRankToString(card.rank));
    writer->writeAttribute("is-ready",  boolToString(card.isReady));
}

void GameStructParser::readCard(XmlNode* node, CardData& res)
{
    res.id          = stringToInt(node->attribute("id"));
    res.name        = node->attribute("name");
    res.type        = stringToCardType(node->attribute("type"));
    res.suit        = stringToCardSuit(node->attribute("suit"));
    res.rank        = stringToCardRank(node->attribute("rank"));
    res.isReady     = stringToBool(node->attribute("is-ready"));
}

CardData GameStructParser::readCard(XmlNode* node)
{
    CardData res;
    readCard(node, res);
    return res;
}

void GameStructParser::writePublicPlayer(QXmlStreamWriter*, const PublicPlayerData&)
{
}

void GameStructParser::readPublicPlayer(XmlNode*, PublicPlayerData&)
{
}

PublicPlayerData GameStructParser::readPublicPlayer(XmlNode*)
{
}

void GameStructParser::writePrivatePlayer(QXmlStreamWriter*, const PrivatePlayerData&)
{
}

void GameStructParser::readPrivatePlayer(XmlNode*, PrivatePlayerData&)
{
}

PrivatePlayerData GameStructParser::readPrivatePlayer(XmlNode*)
{
}

