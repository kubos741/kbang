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

#include "cardpocket.h"
#include "cardwidget.h"
#include "cardwidgetsizemanager.h"

using namespace client;

CardPocket::CardPocket(QWidget *parent, bool isRevealed):
        QFrame(parent),
        m_isRevealed(isRevealed),
        m_pocketType(POCKET_INVALID),
        m_ownerId(0),
        m_cardSizeRole(CARD_SIZE_NORMAL)
{
    connect(&CardWidgetSizeManager::instance(), SIGNAL(cardSizeChanged()),
            this, SLOT(updateWidgetSize()));
    updateWidgetSize();
}

CardPocket::~CardPocket()
{
}

/* virtual */ void
CardPocket::push(CardWidget* cardWidget)
{
    cardWidget->setOwnerId(m_ownerId);
    cardWidget->setPocketType(m_pocketType);
}

void
CardPocket::setRevealed(bool isRevealed)
{
    m_isRevealed = isRevealed;
}

void
CardPocket::setPocketType(const PocketType& pocketType)
{
    m_pocketType = pocketType;
}

void CardPocket::setOwnerId(PlayerId ownerId)
{
    m_ownerId = ownerId;
}

void CardPocket::setCardSizeRole(CardSizeRole cardSizeRole)
{
    m_cardSizeRole = cardSizeRole;
    updateWidgetSize();
}
