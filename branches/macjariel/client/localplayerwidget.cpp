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

#include <QtDebug>

using namespace client;

LocalPlayerWidget::LocalPlayerWidget(QWidget *parent)
 : PlayerWidget(parent), Ui::LocalPlayerWidget()
{
    setupUi(this);
    characterWidget->show();
    mp_hand = new CardList(0, CardWidget::SIZE_NORMAL);
    mp_table = new CardList(0, CardWidget::SIZE_SMALL);
    verticalLayout->addWidget(mp_table);
    verticalLayout->addStretch();
    verticalLayout->addWidget(mp_hand);
    m_baseStyleSheet = mainFrame->styleSheet();
    setActive(0);
}



LocalPlayerWidget::~LocalPlayerWidget()
{
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



void LocalPlayerWidget::updateWidgets()
{
    if (m_id != 0)
    {
        labelPlayerName->setText(m_name);
    }
    else
    {
        labelPlayerName->setText("");
    }
}



