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
#include "playercharacterwidget.h"

using namespace client;

PlayerCharacterWidget::PlayerCharacterWidget(QWidget *parent)
 : QWidget(parent)
{
    mp_timer = new QTimer(this);
    mp_timer->setInterval(10);
    connect(mp_timer, SIGNAL(timeout()),
            this, SLOT(animateCard()));

    mp_backCard = new CardWidget(this);
    mp_backCard->setSize(CardWidget::SIZE_SMALL);
    mp_backCard->setCardClass("back-bullets");
    mp_backCard->applyNewProperties();
    mp_backCard->move(0,0);

    mp_characterCard = new CardWidget(this);
    mp_characterCard->setSize(CardWidget::SIZE_SMALL);
    mp_characterCard->applyNewProperties();
    mp_characterCard->hide();
    mp_characterCard->move(0,0);


    m_sizeHint = QSize(mp_backCard->width(), 2 * mp_backCard->height());
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setLifePoints(5);
}


PlayerCharacterWidget::~PlayerCharacterWidget()
{
}

void PlayerCharacterWidget::setCharacter(const QString& character)
{
    m_character = character;
    mp_characterCard->setCardClass(character);
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
    static int levels[6] = {0, 15, 27, 37, 49, 60};
    m_targetY = mp_backCard->y() + levels[m_lifePoints];
    mp_timer->start();
}

void PlayerCharacterWidget::animateCard()
{
    if (mp_characterCard->y() < m_targetY)
    {
        mp_characterCard->move(mp_characterCard->x(), mp_characterCard->y() + 1);
    }
    else if (mp_characterCard->y() < m_targetY)
    {
        mp_characterCard->move(mp_characterCard->x(), mp_characterCard->y() - 1);
    }
    if (mp_characterCard->y() == m_targetY)
    {
        mp_timer->stop();
    }
}
