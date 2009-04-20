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

#include <QtDebug>
#include "playercharacterwidget.h"
#include "cardwidgetfactory.h"


using namespace client;

QTimer PlayerCharacterWidget::sm_timer;
int    PlayerCharacterWidget::sm_countAnimaton = 0;

const int timerInterval = 20;


PlayerCharacterWidget::PlayerCharacterWidget(QWidget *parent):
        QWidget(parent),
        m_lifePoints(0),
        m_isAnimating(0),
        mp_cardWidgetFactory(0)
{
        QSize widgetSize(CardWidget::qSize(CardWidget::SIZE_SMALL).width(),
                         (int)(CardWidget::qSize(CardWidget::SIZE_SMALL).height() * 1.9));
        setMinimumSize(widgetSize);
        setMaximumSize(widgetSize);
}

PlayerCharacterWidget::~PlayerCharacterWidget()
{
}

void PlayerCharacterWidget::init(CardWidgetFactory* cardWidgetFactory)
{
    mp_backCard = cardWidgetFactory->createCharacterCard(this);
    mp_backCard->validate();
    mp_backCard->move(0,0);
    mp_backCard->show();

    mp_characterCard = cardWidgetFactory->createCharacterCard(this);
    mp_characterCard->validate();
    mp_characterCard->move(0,0);
    mp_characterCard->show();
}

void PlayerCharacterWidget::setLifePoints(int lifePoints)
{
    if (lifePoints < 0 || lifePoints > 5) return;
    int oldLifePoints = m_lifePoints;
    m_lifePoints = lifePoints;
    if (oldLifePoints != m_lifePoints)
        lifePointsChanged();
}

void PlayerCharacterWidget::lifePointsChanged()
{
    static int levels[6] = {0, 19, 32, 45, 59, 71};
    m_targetY = mp_backCard->y() + levels[m_lifePoints];
    if (m_isAnimating) return;
    m_isAnimating = 1;
    connect(&sm_timer, SIGNAL( timeout()),
            this,      SLOT(onTimeout()));

    if (sm_countAnimaton == 0) {
        sm_timer.start(timerInterval);
    }
    sm_countAnimaton++;
}

void PlayerCharacterWidget::onTimeout()
{
    if (mp_characterCard->y() < m_targetY)
    {
        mp_characterCard->move(mp_characterCard->x(), mp_characterCard->y() + 1);
        mp_characterCard->show();
    }
    else if (mp_characterCard->y() > m_targetY)
    {
        mp_characterCard->move(mp_characterCard->x(), mp_characterCard->y() - 1);
        mp_characterCard->show();
    }
    if (mp_characterCard->y() == m_targetY)
    {
        sm_countAnimaton--;
        m_isAnimating = 0;
        disconnect(&sm_timer, 0, this, 0);
        if (sm_countAnimaton == 0) {
            sm_timer.stop();
        }
        emit animationFinished();
    }
}
