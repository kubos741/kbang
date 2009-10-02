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
#include "cardwidgetsizemanager.h"
#include "cardbank.h"
#include "game.h"
#include "gameactionmanager.h"
#include "debug/debugblock.h"

using namespace client;


CardWidget::CardWidget(QWidget* parent):
        QLabel(parent),
        m_pocketType(POCKET_INVALID),
        m_ownerId(0),
        m_cardSizeRole(CARD_SIZE_NORMAL),
        m_hasHighlight(0)
{
    DEBUG_BLOCK;
    connect(&CardWidgetSizeManager::instance(), SIGNAL(cardSizeChanged()),
            this, SLOT(updatePixmap()));
}

CardWidget::~ CardWidget()
{
    DEBUG_BLOCK;
}

QPoint
CardWidget::center() const
{
    return QPoint((int)(QWidget::size().width() / 2),
                          (int)(QWidget::size().height() / 2));
}

void
CardWidget::clone(CardWidget* other)
{
    m_cardData = other->cardData();
}

void
CardWidget::clear()
{
    m_cardData = CardData();
}


void
CardWidget::setCardData(const CardData& cardData)
{
    m_cardData = cardData;
}

void
CardWidget::setPocketType(const PocketType& pocketType)
{
    m_pocketType = pocketType;
}

void
CardWidget::setOwnerId(PlayerId ownerId)
{
    m_ownerId = ownerId;
}

void
CardWidget::setCardSizeRole(CardSizeRole cardSizeRole)
{
    m_cardSizeRole = cardSizeRole;
}

void
CardWidget::setHighlight(bool hasHighlight)
{
    m_hasHighlight = hasHighlight;
    update();
}

void
CardWidget::unreveal()
{
    CardType type = m_cardData.type;
    m_cardData = CardData();
    m_cardData.type = type;
}

void
CardWidget::setPlayerRoleCard(PlayerRole playerRole)
{
    m_cardData = CardData();
    m_cardData.name = playerRoleToString(playerRole);
    if (playerRole == ROLE_UNKNOWN) {
        m_cardData.name = "";
    }
    m_cardData.type = CARDTYPE_ROLE;
    updatePixmap();
}

void
CardWidget::setCharacterCard(QString character)
{
    m_cardData = CardData();
    m_cardData.name = character;
    m_cardData.type = CARDTYPE_CHARACTER;
}

void
CardWidget::updatePixmap()
{
    QSize size = CardWidgetSizeManager::instance().cardSize(m_cardSizeRole);
    QPixmap pixmap;
    if (!m_cardData.name.isEmpty() || m_cardData.type != CARDTYPE_UNKNOWN) {
        const Card* card = CardBank::instance().card(m_cardData);
        if (card != 0) {
            pixmap = card->pixmap(m_cardData);
        }
    }

    if (pixmap.isNull()) {
        setPixmap(pixmap);
    } else {
        setPixmap(pixmap.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    setMinimumSize(size);
    setMaximumSize(size);
    resize(size);
}

/* virtual */ void
CardWidget::mousePressEvent(QMouseEvent* e)
{
    Game* game = Game::currentGame();
    if (!game) return;

    switch(e->button()) {
        case Qt::LeftButton: {
            bool handled = game->actionManager()->onCardClicked(this);
            if (!handled)
                QLabel::mousePressEvent(e);
            break;
        }
        case Qt::RightButton:
            game->actionManager()->onCardRightClicked(this);
            break;
        default:
            break;
    }
}

/* virtual */ void
CardWidget::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    if (m_hasHighlight) {
        QPainter painter(this);
        painter.fillRect(this->rect(), QBrush(QColor(0,0,0,128)));
    }
}

