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
#include "opponentwidget.h"
#include "cardwidget.h"
#include "cardlist.h"

#include <QMovie>
#include <QtDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>

#include "cardpilewidget.h"
#include "cardwidgetfactory.h"

using namespace client;

OpponentWidget::OpponentWidget(QWidget *parent):
        PlayerWidget(parent),
        mp_sheriffBadge(0),
        mp_disconnectIcon(0),
        m_isDead(0),
        m_role(ROLE_UNKNOWN),
        mp_roleCard(0)

{
    setupUi(this);
    setContentsMargins(5, 5, 5, 5);

    mp_hand->setCardSize(CardWidget::SIZE_SMALL);
    mp_hand->setPocketType(POCKET_HAND);
    mp_hand->setOwnerId(id());
    mp_table->setCardSize(CardWidget::SIZE_SMALL);
    mp_table->setPocketType(POCKET_TABLE);
    mp_table->setOwnerId(id());

    updateWidgets();
}

OpponentWidget::~OpponentWidget()
{
}


void OpponentWidget::init(GameObjectClickHandler* gameObjectClickHandler, CardWidgetFactory* cardWidgetFactory)
{
    PlayerWidget::init(gameObjectClickHandler, cardWidgetFactory);
    mp_characterWidget->init(mp_cardWidgetFactory);
    m_isDead = 0;
    m_hasController = 1;
}

void OpponentWidget::setFromPublicData(const PublicPlayerData& publicPlayerData)
{
    setId(publicPlayerData.id);
    setName(publicPlayerData.name);
    mp_characterWidget->setCharacter(publicPlayerData.character);
    mp_characterWidget->setLifePoints(publicPlayerData.lifePoints);
    mp_characterWidget->setOwnerId(id());
    setSheriff(publicPlayerData.isSheriff);




    if (!publicPlayerData.avatar.isNull()) {
        m_avatar = QPixmap::fromImage(publicPlayerData.avatar).scaled(mp_labelAvatar->size(),
                                                                    Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    setAvatarPixmap();

    m_hasController = publicPlayerData.hasController;

    mp_hand->setOwnerId(id());
    mp_table->setOwnerId(id());


    mp_hand->clear();
    for(int i = 0; i < publicPlayerData.handSize; ++i) {
        CardWidget* card = mp_cardWidgetFactory->createPlayingCard(this);
        card->validate();
        mp_hand->push(card);
    }

    mp_table->clear();
    foreach (const CardData& cardData, publicPlayerData.table) {
        CardWidget* card = mp_cardWidgetFactory->createPlayingCard(this);
        card->setCardData(cardData);
        card->validate();
        mp_table->push(card);
    }
    m_isDead = !publicPlayerData.isAlive;
    m_role = publicPlayerData.role;
    updateWidgets();
}

void OpponentWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setClipRegion(event->rect());
    painter.fillRect(contentsRect(), QColor(0, 0, 0, 32));

    if (m_isCurrent) {
        painter.setPen(Qt::blue);
        painter.drawRect(contentsRect().adjusted(0, 0, -1, -1));
    }

    if (m_isRequested) {
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(2);
        pen.setStyle(Qt::DashLine);
        painter.setPen(pen);
        painter.drawRect(rect().adjusted(1, 1, -2, -2));
    }
}


void OpponentWidget::dieAndRevealRole(const PlayerRole& role)
{
    m_isDead = 1;
    m_role = role;
    updateWidgets();
}

void OpponentWidget::clear()
{
    setId(0);
    setName("");
    updateWidgets();
}


    /*
    if (progress == 0) {
        //frame->setStyleSheet(m_baseStyleSheet);
    } else {
        frame->setStyleSheet(
                m_baseStyleSheet + " QFrame#frame {"
                "border-left-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0.9, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 64));"
                "border-right-color: qlineargradient(spread:reflect, x1:0.1, y1:0, x2:1, y2:0, stop:0 rgba(255, 255, 255, 64), stop:1 rgba(0, 0, 0, 0));"
                "border-top-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.9, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 64));"
                "border-bottom-color: qlineargradient(spread:reflect, x1:0, y1:1, x2:0, y2:0.1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 64))""}");
    }
    */

void OpponentWidget::setAvatarPixmap()
{
    QPixmap avatar = m_avatar;
    if (!m_hasController && !avatar.isNull()) {
        QPainter painter(&avatar);
        painter.fillRect(avatar.rect(), QColor(0, 0, 0, 128));
    }
    mp_labelAvatar->setPixmap(avatar);
}


void OpponentWidget::updateWidgets()
{
    if (isVoid()) {
        mp_labelPlayerName->setText("");
        mp_characterWidget->setCharacter(CHARACTER_UNKNOWN);
        if (mp_roleCard)
            mp_roleCard->hide();
        if (mp_sheriffBadge)
            mp_sheriffBadge->hide();
        mp_hand->clear();
        mp_table->clear();
        mp_labelAvatar->setPixmap(QPixmap());
    } else {
        mp_labelPlayerName->setText(name());
        if (isSheriff()) {
            m_sheriffBadgePixmap.load(":/misc/gfx/misc/sheriff-badge.png");
            Q_ASSERT(!m_sheriffBadgePixmap.isNull());
            if (mp_sheriffBadge == 0) {
                mp_sheriffBadge = new QLabel(this);
                mp_sheriffBadge->setPixmap(m_sheriffBadgePixmap.scaled(48, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
                mp_sheriffBadge->resize(48, 48);
                mp_sheriffBadge->setToolTip(tr("This player is sheriff."));
            }
            mp_sheriffBadge->move(width() - mp_sheriffBadge->width(), 0);
            mp_sheriffBadge->show();
            //mp_sheriffBadge->setText("ADS");
        } else {
            if (mp_sheriffBadge != 0)
                mp_sheriffBadge->hide();
        }
        if (m_isDead) {
            if (mp_roleCard == 0) {
                mp_roleCard = mp_cardWidgetFactory->createRoleCard(this, m_role);
                mp_roleCard->setSize(CardWidget::SIZE_NORMAL);
            } else {
                mp_roleCard->setPlayerRole(m_role);
            }
            mp_roleCard->validate();
            mp_roleCard->move((int)(width() / 2 - mp_roleCard->width() / 2),
                              (int)(height() / 2 - mp_roleCard->height() / 2));
            mp_roleCard->show();
        }
        if (m_hasController) {
            if (mp_disconnectIcon)
                mp_disconnectIcon->hide();
            setAvatarPixmap();
        } else {
            if (!mp_disconnectIcon) {
                mp_disconnectIcon = new QLabel(this);
                QPixmap pixmap(":/icons/gfx/icons/disconnect.png");
                mp_disconnectIcon->setPixmap(pixmap);
                mp_disconnectIcon->resize(pixmap.size());
                QPoint pos = mp_labelAvatar->pos();
                QSize s = (mp_labelAvatar->size() - mp_disconnectIcon->size()) / 2;
                pos += QPoint(s.width(), s.height());
                mp_disconnectIcon->move(pos);mp_labelAvatar->pos();
            }
            mp_disconnectIcon->raise();
            mp_disconnectIcon->show();
            setAvatarPixmap();
        }
    }
}
