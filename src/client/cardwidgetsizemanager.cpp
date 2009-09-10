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
#include "cardwidgetsizemanager.h"

using namespace client;

qreal CardWidgetSizeManager::sm_cardRatio = 20 / 31;
qreal CardWidgetSizeManager::sm_lifePointCardRatio[] = {0, 19/75, 31/75, 44/75, 57/75, 68/75};
int CardWidgetSizeManager::sm_initialHeight = 75;

CardWidgetSizeManager::CardWidgetSizeManager():
        QObject(0)
{
    m_sizes[CARD_SIZE_NORMAL] = QSize(width(sm_initialHeight), sm_initialHeight);
    m_sizes[CARD_SIZE_ZOOMED] = QSize(200, 310);
}


QSize
CardWidgetSizeManager::cardSize(CardSizeRole cardSizeRole) const
{
    return m_sizes.value(cardSizeRole, QSize());
}

int
CardWidgetSizeManager::lifeLevel(int lifePoints) const
{
    if (lifePoints < 0 || lifePoints > 5)
        return 0;
    return (int)(m_normalSize.height() * sm_lifePointCardRatio[lifePoints]);
}

int
CardWidgetSizeManager::width(int height)
{
    return (int)(height * sm_cardRatio);
}
