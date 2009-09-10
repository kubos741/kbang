/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
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

#include "characterwidget.h"

using namespace client;

QTimer CharacterWidget::sm_timer;
int    CharacterWidget::sm_countAnimaton = 0;

double pixelsPerSecond =  25;
const int timerInterval = 100;


CharacterWidget::CharacterWidget(QWidget *parent):
        QWidget(parent),
        m_character(CHARACTER_UNKNOWN),
        m_lifePoints(0),
        mp_backCard(0),
        mp_characterCard(0),
        m_isAnimating(0)
{
    connect(&CardWidgetSizeManager::instance(), SIGNAL(cardSizeChanged()),
            this, SLOT(updateWidgetSize()));
    updateWidgetSize();

    mp_backCard = new CardWidget(this);
    mp_backCard->setCharacterCard();
    mp_backCard->updatePixmap();
    mp_backCard->move(0, 0);
    mp_backCard->hide();

    mp_characterCard = new CardWidget(this);
    mp_characterCard->setCharacterCard();
    mp_characterCard->move(0, 0);
    mp_characterCard->hide();
}

/* virtual */
CharacterWidget::~CharacterWidget()
{
}

void
CharacterWidget::setOwnerId(PlayerId ownerId)
{
    mp_backCard->setOwnerId(ownerId);
    mp_characterCard->setOwnerId(ownerId);
}

void
CharacterWidget::setCharacter(const QString& character)
{
    m_character = character;
    if (mp_characterCard) {
        mp_characterCard->setCharacterCard(character);
        mp_characterCard->updatePixmap();
        mp_characterCard->setVisible(!isEmpty());
    }
    if (mp_backCard) {
        mp_backCard->setVisible(!isEmpty());
    }
}

void
CharacterWidget::setLifePoints(int lifePoints)
{
    if (lifePoints < 0 || lifePoints > 5) return;

    int oldLifePoints = m_lifePoints;
    m_lifePoints = lifePoints;
    if (oldLifePoints != m_lifePoints) {
        startAnimation();
    } else {
        emit animationFinished();
    }
}

void
CharacterWidget::startAnimation()
{
    m_sourceY = mp_characterCard->y();
    m_targetY = mp_backCard->y() +
                CardWidgetSizeManager::instance().lifeLevel(m_lifePoints);
    m_time.start();
    if (m_isAnimating) return;
    m_isAnimating = 1;

    connect(&sm_timer, SIGNAL( timeout()),
            this,      SLOT(onAnimationTimeout()));
    if (sm_countAnimaton == 0) {
        sm_timer.start(timerInterval);
    }
    sm_countAnimaton++;
}

void
CharacterWidget::updateWidgetSize()
{
    QSize cardSize(CardWidgetSizeManager::instance().size(CARD_SIZE_NORMAL));
    int maxLifeLevel = CardWidgetSizeManager::instance().lifeLevel(5);
    QSize widgetSize(cardSize.width(), (int)(cardSize.height() + maxLifeLevel));
    setMinimumSize(widgetSize);
    setMaximumSize(widgetSize);
    resize(widgetSize);
}

void
CharacterWidget::onAnimationAnimationTimeout()
{
    qreal progress;
    if (!isEmpty()) {
        progress = (m_time.elapsed() * pixelsPerSecond / 1000) / abs(m_sourceY - m_targetY);
        int currentY;
        if (progress >= 1) {
            currentY = m_targetY;
        } else {
            currentY = m_sourceY + (int)((m_targetY - m_sourceY) * progress);
        }
        //qDebug() << m_time.elapsed() << ", " << pixelsPerSecond << ", " << progress << ", " << m_sourceY << ", " << m_targetY << ", " << currentY;
        mp_characterCard->move(mp_characterCard->x(), currentY);
        mp_characterCard->show();
    }

    if (progress >= 1 || isEmpty())
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
