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
#include "localplayerwidget.h"
#include "cardwidget.h"
#include "cardlistwidget.h"
#include "characterwidget.h"
#include "gameactionmanager.h"

#include <QtDebug>
#include <QPainter>
#include <QPaintEvent>

using namespace client;

LocalPlayerWidget::LocalPlayerWidget(QWidget *parent):
        PlayerWidget(parent)
{
    setupUi(this);
    setContentsMargins(5, 5, 5, 5);

    mp_roleCardWidget->setPlayerRoleCard(ROLE_UNKNOWN);

    mp_hand->setCardSizeRole(CARD_SIZE_NORMAL);
    mp_hand->setPocketType(POCKET_HAND);
    mp_hand->setOwnerId(id());

    mp_table->setCardSizeRole(CARD_SIZE_NORMAL);
    mp_table->setPocketType(POCKET_TABLE);
    mp_table->setOwnerId(id());

    clear();

    connect(mp_buttonEndTurn, SIGNAL(clicked()),
            this,             SLOT(onEndTurnClicked()));
    connect(mp_buttonPass,    SIGNAL(clicked()),
            this,             SLOT(onPassClicked()));
    connect(mp_buttonDiscard, SIGNAL(toggled(bool)),
            this,             SLOT(onDiscardClicked()));

    mp_buttonEndTurn->setEnabled(0);
    mp_buttonPass->setEnabled(0);
    mp_buttonDiscard->setEnabled(0);
}

LocalPlayerWidget::~LocalPlayerWidget()
{
}

void LocalPlayerWidget::setFromPrivateData(const PrivatePlayerData& privatePlayerData)
{
    Q_ASSERT(m_id == privatePlayerData.id);
    qDebug() << this << "setFromPrivateData";
    m_playerRole = privatePlayerData.role;
    
    mp_hand->clear();
    foreach (const CardData& cardData, privatePlayerData.hand) {
        CardWidget* card = new CardWidget(this);
        card->setCardData(cardData);
        card->updatePixmap();
        mp_hand->push(card);
    }
    
    updateWidgets();
}

void LocalPlayerWidget::setFromContext(const GameContextData& gameContext)
{
    if (gameContext.requestedPlayerId != id()) {
        mp_buttonPass->setEnabled(0);
        mp_buttonEndTurn->setEnabled(0);
        mp_buttonDiscard->setEnabled(0);
        mp_buttonDiscard->setChecked(0);
        return;
    }

    switch(gameContext.gamePlayState) {
    case GAMEPLAYSTATE_DRAW:
        mp_buttonPass->setEnabled(0);
        mp_buttonEndTurn->setEnabled(0);
        mp_buttonDiscard->setEnabled(0);
        mp_buttonDiscard->setChecked(0);
        break;
    case GAMEPLAYSTATE_TURN:
        mp_buttonPass->setEnabled(0);
        mp_buttonEndTurn->setEnabled(1);
        mp_buttonDiscard->setEnabled(1);
        mp_buttonDiscard->setChecked(0);
        break;
    case GAMEPLAYSTATE_RESPONSE:
        mp_buttonPass->setEnabled(1);
        mp_buttonEndTurn->setEnabled(0);
        mp_buttonDiscard->setEnabled(0);
        mp_buttonDiscard->setChecked(0);
        break;
    case GAMEPLAYSTATE_DISCARD:
        mp_buttonPass->setEnabled(0);
        mp_buttonEndTurn->setEnabled(0);
        mp_buttonDiscard->setEnabled(0);
        mp_buttonDiscard->setChecked(1);
        break;
    case GAMEPLAYSTATE_INVALID:
        break;
    }
}
void LocalPlayerWidget::clearWidgets()
{
    PlayerWidget::clear();
    mp_roleCardWidget->clear();

    mp_buttonEndTurn->setEnabled(0);
    mp_buttonPass->setEnabled(0);
    mp_buttonDiscard->setEnabled(0);

    update();
}

void LocalPlayerWidget::updateWidgets()
{
    PlayerWidget::updateWidgets();
    updateRoleCardWidget();
    update();
}

void LocalPlayerWidget::moveWinnerIcon()
{
    int x = (int)((mp_hand->width() - mp_winnerIcon->width()) / 2);
    int y = (int)((mp_table->y() + mp_table->height() - mp_hand->y() - mp_winnerIcon->height()) / 2);
    mp_winnerIcon->move(mp_hand->x() + x, mp_hand->y() + y);
}

void LocalPlayerWidget::setRoleFromPublicData(PlayerRole playerRole)
{
    Q_UNUSED(playerRole);
}

void LocalPlayerWidget::setHandSize(int handSize)
{
    Q_UNUSED(handSize);
}

void LocalPlayerWidget::onEndTurnClicked()
{
    if (gameActionManager() != 0)
        gameActionManager()->onEndTurnClicked();
}

void LocalPlayerWidget::onPassClicked()
{
    if (gameActionManager() != 0)
        gameActionManager()->onPassClicked();
}

void LocalPlayerWidget::onDiscardClicked()
{
    if (gameActionManager() != 0)
        gameActionManager()->setDiscardMode(mp_buttonDiscard->isChecked());
}

void LocalPlayerWidget::updateRoleCardWidget()
{
    if (m_playerRole != ROLE_UNKNOWN) {
        mp_roleCardWidget->setPlayerRoleCard(m_playerRole);
    } else {
        mp_roleCardWidget->clear();
    }
}
