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

double pixelsPerSecond =  25;
const int timerInterval = 100;


PlayerCharacterWidget::PlayerCharacterWidget(QWidget *parent):
        QWidget(parent),
        m_lifePoints(0),
        m_isAnimating(0),
        mp_cardWidgetFactory(0)
{
        QSize widgetSize(CardWidget::qSize(CardWidget::SIZE_SMALL).width(),
                         (int)(CardWidget::qSize(CardWidget::SIZE_SMALL).height() * 2));
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
    else
        emit animationFinished();
}

void PlayerCharacterWidget::lifePointsChanged()
{
    static int levels[6] = {0, 21, 34, 49, 64, 77};
    m_sourceY = mp_characterCard->y();
    m_targetY = mp_backCard->y() + levels[m_lifePoints];
    m_time.start();
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
    qreal progress = (m_time.elapsed() * pixelsPerSecond / 1000) / abs(m_sourceY - m_targetY);
    int currentY;
    if (progress >= 1) {
        currentY = m_targetY;
    } else {
        currentY = m_sourceY + (m_targetY - m_sourceY) * progress;
    }
    //qDebug() << m_time.elapsed() << ", " << pixelsPerSecond << ", " << progress << ", " << m_sourceY << ", " << m_targetY << ", " << currentY;
    mp_characterCard->move(mp_characterCard->x(), currentY);
    mp_characterCard->show();

    if (progress >= 1)
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
