/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
 *   echo "dmailet@gbalt.dob" | tr "edibmlt" "ecrmjil"                   *
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
#include <QtCore>
#include <QtDebug>
#include <QPainter>
#include <QMouseEvent>


#include "card.h"
#include "cardwidget.h"
#include "cardactionswidget.h"
#include "gameobjectclickhandler.h"

using namespace client;


//const QSize CardWidget::sm_qsizeSmall(48, 78 );
//const QSize CardWidget::sm_qsizeSmall(50, 80);
const QSize CardWidget::sm_qsizeSmall(55, 85);
const QSize CardWidget::sm_qsizeNormal(80, 124);
const QSize CardWidget::sm_qsizeBig(200, 310);

//const QSize  margins(10,10);
//const QPoint padding(5,5);

CardWidget::CardWidget(QWidget* parent, Card::Type cardType):
        QLabel(parent),
        m_cardType(cardType),
        m_pocket(POCKET_INVALID),
        m_ownerId(0),
        m_playerRole(ROLE_UNKNOWN),
        m_characterType(CHARACTER_UNKNOWN),
        m_qsize(sm_qsizeSmall),
        m_shadowMode(0),
        m_hasHighlight(0),
        mp_gameObjectClickHandler(0)
{
    show();
}

CardWidget::~ CardWidget()
{
}

void CardWidget::setGameObjectClickHandler(GameObjectClickHandler* gameObjectClickHandler)
{
    mp_gameObjectClickHandler = gameObjectClickHandler;
}

void CardWidget::setType(Card::Type cardType)
{
    m_cardType = cardType;
}

void CardWidget::setCardData(const CardData& cardData)
{
    m_cardData = cardData;
}

void CardWidget::setSize(Size size)
{
    m_size = size;
    m_qsize = qSize(size);
}

void CardWidget::validate()
{
    const Card* card;
    switch(m_cardType) {
        case Card::Playing:
        card = Card::findPlayingCard(m_cardData.type);
        break;
    case Card::Role:
        card = Card::findRoleCard(m_playerRole);
        break;
    case Card::Character:
        card = Card::findCharacterCard(m_characterType);
        break;
    }

    if (card == 0) {
        qWarning("Cannot look-up the card!");
        return;
    }

    if (card->image().isNull()) {
        qWarning(qPrintable(QString("Card '%1' has null pixmap.").arg(card->name())));
    }

    setPixmap(card->image().scaled(m_qsize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setMinimumSize(m_qsize);
    setMaximumSize(m_qsize);
    resize(m_qsize);
}

void CardWidget::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    if (type() == Card::Playing && cardData().type != CARD_UNKNOWN) {
        QPoint posRank, posSuit;
        QColor suitColor;
        QFont font;
        QPainter painter(this);

        if (size() == SIZE_SMALL) {
            posRank = QPoint(6, 81);
            font = QFont("Verdana", 7);
        } else {
            posRank = QPoint(8, 118);
            font = QFont("Verdana", 10);
        }
        QString textRank;
        QChar   textSuit;
        if (cardData().rank < 9) {
            textRank = QString::number(cardData().rank);
        } else if (cardData().rank == 10) {
            textRank = "10";
        } else if (cardData().rank == 11) {
            textRank = "J";
        } else if (cardData().rank == 12) {
            textRank = "Q";
        } else if (cardData().rank == 13) {
            textRank = "K";
        } else {
            textRank = "A";
        }
        switch (cardData().suit) {
            case SUIT_CLUBS:
                textSuit = 0x2663;
                suitColor = Qt::black;
                break;
            case SUIT_DIAMONDS:
                textSuit = 0x2666;
                suitColor = Qt::red;
                break;
            case SUIT_HEARTS:
                textSuit = 0x2665;
                suitColor = Qt::red;
                break;
            case SUIT_SPADES:
                textSuit = 0x2660;
                suitColor = Qt::black;
                break;
        }

        QPainterPath path1;
        QPainterPath path2;
        //timesFont.setStyleStrategy(QFont::ForceOutline);
        path1.addText(posRank, font, textRank);
        posSuit = posRank + QPoint(font.pointSize() * textRank.size(), 0);
        path2.addText(posSuit, font, textSuit);

        painter.setRenderHint(QPainter::Antialiasing);

        painter.setPen(QPen(Qt::white, 2, Qt::SolidLine, Qt::RoundCap,
                         Qt::RoundJoin));

        painter.setBrush(Qt::white);
        painter.drawPath(path1);
        painter.drawPath(path2);

        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap,
                         Qt::RoundJoin));
        painter.drawPath(path1);
        painter.setPen(QPen(suitColor, 1, Qt::SolidLine, Qt::RoundCap,
                         Qt::RoundJoin));
        painter.setBrush(suitColor);
        painter.drawPath(path2);

    }

    if (m_hasHighlight) {
        QPainter painter(this);
        painter.fillRect(this->rect(), QBrush(QColor(0,0,0,128)));
    }
}





QSize CardWidget::qSize(Size size)
{
    switch(size) {
        case SIZE_SMALL:  return sm_qsizeSmall;  break;
        case SIZE_NORMAL: return sm_qsizeNormal; break;
        case SIZE_BIG:    return sm_qsizeBig;    break;
    }
    Q_ASSERT(0);
    return QSize(); // avoid warning
}




void CardWidget::setPocketType(const PocketType& pocket)
{
    m_pocket = pocket;
}

void CardWidget::setOwnerId(int ownerId)
{
    m_ownerId = ownerId;
}

void CardWidget::setPlayerRole(PlayerRole playerRole)
{
    m_playerRole = playerRole;
}

void CardWidget::setCharacterType(CharacterType characterType)
{
    m_characterType = characterType;
}

void CardWidget::setHighlight(bool hasHighlight)
{
    m_hasHighlight = hasHighlight;
    update();
}

void CardWidget::mousePressEvent(QMouseEvent*)
{
    if (mp_gameObjectClickHandler)
        mp_gameObjectClickHandler->onCardClicked(this);
}


