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
#include "cardlist.h"
#include "playercharacterwidget.h"
#include "cardwidgetfactory.h"
#include "gameobjectclickhandler.h"

#include <QtDebug>
#include <QPainter>
#include <QPaintEvent>

using namespace client;

LocalPlayerWidget::LocalPlayerWidget(QWidget *parent):
        PlayerWidget(parent),
        Ui::LocalPlayerWidget(),
        m_role(ROLE_UNKNOWN)
{
    setupUi(this);
    setContentsMargins(5, 5, 5, 5);
    mp_roleCardWidget->setType(Card::Role);
    mp_hand->setCardSize(CardWidget::SIZE_SMALL);
    mp_hand->setPocketType(POCKET_HAND);
    mp_hand->setOwnerId(id());
    mp_table->setCardSize(CardWidget::SIZE_SMALL);
    mp_table->setPocketType(POCKET_TABLE);
    mp_table->setOwnerId(id());

    updateWidgets();


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

void LocalPlayerWidget::init(GameObjectClickHandler* gameObjectClickHandler, CardWidgetFactory* cardWidgetFactory)
{
    PlayerWidget::init(gameObjectClickHandler, cardWidgetFactory);
    mp_characterWidget->init(mp_cardWidgetFactory);
    mp_cardWidgetFactory->registerCard(mp_roleCardWidget);
    m_role = ROLE_UNKNOWN;
    mp_buttonEndTurn->setEnabled(0);
    mp_buttonPass->setEnabled(0);
    mp_buttonDiscard->setEnabled(0);
}

void LocalPlayerWidget::setFromPublicData(const PublicPlayerData& publicPlayerData)
{
    setId(publicPlayerData.id);
    setName(publicPlayerData.name);
    mp_characterWidget->setCharacter(publicPlayerData.character);
    mp_characterWidget->setLifePoints(publicPlayerData.lifePoints);
    mp_characterWidget->setOwnerId(id());
    setSheriff(publicPlayerData.isSheriff);

    QPixmap avatar;
    if (!publicPlayerData.avatar.isNull())
        avatar = QPixmap::fromImage(publicPlayerData.avatar).scaled(mp_labelAvatar->size(),
                                                                    Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mp_labelAvatar->setPixmap(avatar);

    mp_hand->setOwnerId(id());
    mp_table->setOwnerId(id());

    mp_table->clear();
    foreach (const CardData& cardData, publicPlayerData.table) {
        CardWidget* card = mp_cardWidgetFactory->createPlayingCard(this);
        card->setCardData(cardData);
        card->validate();
        mp_table->push(card);
    }

    updateWidgets();
}

void LocalPlayerWidget::setFromPrivateData(const PrivatePlayerData& privatePlayerData)
{
    Q_ASSERT(id() == privatePlayerData.id);
    m_role = privatePlayerData.role;
    mp_hand->clear();
    foreach (const CardData& cardData, privatePlayerData.hand) {
        CardWidget* card = mp_cardWidgetFactory->createPlayingCard(this);
        card->setCardData(cardData);
        card->validate();
        mp_hand->push(card);
    }
    updateWidgets();
}

void LocalPlayerWidget::dieAndRevealRole(const PlayerRole& role)
{
    Q_UNUSED(role);
}


void LocalPlayerWidget::clear()
{
    setId(0);
    setName("");
    updateWidgets();
}

void LocalPlayerWidget::setGameButtonState(const GameContextData& gameContext)
{
    qDebug() << "setGameButtonState" << gameContext.requestedPlayerId;
    if (gameContext.requestedPlayerId != id()) {
        qDebug() << "A";
        mp_buttonPass->setEnabled(0);
        mp_buttonEndTurn->setEnabled(0);
        mp_buttonDiscard->setEnabled(0);
        mp_buttonDiscard->setChecked(0);
        return;
    }
    switch(gameContext.gamePlayState) {
    case GAMEPLAYSTATE_DRAW:
        qDebug() << "B";
        mp_buttonPass->setEnabled(0);
        mp_buttonEndTurn->setEnabled(0);
        mp_buttonDiscard->setEnabled(0);
        mp_buttonDiscard->setChecked(0);
        break;
    case GAMEPLAYSTATE_TURN:
        qDebug() << "C";
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

void LocalPlayerWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setClipRect(event->rect());
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

void LocalPlayerWidget::onEndTurnClicked()
{
    if (mp_gameObjectClickHandler != 0)
        mp_gameObjectClickHandler->onEndTurnClicked();
}

void LocalPlayerWidget::onPassClicked()
{
    if (mp_gameObjectClickHandler != 0)
        mp_gameObjectClickHandler->onPassClicked();
}

void LocalPlayerWidget::onDiscardClicked()
{
    if (mp_gameObjectClickHandler != 0)
        mp_gameObjectClickHandler->setDiscardMode(mp_buttonDiscard->isChecked());
}



void LocalPlayerWidget::updateWidgets()
{
    if (isVoid()) {
        mp_labelPlayerName->setText("");
        mp_characterWidget->setCharacter(CHARACTER_UNKNOWN);
        mp_roleCardWidget->setEmpty();
        mp_roleCardWidget->validate();
        mp_hand->clear();
        mp_table->clear();
        mp_labelAvatar->setPixmap(QPixmap());
    } else {
        mp_labelPlayerName->setText(name());
        if (m_role != ROLE_UNKNOWN) {
            mp_roleCardWidget->setPlayerRole(m_role);
        } else {
            mp_roleCardWidget->setEmpty();
        }
        mp_roleCardWidget->validate();
    }
}



