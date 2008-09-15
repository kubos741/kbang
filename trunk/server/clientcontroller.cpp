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
#include "clientcontroller.h"
#include "clientplayerctrl.h"
#include "client.h"

ClientController::ClientController(Client* client, ClientPlayerCtrl* clientPlayerController):
        QObject(client), mp_client(client), mp_clientPlayerController(clientPlayerController)
{
//    connect(this, SIGNAL(actionLeaveGame()), clientPlayerController, SLOT(actionLeaveGame()),Qt::QueuedConnection);
}

void ClientController::leaveGame()
{
    qDebug() << "ClientController::leaveGame()"  << QThread::currentThread();
//    mp_clientPlayerController->actionLeaveGame();
    emit actionLeaveGame();
}

ClientController::~ ClientController()
{
}

void ClientController::test()
{
    qDebug() << "Number: " << (int)receivers(SIGNAL(actionLeaveGame()));
}




int ClientController::gameId() const
{
    return mp_clientPlayerController->gameId();
}

void ClientController::sendMessage(const QString& message)
{
    emit actionSendMessage(message);
}