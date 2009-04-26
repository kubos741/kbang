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

#include <QXmlStreamWriter>

#include "game.h"
#include "gameserver.h"
#include "client.h"
#include "player.h"
#include "common.h"



Game::Game(GameServer* parent, int gameId, const QString& name, const QString& description,
                     int creatorId, int minPlayers, int maxPlayers, int maxObservers,
                     const QString& playerPassword, const QString& observerPassword,
                     bool shufflePlayers):
QObject(parent),
m_gameId(gameId),
m_name(name),
m_description(description),
m_creatorId(creatorId),
m_minPlayers(minPlayers),
m_maxPlayers(maxPlayers),
m_maxObservers(maxObservers),
m_playerPassword(playerPassword),
m_observerPassword(observerPassword),
m_shufflePlayers(shufflePlayers),
m_nextPlayerId(0),
m_gameState(WaitingForPlayers),
m_publicGameView(this)
{
    Q_ASSERT(!m_name.isEmpty());
    Q_ASSERT(minPlayers <= maxPlayers);
    Q_ASSERT(m_observerPassword.isNull() || !m_playerPassword.isNull()); // observerPassword implies playerPassword
    //    m_adminPassword = randomToken(10, 16);



}

void Game::writeXml(QXmlStreamWriter& xmlOut, int level)
{
    xmlOut.writeStartElement("game");
    xmlOut.writeAttribute("id", QString::number(m_gameId));
    xmlOut.writeAttribute("name", m_name);
    xmlOut.writeAttribute("description", m_description);
    xmlOut.writeAttribute("creatorId", QString::number(m_creatorId));
    xmlOut.writeAttribute("minPlayers", QString::number(m_minPlayers));
    xmlOut.writeAttribute("maxPlayers", QString::number(m_maxPlayers));
    xmlOut.writeAttribute("maxObservers", QString::number(m_maxObservers));
    xmlOut.writeAttribute("playerPassword", QString::number(hasPlayerPassword()));
    xmlOut.writeAttribute("observerPassword", QString::number(hasObserverPassword()));
    xmlOut.writeAttribute("shufflePlayers", QString::number(hasShufflePlayers()));
    if (level > 0)
    {
        xmlOut.writeStartElement("players");
        foreach(Player* player, m_players.values())
        {
            xmlOut.writeStartElement("player");
            xmlOut.writeAttribute("name", player->name());
            // TODO: write about client
            xmlOut.writeEndElement();
        }
        xmlOut.writeEndElement();
    }
    xmlOut.writeEndElement();
}


Game::~Game()
{
}


Player* Game::createNewPlayer(const QString& name, const QString& password)
{
    while (!m_nextPlayerId || m_players.contains(m_nextPlayerId))
    {
        m_nextPlayerId++;
    }
    Player* newPlayer = new Player(m_nextPlayerId, name, password, this);
    m_players[m_nextPlayerId] = newPlayer;
    m_playerList.append(newPlayer);
    return newPlayer;
}




QList<Player *> Game::playerList()
{
    return m_playerList;
}

void Game::postMessage(Player* player, const QString& message)
{
    emit chatMessage(player->id(), player->name(), message);
}
