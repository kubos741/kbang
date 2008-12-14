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

#include <QtDebug>

#include "card.h"

QMap<QString, CardPointer> Card::sm_cards;

Card::Card(const QString& id, const QString& name, Type type, const QString& imageSmall, const QString& image):
    m_id(id), m_name(name), m_type(type), m_imageSmallFile(imageSmall), m_imageFile(image)
{
    if (sm_cards.contains(id))
    {
        qWarning() << "Cannot create a card with already used id.";
        return;
    }
    sm_cards[id] = this;
}

QPixmap Card::imageSmall()
{
    if (m_imageSmall.isNull())
    {
        m_imageSmall.load(m_imageSmallFile); // flags?
    }
    return m_imageSmall;
}

QPixmap Card::image()
{
    if (m_image.isNull())
    {
        m_image.load(m_imageFile);
    }
    return m_image;
}

void Card::loadDefaultRuleset()
{
    new Card("sheriff",  "Sheriff",  CT_ROLE, "", "");
    new Card("renegade", "Renegade", CT_ROLE, "", "");
    new Card("bandita",  "Bandita",  CT_ROLE, "", "");
    new Card("deputy",   "Deputy",   CT_ROLE, "", "");
    
    new Card("bang", "Bang!", CT_PLAYING, "", "");
    new Card("mancato", "Vedle!", CT_PLAYING, "", "");
}

const CardPointer Card::findCard(const QString& id)
{
    if (!sm_cards.contains(id)) return 0;
    return sm_cards[id];
}
