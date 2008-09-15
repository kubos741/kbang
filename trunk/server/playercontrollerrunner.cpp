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
    qDebug() << __LINE__ << mp_playerController;

}


PlayerControllerRunner::~PlayerControllerRunner()
{
    if (isRunning())
    {
        exit();
        wait();
    }
}


void PlayerControllerRunner::start()
{
    /// The playerController is moved to this thread which means that events for the controller will be
    /// handled in this thread. After the thread event loop returns, the thread affinity of the controller
    /// is restored.
    qDebug() << "PlayerControllerRunner::start() - thread: " << QThread::currentThread();
    qDebug() << "mp_playerController's thread before:" << mp_playerController->thread();
    QThread::start();
    //QThread* originalThread = mp_playerController->thread();
    mp_playerController->moveToThread(this);
    qDebug() << "mp_playerController's thread after:" << mp_playerController->thread();
}


void PlayerControllerRunner::run()
{
    Q_ASSERT(mp_playerController);
    qDebug() << "PlayerControllerRunner::run() - thread: " << QThread::currentThread();
    
    mp_playerController->start();
    this->exec();
    qDebug() << "PlayerControllerRunner::run() - end of loop, thread: " << QThread::currentThread();

//    mp_playerController->moveToThread(originalThread);
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
    qDebug() << "Attaching mp_playerController()";
    /// Supply the callback functions to the controller
    mp_playerController->attachPlayer(mp_player->privatePlayerView(),
                                      mp_player->game()->publicGameView(),
                                      mp_player->playerActions()
                                     );
    connect(mp_player, SIGNAL(incomingChatMessage(int, const QString&, const QString&)),
            mp_playerController, SLOT(incomingChatMessage(int, const QString&, const QString&)));
    
}

void PlayerControllerRunner::detachPlayerController()
{
    if (isRunning())
    {
        quit();
        if (!wait(500))
        {
            qDebug() << __FILE__ << ":" << __LINE__ << ": Killing thread";
            terminate();
        }
    }
    Q_ASSERT(!isRunning());
    Q_ASSERT(mp_playerController != 0);
    mp_playerController->detachPlayer();
    mp_playerController = 0;
    qDebug() << "Detaching mp_playerController()";
    qDebug() << __LINE__ << mp_playerController;
    disconnect(mp_player, SIGNAL(incomingChatMessage(int, const QString&, const QString&)),
               mp_playerController, SLOT(incomingChatMessage(int, const QString&, const QString&)));
}

bool PlayerControllerRunner::postEventToController(QEvent* e)
{

    qDebug() << "Inside PlayerControllerRunner::event()";
/*
    printf("%d\n", mp_playerController);
    qDebug() << __LINE__ << mp_playerController;
    
    if (e->spontaneous()) return QObject::event(e);
    //Q_ASSERT(mp_playerController == 0);
    
   // Q_ASSERT(mp_playerController);
   // Q_ASSERT(e);
    QCoreApplication::postEvent(mp_playerController, e);
    return true;
*/
}



