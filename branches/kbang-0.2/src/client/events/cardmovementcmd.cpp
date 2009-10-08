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

#include "cardmovementcmd.h"
#include "cardwidget.h"
#include "game.h"
#include "deckwidget.h"
#include "graveyardwidget.h"
#include "playerwidget.h"
#include "cardlistwidget.h"
#include "mainwindow.h"

#include <cmath>
#include <QTimerEvent>
#include <QTimer>

#include "debug/debugblock.h"

using namespace client;

//const int       tickTime        = 20;
//const double    pixelsPerTick   = 24;

// DEBUG FAST VALUES
const int       tickTime        = 20;
const double    pixelsPerSecond = 1000;

CardMovementCmd::CardMovementCmd(GameEvent* gameEvent,
                                 CardMovementCmdDataPtr doCmd):
        GameEventCmd(gameEvent),
        mp_doCmd(doCmd),
        mp_card(0),
        mp_destPocket(0),
        mp_cardData(0),
        m_tick(0),
        m_animationTimer(0)
{
}

/* virtual */
CardMovementCmd::~CardMovementCmd()
{
    if (mp_card) {
        mp_card->deleteLater();
    }
}

/* virtual slot */
void CardMovementCmd::doEventCmd(GameEvent::ExecutionMode mode)
{
    DEBUG_BLOCK;
    Q_ASSERT(mp_card == 0);
    Q_ASSERT(mp_destPocket == 0);
    Q_ASSERT(mp_cardData == 0);

    GameEventCmd::doEventCmd(mode);
    setCardAndPocket(mp_doCmd);

    if (mp_card == 0 || mp_destPocket == 0) {
        qCritical("Cannot run CardMovementEvent. Either card or destPocket "
                  "cannot be found.");
        if (mode == GameEvent::ExecuteNormal) {
            QTimer::singleShot(1, this, SLOT(finish()));
        }
        return;
    }

    if (mode == GameEvent::ExecuteNormal) {
        startTransition();
    } else {
        ///@todo Fast mode needs to be tested
        if (mp_cardData->id != 0 && !mp_destPocket->isRevealed()) {
            mp_card->setCardData(CardData());
        } else {
            mp_card->setCardData(*mp_cardData);
        }
        mp_cardData = 0;
        mp_destPocket->push(mp_card);
        mp_card = 0;
        mp_destPocket = 0;
    }
}

/* virtual */
void CardMovementCmd::undoEventCmd(GameEvent::ExecutionMode mode)
{
    DEBUG_BLOCK;
    GameEventCmd::doEventCmd(mode);
    setCardAndPocket(mp_undoCmd);

    if (mp_card == 0 || mp_destPocket == 0) {
        qCritical("Cannot run CardMovementEvent. Either card or destPocket "
                  "cannot be found.");
        if (mode == GameEvent::ExecuteNormal) {
            QTimer::singleShot(1, this, SLOT(finish()));
        }
        return;
    }

    if (mode == GameEvent::ExecuteNormal) {
        Q_ASSERT(mp_card->isVisible());
        Q_ASSERT(mp_destPocket->isVisible());
        startTransition();
    } else {
        ///@todo Fast mode needs to be tested
        if (mp_cardData->id != 0 && !mp_destPocket->isRevealed()) {
            mp_card->setCardData(CardData());
        } else {
            mp_card->setCardData(*mp_cardData);
        }
        mp_cardData = 0;
        mp_destPocket->push(mp_card);
        mp_card = 0;
        mp_destPocket = 0;
    }
}

/* virtual */
void CardMovementCmd::finish()
{
    mp_cardData = 0;
    mp_card = 0;
    mp_destPocket = 0;
    GameEventCmd::finish();
}

void
CardMovementCmd::setCardAndPocket(const CardMovementCmdDataPtr& cmd)
{
    Game* game = mp_gameEvent->game();
    Q_ASSERT(game != 0);
    Q_ASSERT(game->interfaceType() == Game::GameInterface);

    if (m_isFirstRun) {
        /// Set the undo cmd
        Q_ASSERT(mp_undoCmd.isNull());
        mp_undoCmd = CardMovementCmdDataPtr(new CardMovementCmdData());
        mp_undoCmd->pocketTypeFrom  = mp_doCmd->pocketTypeTo;
        mp_undoCmd->pocketTypeTo    = mp_doCmd->pocketTypeFrom;
        mp_undoCmd->playerFrom      = mp_doCmd->playerTo;
        mp_undoCmd->playerTo        = mp_doCmd->playerFrom;
        mp_undoCmd->card            = mp_doCmd->card;
        if (cmd->pocketTypeTo == POCKET_GRAVEYARD) {
            CardWidget* graveyardTop = game->graveyard()->peek();
            if (graveyardTop != 0) {
                mp_undoCmd->secondCard = graveyardTop->cardData();
            }
        }
        m_isFirstRun = 0;
    }

    PlayerWidget* srcPlayer  = game->playerWidget(cmd->playerFrom);
    PlayerWidget* destPlayer = game->playerWidget(cmd->playerTo);
    mp_cardData = &cmd->card;

    switch(cmd->pocketTypeFrom)
    {
    case POCKET_DECK:
        mp_card = game->deck()->pop();
        break;
    case POCKET_GRAVEYARD:
        if (cmd->secondCard.id != 0) {
            game->graveyard()->setSecondCard(cmd->secondCard);
        }
        mp_card = game->graveyard()->pop();
        break;
    case POCKET_HAND:
        if (!srcPlayer) {
            qCritical("Invalid card movement from POCKET_HAND (unknown player).");
            break;
        }
        if (srcPlayer->isLocalPlayer() && cmd->card.id == 0) {
            qCritical("Invalid card movement from POCKET_HAND (unknown card).");
            break;
        }
        mp_card = srcPlayer->hand()->take(srcPlayer->isLocalPlayer() ?
                                          cmd->card.id : 0);
        break;
    case POCKET_TABLE:
        if (!srcPlayer) {
            qCritical("Invalid card movement from POCKET_TABLE (unknown player).");
            break;
        }
        if (cmd->card.id == 0) {
            qCritical("Invalid card movement from POCKET_TABLE (unknown card).");
            break;
        }
        mp_card = srcPlayer->table()->take(cmd->card.id);
        break;
    case POCKET_SELECTION:
        mp_card = game->selection()->take(cmd->card.id);
        break;
    case POCKET_INVALID:
        break;
    }

    switch(cmd->pocketTypeTo)
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
CardMovementCmd::startTransition()
{
    if (!mp_destPocket->isVisible() || !mp_card->isVisible()) {
        QTimer::singleShot(10, this, SLOT(startTransition()));
        return;
    }

    if (mp_card->parent() != MainWindow::instance()->centralWidget())
    {
        qDebug() << "mp_card->pos()" << mp_card->pos();
        // reparent card to centralWidget
        QPoint pos = mp_card->mapTo(MainWindow::instance()->centralWidget(), QPoint(0,0));
        qDebug() << "#pos" << pos;
        mp_card->setParent(MainWindow::instance()->centralWidget());
        mp_card->move(pos);
    }

    mp_card->raise();
    mp_card->show();
    m_srcPos = mp_card->pos();
    m_destPos = mp_destPocket->mapTo(MainWindow::instance()->centralWidget(), mp_destPocket->newCardPosition());
    m_length  = sqrt(pow(m_destPos.x() - m_srcPos.x(), 2) + pow(m_destPos.y() - m_srcPos.y(), 2));
    m_time.start();
    m_animationTimer = startTimer(tickTime);
}

/* virtual */
void CardMovementCmd::timerEvent(QTimerEvent* e)
{
    if (e->timerId() == m_animationTimer) {
        qreal progress = (m_time.elapsed() * pixelsPerSecond / 1000) / m_length;
        if (progress >= 1) {
            stopTransition();
        } else {
            QPoint currPos = m_srcPos + (m_destPos - m_srcPos) * progress;
            mp_card->move(currPos);
        }
    } else {
        GameEventCmd::timerEvent(e);
    }
}

void CardMovementCmd::stopTransition()
{
    DEBUG_BLOCK;
    killTimer(m_animationTimer);
    mp_card->setCardData(*mp_cardData);
    mp_destPocket->push(mp_card);
    if (mp_card->cardData().id != 0 && !mp_destPocket->isRevealed()) {
        // If revealed card moves to a unrevealed pocket (deck or opponent's
        // hand), it must be unrevealed. To give user time to notice what the
        // card was, the unrevealing is delayed.
        QTimer::singleShot(500, this, SLOT(unrevealCard()));
    } else {
        mp_card = 0;
        finish();
    }
}

/* slot */
void CardMovementCmd::unrevealCard()
{
    mp_card->unreveal();
    mp_card->updatePixmap();
    mp_card = 0;
    finish();
}
