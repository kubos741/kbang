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

#include <QtDebug>

#include "cardpilewidget.h"

using namespace client;

OpponentWidget::OpponentWidget(QWidget *parent)
: PlayerWidget(parent), m_id(0)
{
    setupUi(this);

    mp_labelPlayerName->setText("");

    mp_hand = new CardList(0, CardWidget::SIZE_SMALL);
    horizontalLayout->addWidget(mp_hand);

    m_baseStyleSheet = frame->styleSheet();
    setActive(0);



//((QBoxLayout*)layout())->addLayout(l);

    /*
    QBoxLayout* l = new QBoxLayout(QBoxLayout::TopToBottom);
    //l->addWidget(mp_table);
    l->addWidget(x);
    tableSpace->setLayout(l);
    tableSpace->show();
    mp_table->show();
    */

    //    mp_labelPlayerName->setText(player.name);
    //m_id = player.id;

    //frame->setFrameStyle(QFrame::Box |  QFrame::Plain);
    //frame->setLineWidth(1);

}


OpponentWidget::~OpponentWidget()
{

}

void OpponentWidget::setPlayer(const StructPlayer& player)
{
    m_id = player.id;
    m_name = player.name;
    updateWidgets();
}

void OpponentWidget::unsetPlayer()
{
    m_id = 0;
    updateWidgets();
}

void OpponentWidget::setActive(uint8_t progress)
{
    qDebug() << m_baseStyleSheet;
    if (progress == 0) {
        frame->setStyleSheet(m_baseStyleSheet);
    } else {
        frame->setStyleSheet(
                m_baseStyleSheet + " QFrame#frame {"
                "background-clip: content;"
                "border-left-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0.9, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 64));"
                "border-right-color: qlineargradient(spread:reflect, x1:0.1, y1:0, x2:1, y2:0, stop:0 rgba(255, 255, 255, 64), stop:1 rgba(0, 0, 0, 0));"
                "border-top-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.9, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 64));"
                "border-bottom-color: qlineargradient(spread:reflect, x1:0, y1:1, x2:0, y2:0.1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 64))""}");
    }
}




QSize OpponentWidget::sizeHint() const
{
    return QWidget::sizeHint();
    //    return QSize(220, 220);
}



void OpponentWidget::updateWidgets()
{
    if (isEmpty())
    {
        mp_labelPlayerName->setText("");
    }
    else
    {
        mp_labelPlayerName->setText(m_name);
    }
}
