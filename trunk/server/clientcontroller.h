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
#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

class ClientPlayerCtrl;

#include <QObject>


class Client;

/**
 *	@author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class ClientController : public QObject
{
Q_OBJECT
public:
    ClientController(Client *client, ClientPlayerCtrl *clientPlayerController);
    ~ClientController();
    
    
    void leaveGame();
    void sendMessage(const QString& message);
    int gameId() const;
    void test();
    
private:
    Client             *mp_client;
    ClientPlayerCtrl   *mp_clientPlayerController;
    
signals:
    void actionLeaveGame();
    void actionSendMessage();

};

#endif
