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

#include <QtDebug>

using namespace client;

LocalPlayerWidget::LocalPlayerWidget(QWidget *parent):
        PlayerWidget(parent),
        Ui::LocalPlayerWidget(),
        m_isSheriff(0)
{
    setupUi(this);
    mp_hand->setCardSize(CardWidget::SIZE_NORMAL);
    mp_table->setCardSize(CardWidget::SIZE_SMALL);
    m_baseStyleSheet = mainFrame->styleSheet();
    setActive(0);
}



LocalPlayerWidget::~LocalPlayerWidget()
{
}

void LocalPlayerWidget::init()
{
    mp_characterWidget->init();
}



void LocalPlayerWidget::setFromPublicData(const PublicPlayerData& publicPlayerData)
{
    m_id        = publicPlayerData.id;
    m_name      = publicPlayerData.name;
    // mp_characterWidget->setCharacter(publicPlayerData.character);
    //mp_characterWidget->setLifePoints(publicPlayerData.lifePoints);
    m_isSheriff  = publicPlayerData.isSheriff;
    foreach (const CardData& cardData, publicPlayerData.table) {
        CardWidget* card = new CardWidget(0);
        card->setCardId(cardData.id);
       // card->setCardClass(cardData.type);
        mp_table->push(card);
    }
}

void LocalPlayerWidget::setFromPrivateData(const PrivatePlayerData& privatePlayerData)
{
    Q_ASSERT(m_id = privatePlayerData.id);
    /// \todo Role
    foreach (const CardData& cardData, privatePlayerData.hand) {
        CardWidget* card = new CardWidget(0);
        card->setCardId(cardData.id);
        //card->setCardClass(cardData.type);
        mp_hand->push(card);
    }
}

void LocalPlayerWidget::setPlayer(const StructPlayer& player)
{
    m_id = player.id;
    m_name = player.name;
    updateWidgets();
}

void LocalPlayerWidget::unsetPlayer()
{
    m_id = 0;
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

PlayerCharacterWidget* LocalPlayerWidget::playerCharacterWidget()
{
    return mp_characterWidget;
}

CardList* LocalPlayerWidget::hand()
{
    return mp_hand;
}

CardList* LocalPlayerWidget::table()
{
    return mp_table;
}

void LocalPlayerWidget::updateWidgets()
{
    if (m_id != 0) {
        mp_labelPlayerName->setText(m_name);
    } else {
        mp_labelPlayerName->setText("");
    }
}



