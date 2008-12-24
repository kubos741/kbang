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

OpponentWidget::OpponentWidget(QWidget *parent)
: QWidget(parent), m_id(0)
{
    setupUi(this);


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
