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
#include "game.h"

using namespace client;

OpponentWidget::OpponentWidget(QWidget *parent):
        PlayerWidget(parent),
        mp_sheriffBadge(0),
        mp_disconnectIcon(0),
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

void OpponentWidget::clearWidgets()
{
    PlayerWidget::clearWidgets();
    if (mp_sheriffBadge) {
        mp_sheriffBadge->hide();
    }
    if (mp_disconnectIcon) {
        mp_disconnectIcon->hide();
    }
    if (mp_roleCard) {
        mp_roleCard->hide();
    }
}

void OpponentWidget::updateWidgets()
{
    PlayerWidget::updateWidgets();
    updateSheriffBadgeIcon();
    updateRoleCard();
    updateDisconnectIcon();
    update();
}

void OpponentWidget::moveWinnerIcon()
{
    /** @todo: refactor me please */
    createRoleCard();
    mp_winnerIcon->move(mp_roleCard->x() + (int)(mp_roleCard->width() / 2) - (int)(mp_winnerIcon->width() / 3),
                        mp_roleCard->y() + mp_roleCard->height() - (int)(mp_roleCard->height() / 2));
}

void OpponentWidget::onGameEntered()
{
}

void OpponentWidget::createSheriffBadgeIcon()
{
    if (mp_sheriffBadge != 0)
        return;
    QPixmap sheriffBadgePixmap(":/misc/sheriff-badge.png");
    mp_sheriffBadge = new QLabel(this);
    mp_sheriffBadge->setPixmap(sheriffBadgePixmap.scaled(48, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    mp_sheriffBadge->resize(48, 48);
    mp_sheriffBadge->setToolTip(tr("This player is sheriff."));
}

void OpponentWidget::updateSheriffBadgeIcon()
{
    if (m_isSheriff) {
        createSheriffBadgeIcon();
        mp_sheriffBadge->move(width() - mp_sheriffBadge->width(), 0);
        mp_sheriffBadge->show();
    } else if (mp_sheriffBadge != 0) {
        mp_sheriffBadge->hide();
    }
}

void OpponentWidget::createRoleCard()
{
    if (mp_roleCard != 0)
        return;
    mp_roleCard = cardWidgetFactory()->createRoleCard(this, ROLE_UNKNOWN);
    mp_roleCard->setSize(CardWidget::SIZE_NORMAL);
    mp_roleCard->validate();
    mp_roleCard->move((int)(width() / 2 - mp_roleCard->width() / 2),
                      (int)(height() / 2 - mp_roleCard->height() / 2));

}

void OpponentWidget::updateRoleCard()
{
    if (!m_isAlive || mp_game->isFinished()) {
        createRoleCard();
        mp_roleCard->setPlayerRole(m_playerRole);
        mp_roleCard->validate();
        mp_roleCard->show();
        mp_roleCard->raise();
    } else if (mp_roleCard != 0) {
        mp_roleCard->hide();
    }
}

void OpponentWidget::createDisconnectIcon()
{
    if (mp_disconnectIcon != 0)
        return;
    QPixmap pixmap(":/icons/disconnect.png");
    mp_disconnectIcon = new QLabel(this);
    mp_disconnectIcon->setPixmap(pixmap);
    mp_disconnectIcon->resize(pixmap.size());
    QPoint pos = mp_labelAvatar->pos();
    QSize s = (mp_labelAvatar->size() - mp_disconnectIcon->size()) / 2;
    pos += QPoint(s.width(), s.height());
    mp_disconnectIcon->move(pos);
}

void OpponentWidget::updateDisconnectIcon()
{
    if (!m_hasController) {
        createDisconnectIcon();
        mp_disconnectIcon->raise();
        mp_disconnectIcon->show();
    } else if (mp_disconnectIcon != 0) {
        mp_disconnectIcon->hide();
    }
}
