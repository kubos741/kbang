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

#include "card.h"               // Card header file
#include "cardbank.h"           // To obtain suit and rank QPixmaps
#include "gamestructs.h"        // CardData

#include <QPainter>             // Runtime suit and rank painting

using namespace client;

Card::Card(CardBank* parent, const QString& name, CardType type,
           const QString& cardSetName):
        QObject(parent),
        m_cardBank(parent),
        m_name(name),
        m_type(type),
        m_cardSetName(cardSetName)
{
}

void
Card::addGraphics(const QString& gfx, const QString& suitString,
                  const QString& rankString, bool renderSigns)
{
    Card::Graphics graphics;
    if (!graphics.image.load(gfx)) {
        qWarning(qPrintable(QString("Cannot load image: %1").arg(gfx)));
        return;
    }
    if (m_type == CARDTYPE_PLAYING) {
        // Only playing cards have suits and ranks
        
        if (!suitString.isEmpty()) {
            graphics.suit = stringToCardSuit(suitString);
        }

        if (!rankString.isEmpty()) {
            QStringList sl = rankString.split("-");
            graphics.rankFrom = stringToCardRank(sl[0]);
            if (sl.size() == 1) {
                graphics.rankTo = graphics.rankFrom;
            } else {
                graphics.rankTo = stringToCardRank(sl[1]);
            }
        }
        graphics.renderSigns = renderSigns;
    }
    m_graphics.append(graphics);
}

QPixmap
Card::pixmap(const CardData& cardData) const
{
    if (m_graphics.size() == 0) {
        qCritical(qPrintable(QString("Card '%1' has no graphics.").arg(m_name)));
        return QPixmap();
    }

    QPixmap result;
    bool renderSigns = 0;

    if (m_graphics.size() == 1) {
        result = m_graphics.first().image;
        renderSigns = m_graphics.first().renderSigns;
    } else {
        CardSuit suit = cardData.suit;
        CardRank rank = cardData.rank;

        foreach (Graphics g, m_graphics) {
            if ((g.suit == SUIT_INVALID || g.suit == suit) &&
                g.rankFrom <= rank && g.rankTo >= rank) {
                result = g.image;
                renderSigns = g.renderSigns;
                break;
            }
        }

        if (result.isNull()) {
            qWarning("No graphics for card %s found.", qPrintable(m_name));
            return result;
        }
    }

if (renderSigns) {
        QPixmap rankImage = CardBank::instance().rank(m_cardSetName, cardData.rank);
        QPixmap suitImage = CardBank::instance().suit(m_cardSetName, cardData.suit);
        QPainter painter(&result);
        QPoint point = CardBank::instance().renderSignsPosition(m_cardSetName);
        painter.drawPixmap(point, rankImage);
        point += QPoint(rankImage.width(), 0);
        painter.drawPixmap(point, suitImage);
    }
    return result;
}
