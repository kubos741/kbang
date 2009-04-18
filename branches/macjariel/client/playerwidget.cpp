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
#include "playerwidget.h"
#include "gameobjectclickhandler.h"
#include <QtDebug>


using namespace client;

PlayerWidget::PlayerWidget(QWidget* parent):
        QWidget(parent),
        mp_gameObjectClickHandler(0),
        mp_cardWidgetFactory(0),
        m_id(0),
        m_isSheriff(0)
{
}

void PlayerWidget::init(GameObjectClickHandler* gameObjectClickHandler, CardWidgetFactory* cardWidgetFactory)
{
    mp_gameObjectClickHandler = gameObjectClickHandler;
    mp_cardWidgetFactory = cardWidgetFactory;
}

void PlayerWidget::setPlayer(const StructPlayer& structPlayer)
{
    PublicPlayerData data;
    data.id = structPlayer.id;
    data.name = structPlayer.name;
    data.isSheriff = 0;
    data.lifePoints = 0;
    data.handSize = 0;
    // data.character
    setFromPublicData(data);
}

void PlayerWidget::setId(int id)
{
    m_id = id;
}

void PlayerWidget::setName(const QString& name)
{
    m_name = name;
}

void PlayerWidget::setSheriff(bool isSheriff)
{
    m_isSheriff = isSheriff;
}


void PlayerWidget::mousePressEvent(QMouseEvent *ev)
{
    if (mp_gameObjectClickHandler)
        mp_gameObjectClickHandler->onPlayerClicked(this);
}


