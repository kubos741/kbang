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
#include "player.h"
#include "game.h"
#include "client.h"


Player::Player(int id, const QString& name, const QString& password, Game* game):
QObject(game),
m_id(id),
//m_controller(0),
m_name(name),
m_password(password),
mp_game(game),
m_runner(this),
m_publicPlayerView(this),
m_privatePlayerView(this),
m_playerActions(this)
{
    connect(game, SIGNAL(chatMessage(int, const QString&, const QString&)),
            this, SIGNAL(incomingChatMessage(int, const QString&, const QString&)));
    //    mp_client->mp_player = this;
    //    m_id = mp_game->appendNewPlayer(this);
}


Player::~Player()
{

}


void Player::attachPlayerController(AbstractPlayerCtrl* controller)
{
    m_runner.attachPlayerController(controller);
    m_runner.start();
}

void Player::detachPlayerController()
{
    m_runner.detachPlayerController();
}


/*
Player* Player::construct(const QString&      name,
                          const QString&      password,
                          Client*             client,
                          Game*          game)
{
    player = new Player(game, name, password, client);
    Q_ASSERT(player);

}
*/

void Player::postEventToController(QEvent* event)
{
    qDebug() << "Trying to post event to m_runner";
    m_runner.postEventToController(event);
    qDebug() << "Done here";

}


void Player::writeXml(QXmlStreamWriter& xmlOut) 
{
    xmlOut.writeStartElement("player");
    xmlOut.writeAttribute("id", QString::number(m_id));
    xmlOut.writeAttribute("name", m_name);
    xmlOut.writeEndElement();

}
