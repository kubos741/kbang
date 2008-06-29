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

#include "gameserver.h"
#include "charactercard.h"
#include "console.h"
#include <QCoreApplication>


int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    GameServer& server = GameServer::instance();
    QObject::connect(&server, SIGNAL(aboutToQuit()),
                     &app, SLOT(quit()));
    server.setName("Testing server");
    server.listen();
    server.createGame("Testovaci hra", "Popis testovaci hry", 0, 5, 7, 99, QString(), QString(), 0);
    Console* console = new Console(&server, stdin, stdout);
    QObject::connect(&server, SIGNAL(aboutToQuit()),
                     console, SLOT(terminate()));

    console->start();
//    CharacterCard::loadCharacterBank();

//    Arbiter a;
    return app.exec();
}

