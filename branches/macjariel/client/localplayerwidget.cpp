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
    mp_roleCardWidget->setType(Card::Role);
    mp_hand->setCardSize(CardWidget::SIZE_SMALL);
    mp_hand->setPocketType(POCKET_HAND);
    mp_hand->setOwnerId(id());
    mp_table->setCardSize(CardWidget::SIZE_SMALL);
    mp_table->setPocketType(POCKET_TABLE);
    mp_table->setOwnerId(id());
    //m_baseStyleSheet = mainFrame->styleSheet();
    setActive(0);
    updateWidgets();

    connect(mp_buttonEndTurn, SIGNAL(clicked()),
            this,             SLOT(onEndTurnClicked()));
    connect(mp_buttonPass,    SIGNAL(clicked()),
            this,             SLOT(onPassClicked()));
    connect(mp_buttonDiscard, SIGNAL(clicked()),
            this,             SLOT(onDiscardClicked()));

}

LocalPlayerWidget::~LocalPlayerWidget()
{
}

void LocalPlayerWidget::init(GameObjectClickHandler* gameObjectClickHandler, CardWidgetFactory* cardWidgetFactory)
{
    PlayerWidget::init(gameObjectClickHandler, cardWidgetFactory);
    mp_characterWidget->init(mp_cardWidgetFactory);
    mp_cardWidgetFactory->registerCard(mp_roleCardWidget);
}

void LocalPlayerWidget::setFromPublicData(const PublicPlayerData& publicPlayerData)
{
    setId(publicPlayerData.id);
    setName(publicPlayerData.name);
    //mp_characterWidget->setCharacter(publicPlayerData.character);
    mp_characterWidget->setLifePoints(publicPlayerData.lifePoints);
    setSheriff(publicPlayerData.isSheriff);
    // Set cards on table
    /* TODO
    foreach (const CardData& cardData, publicPlayerData.table) {
        CardWidget* card = mp_cardWidgetFactory->createBackCard();
        card->setCardId(cardData.id);
       // card->setCardClass(cardData.type);
        mp_table->push(card);
    }
    */
    mp_hand->setOwnerId(id());
    mp_table->setOwnerId(id());
    updateWidgets();
}

void LocalPlayerWidget::setFromPrivateData(const PrivatePlayerData& privatePlayerData)
{
    Q_ASSERT(id() == privatePlayerData.id);
    m_role = privatePlayerData.role;


    // Set cards in hand
    /* TODO
    foreach (const CardData& cardData, privatePlayerData.hand) {
        CardWidget* card = new CardWidget(0);
        card->setCardId(cardData.id);
        //card->setCardClass(cardData.type); //TODO
        mp_hand->push(card);
    }
    */
    updateWidgets();
}

void LocalPlayerWidget::dieAndRevealRole(const PlayerRole& role)
{
}


void LocalPlayerWidget::clear()
{
    setId(0);
    setName("");
    updateWidgets();
}

void LocalPlayerWidget::setActive(uint8_t progress)
{
    if (progress == 0) {
        mainFrame->setStyleSheet(m_baseStyleSheet);
    } else {
        mainFrame->setStyleSheet(
                m_baseStyleSheet + " QFrame#mainFrame {"
                "background-clip: content;"
                "border-left-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0.9, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 64));"
                "border-right-color: qlineargradient(spread:reflect, x1:0.1, y1:0, x2:1, y2:0, stop:0 rgba(255, 255, 255, 64), stop:1 rgba(0, 0, 0, 0));"
                "border-top-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.9, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 64));"
                "border-bottom-color: qlineargradient(spread:reflect, x1:0, y1:1, x2:0, y2:0.1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 64))""}");
    }
}


void LocalPlayerWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(event->rect(), QColor(0, 0, 0, 32));
}

void LocalPlayerWidget::onEndTurnClicked()
{
    mp_gameObjectClickHandler->onEndTurnClicked();
}

void LocalPlayerWidget::onPassClicked()
{
    mp_gameObjectClickHandler->onPassClicked();
}

void LocalPlayerWidget::onDiscardClicked()
{
    mp_gameObjectClickHandler->setDiscardMode(mp_buttonDiscard->isChecked());
}



void LocalPlayerWidget::updateWidgets()
{
    if (isVoid()) {
        mp_labelPlayerName->setText("");
        //mp_characterWidget->hide();
    } else {
        mp_labelPlayerName->setText(name());
        mp_characterWidget->show();
    }
    mp_roleCardWidget->setPlayerRole(m_role);
    mp_roleCardWidget->validate();
}



