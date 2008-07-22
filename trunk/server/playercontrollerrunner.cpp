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
#include "playercontrollerrunner.h"
#include "player.h"
#include "abstractplayerctrl.h"
#include "game.h"

PlayerControllerRunner::PlayerControllerRunner(Player* player):
QThread(0),
mp_player(player),
mp_playerController(0)
{

}


PlayerControllerRunner::~PlayerControllerRunner()
{
}


void PlayerControllerRunner::run()
{
    Q_ASSERT(mp_playerController);
    QThread* originalThread = mp_playerController->thread();
    /// The playerController is moved to this thread which means that events for the controller will be
    /// handled in this thread. After the thread event loop returns, the thread affinity of the controller
    /// is restored.
    mp_playerController->moveToThread(this);
    this->exec();
    mp_playerController->moveToThread(originalThread);
    /// As soon as thread ends, we detach player controller
    detachPlayerController();
}

void PlayerControllerRunner::stop()
{
    quit();
}

void PlayerControllerRunner::attachPlayerController(AbstractPlayerCtrl* playerController)
{
    Q_ASSERT(!isRunning());
    Q_ASSERT(mp_playerController == 0);
    mp_playerController = playerController;
    /// Supply the callback functions to the controller
    mp_playerController->attachPlayer(mp_player->privatePlayerView(),
                                      mp_player->game()->publicGameView(),
                                      mp_player->playerActions()
                                     );
}

void PlayerControllerRunner::detachPlayerController()
{


    Q_ASSERT(!isRunning()); /// Maybe we can wait for thread to terminate with QThread::wait
    Q_ASSERT(mp_playerController != 0);
    mp_playerController->detachPlayer();
    mp_playerController = 0;
}

bool PlayerControllerRunner::event(QEvent* e)
{
    if (e->spontaneous()) return QObject::event(e);
    Q_ASSERT(mp_playerController);
    QCoreApplication::postEvent(mp_playerController, e);
    return true;
}

