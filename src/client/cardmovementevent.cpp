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
#include <cmath>
#include <QtCore>
#include <QtDebug>

#include "cardmovementevent.h"
#include "cardwidget.h"
#include "game.h"
#include "deckwidget.h"
#include "graveyardwidget.h"

using namespace client;

//const int       tickTime        = 20;
//const double    pixelsPerTick   = 24;

// DEBUG FAST VALUES
const int       tickTime        = 20;
const double    pixelsPerSecond = 1000;

CardMovementEvent::CardMovementEvent(Game* game, const CardMovementData& cardMovementData):
        GameEvent(game),
        m_cardMovementData(cardMovementData),
        mp_card(0),
        mp_destPocket(0),
        m_tick(0)
{
}

/* virtual */
CardMovementEvent::~CardMovementEvent()
{
    if (mp_card) {
        mp_card->deleteLater();
    }
}

/* virtual slot */ void
CardMovementEvent::run()
{
    if (mp_card == 0 || mp_destPocket == 0) {
        setCardAndPocket();
        if (mp_card == 0 || mp_destPocket == 0) {
            qCritical("Invalid card-movement event received. Skipping.");
            QTimer::singleShot(1, this, SLOT(finish()));
            return;
        }
    }

    if (!mp_card->isVisible() || !mp_destPocket->isVisible()) {
        // We need to wait, because widgets that are essential
        // for translation are not visible yet (and thus their
        // coords can be incorrect).
        QTimer::singleShot(20, this, SLOT(run()));
        return;
    }

    startTransition();
    GameEvent::run();
}

void
CardMovementEvent::setCardAndPocket()
{
    Game* game = Game::currentGame();

    if (game == 0 || game->gameInterfaceLoaded()) {
        return;
    }

    PlayerWidget* srcPlayer  = game->playerWidget(m_cardMovementData.playerFrom);
    PlayerWidget* destPlayer = game->playerWidget(m_cardMovementData.playerTo);

    switch(m_cardMovementData.pocketTypeFrom)
    {
    case POCKET_DECK:
        mp_card = game->deck()->pop();
        break;
    case POCKET_GRAVEYARD:
        if (m_cardMovementData.secondCard.id != 0) {
            game->graveyard()->setSecondCard(m_cardMovementData.secondCard);
        }
        mp_card = game->graveyard()->pop();
        break;
    case POCKET_HAND:
        if (!srcPlayer) {
            qCritical("Invalid card movement from POCKET_HAND (unknown player).");
            break;
        }
        if (srcPlayer->isLocalPlayer() && m_cardMovementData.card.id == 0) {
            qCritical("Invalid card movement from POCKET_HAND (unknown card).");
            break;
        }
        mp_card = srcPlayer->hand()->take(srcPlayer->isLocalPlayer() ?
                                          m_cardMovementData.card.id : 0);
        break;
    case POCKET_TABLE:
        if (!srcPlayer) {
            qCritical("Invalid card movement from POCKET_TABLE (unknown player).");
            break;
        }
        if (m_cardMovementData.card.id == 0) {
            qCritical("Invalid card movement from POCKET_TABLE (unknown card).");
            break;
        }
        mp_card = srcPlayer->table()->take(m_cardMovementData.card.id);
        break;
    case POCKET_SELECTION:
        mp_card = game->selection()->take(m_cardMovementData.card.id);
        break;
    case POCKET_INVALID:
        break;
    }

    switch(m_cardMovementData.pocketTypeTo)
    {
    case POCKET_DECK:
        mp_destPocket = game->deck();
        break;
    case POCKET_GRAVEYARD:
        mp_destPocket = game->graveyard();
        break;
    case POCKET_HAND:
        mp_destPocket = destPlayer != 0 ? destPlayer->hand() : 0;
        break;
    case POCKET_TABLE:
        mp_destPocket = destPlayer != 0 ? destPlayer->table() : 0;
        break;
    case POCKET_SELECTION:
        mp_destPocket = game->selection();
        break;
    case POCKET_INVALID:
        break;
    }
}

void
CardMovementEvent::startTransition()
{
    Game* game = Game::currentGame();

    Q_ASSERT(mp_destPocket->isVisible());
    Q_ASSERT(mp_card->isVisible());

    if (mp_card->parent() != game->mainWidget())
    {
        // reparent card to mainWidget
        QPoint pos = mp_card->mapTo(game->mainWidget(), QPoint(0,0));
        mp_card->setParent(game->mainWidget());
        mp_card->move(pos);
    }
    mp_card->raise();
    mp_card->show();
    m_destPos = mp_destPocket->mapTo(game->mainWidget(), mp_destPocket->newCardPosition());
    m_length  = sqrt(pow(m_destPos.x() - m_srcPos.x(), 2) + pow(m_destPos.y() - m_srcPos.y(), 2));
    m_time.start();
    m_timer.start(tickTime, this);
}

/* virtual */ void
CardMovementEvent::timerEvent(QTimerEvent*)
{
    qreal progress = (m_time.elapsed() * pixelsPerSecond / 1000) / m_length;
    if (progress >= 1) {
        stopTransition();
    } else {
        QPoint currPos = m_srcPos + (m_destPos - m_srcPos) * progress;
        mp_card->move(currPos);
    }
}

void
CardMovementEvent::stopTransition()
{
    m_timer.stop();
    int real     = m_time.elapsed();
    int expected = (int)(m_length * 1000 / pixelsPerSecond);
    if (real - expected > 50) {
        qDebug("Card movement should take %d ms, but took %d ms.", expected, real);
    }
    mp_card->setCardData(m_cardMovementData.card);
    mp_card->updatePixmap();
    mp_destPocket->push(mp_card);
    
    if (mp_card->cardData().id != 0 && ((mp_card->pocketType() == POCKET_HAND &&
        mp_card->ownerId() != game->playerId()) || mp_card->pocketType() == POCKET_DECK)) {
        // If revealed card moves to a unrevealed pocket (deck or opponent's
        // hand), it must be unrevealed. To give player time to notice what the
        // card was, the unrevealing is delayed.
        QTimer::singleShot(500, this, SLOT(unrevealCard()));
    } else {
        mp_card = 0;
        GameEvent::finish();
    }
}

/* slot */ void
CardMovementEvent::unrevealCard()
{
    mp_card->setCardData(CardData());
    mp_card->updatePixmap();
    mp_card = 0;
    GameEvent::finish();
}
