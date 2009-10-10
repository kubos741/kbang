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
#include "cardsetmanager.h"
#include "util.h"           // stringToBool(QString)
#include "gamestructs.h"    // CardData
#include "debug/debugblock.h"

using namespace client;

CardBank::CardBank():
        QObject(0)
{
    /// @attention Loads all available CardSets. This should change in the future.
    foreach (const CardSetInfo& cardSetInfo,
             CardSetManager::instance().localCardSets()) {
        loadCardSet(cardSetInfo);
    }
}

/* virtual */
CardBank::~CardBank()
{
}

void
CardBank::loadCardSet(const CardSetInfo& cardSetInfo)
{
    QFile cardsetFile(cardSetInfo.cardSetFilePath());
    QDomDocument doc("cardset");

    if (!cardsetFile.exists() || !cardsetFile.open(QIODevice::ReadOnly) ||
        !doc.setContent(&cardsetFile)) {
        qWarning("Cannot load card set file '%s'.",
                 qPrintable(cardSetInfo.cardSetFilePath()));
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
            } else if (e.tagName() == "rank") {
                CardRank cardRank = stringToCardRank(e.attribute("value"));
                QString gfx = cardSetInfo.dir().absoluteFilePath(e.attribute("gfx"));
                if (!m_signStorage[cardSetInfo.id()].ranks[cardRank].load(gfx)) {
                    qWarning(qPrintable(QString("Cannot load image: %1").arg(gfx)));
                }
            } else if (e.tagName() == "suit") {
                CardSuit cardSuit = stringToCardSuit(e.attribute("value"));
                QString gfx = cardSetInfo.dir().absoluteFilePath(e.attribute("gfx"));
                if (!m_signStorage[cardSetInfo.id()].suits[cardSuit].load(gfx)) {
                    qWarning(qPrintable(QString("Cannot load image: %1").arg(gfx)));
                }
            }
        }
        m_signStorage[cardSetInfo.id()].renderSignsPosition =
                cardSetInfo.renderSignsPosition();
        n = n.nextSibling();
    }
}

const Card*
CardBank::card(const CardData& cardData) const
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
    return m_cardStorage.value(key, 0);
}

QPixmap
CardBank::rank(const QString& cardSetName, CardRank cardRank) const
{
    return m_signStorage[cardSetName].ranks[cardRank];
}

QPixmap
CardBank::suit(const QString& cardSetName, CardSuit cardSuit) const
{
    return m_signStorage[cardSetName].suits[cardSuit];
}

QPoint
CardBank::renderSignsPosition(const QString& cardSetName) const
{
    return m_signStorage[cardSetName].renderSignsPosition;
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
        card = new Card(this, name, type, cardSetInfo.id());
        m_cardStorage[name] = card;
    }
    if (card->cardSetName() != cardSetInfo.id()) {
        qCritical("CardSet collision found. Trying to add %s from %s, but this"
                  "card is already added from %s", qPrintable(name),
                  qPrintable(cardSetInfo.id()), qPrintable(card->cardSetName()));
        return;
    }
    card->addGraphics(cardSetInfo.dir().absoluteFilePath(gfx), suitString, rankString, renderSigns);
}
