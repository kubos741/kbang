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

using namespace client;

QMap<QString, CardPointer> Card::sm_cards;

Card::Card(const QString& id, const QString& name, Type type, const QString& imageFileName):
    m_id(id), m_name(name), m_type(type), m_imageFileName(imageFileName)
{
    if (sm_cards.contains(id))
    {
        qWarning(qPrintable(QString("Unable to create a card. Card with id '%1' already exists.").arg(id)));
        return;
    }
    sm_cards[id] = this;
    m_image.load(m_imageFileName);
}

void Card::loadDefaultRuleset()
{
    new Card("sheriff",     "Sheriff",  CT_ROLE,    "");
    new Card("renegade",    "Renegade", CT_ROLE,    "");
    new Card("outlaw",      "Outlaw",   CT_ROLE,    "");
    new Card("deputy",      "Deputy",   CT_ROLE,    "");

    new Card("bang",        "Bang!",    CT_PLAYING, ":/cards/gfx/cards/bang.png");
    new Card("missed",      "Mancato",  CT_PLAYING, ":/cards/gfx/cards/missed.png");

    new Card("back-bullets","Bullets",  CT_BACK,    ":/cards/gfx/cards/back-bullets.png");
    new Card("back-bang",   "Back",     CT_BACK,    ":/cards/gfx/cards/back-bang.png");
}
