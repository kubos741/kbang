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
m_name(name),
m_password(password),
mp_game(game)
{
    //    mp_client->mp_player = this;
    //    m_id = mp_game->appendNewPlayer(this);
}


Player::~Player()
{

}

const int Player::id() const
{
    return m_id;
}

QString Player::name() const
{
    return m_name;
}

void Player::startGame()
{
    if (mp_game->creatorId() != m_id) return; // TODO: error to client
    mp_game->startGame();
}

void Player::leaveGame()
{
    mp_game->removePlayer(m_id);
}

void Player::sendMessage(const QString& message)
{
    mp_game->sendMessage(this, message);
}

StructPlayer Player::structPlayer()
{
    StructPlayer x;
    x.id = m_id;
    x.name = m_name;
    x.password = m_password;
    return x;
}

Game* Player::game() const
{
    return mp_game;
}

