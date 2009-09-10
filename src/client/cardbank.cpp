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

#include <QDomElement>
#include "cardbank.h"
#include "util.h"           // stringToBool(QString)
#include "gamestructs.h"    // CardData

using namespace client;

CardBank::CardBank(QObject* parent):
        QObject(parent)
{
}

/* virtual */
CardBank::~CardBank()
{
}

void
CardBank::loadCardSet(const CardSetInfo& cardSetInfo)
{
    if (!cardSetInfo.isLocal()) {
        qCritical("Cannot load remote card set.");
        return;
    }

    QFile cardsetFile(cardSetInfo.cardSetFileName());
    QDomDocument doc("cardset");

    if (!cardsetFile.exists() || !cardsetFile.open(QIODevice::ReadOnly) ||
        !doc.setContent(&cardsetFile)) {
        qWarning("Cannot load card set file '%s'.",
                 qPrintable(cardSetInfo.cardSetFileName()));
        return;
    }
    cardsetFile.close();

    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            if (e.tagName() == "card") {
                addCard(cardSetInfo, e);
            }
        }
        n = n.nextSibling();
    }

    m_name = docElem.attribute("name");
    m_slot = docElem.attribute("slot");
    m_locale = QLocale(docElem.attribute("locale"));

    CardSetManager::instance().addKnownSlot(m_slot);

//    qDebug() << m_name << m_slot << m_locale.name();
}

const Card*
CardBank::card(const CardData& cardData)
{
    QString key = cardData.name;
    if (key.isEmpty()) {
        switch(cardData.type) {
            case CARDTYPE_PLAYING:   key = "back-playing";   break;
            case CARDTYPE_ROLE:      key = "back-role";      break;
            case CARDTYPE_CHARACTER: key = "back-character"; break;
            case CARDTYPE_UNKNOWN:                           break;
        }
    }
    return m_cardStorage.value(cardData.name, 0);
}

void
CardBank::addCard(const CardSetInfo& cardSetInfo, const QDomElement& e)
{
    CardName name = e.attribute("name");
    CardType type = stringToCardType(e.attribute("type"));
    QString gfx = e.attribute("gfx");
    QString suitString = e.attribute("suit");
    QString rankString = e.attribute("rank");
    QString renderSignsString = e.attribute("render-signs");

    bool renderSigns;
    if (renderSignsString.isEmpty()) {
        renderSigns = cardSetInfo.renderSigns();
    } else {
        renderSigns = stringToBool(renderSignsString);
    }

    Card* card = 0;
    if (m_cardStorage.contains(name)) {
        card = m_cardStorage[name];
    } else {
        card = new Card(this, name, type, cardSetName);
    }
    if (card->cardSetName() != cardSetInfo.name()) {
        qCritical("CardSet collision found. Trying to add %s from %s, but this"
                  "card is already added from %s", qPrintable(name),
                  qPrintable(cardSetInfo.name()), qPrintable(card->cardSetName()));
        return;
    }
    card->addGraphics(gfx, suit, rank, renderSigns);
}
