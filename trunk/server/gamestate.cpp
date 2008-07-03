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


#include "gamestate.h"
#include "gameserver.h"

#include <QXmlStreamWriter>

GameState::GameState(GameServer* parent, int gameId, const QString& name, const QString& description,
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
m_shufflePlayers(shufflePlayers)
{
    Q_ASSERT(!m_name.isEmpty());
    Q_ASSERT(minPlayers <= maxPlayers);
    Q_ASSERT(m_observerPassword.isNull() || !m_playerPassword.isNull()); // observerPassword implies playerPassword



}

void GameState::writeXml(QXmlStreamWriter& xmlOut)
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
    xmlOut.writeEndElement();
}


GameState::~GameState()
{
}
/*
GameState::GameState(QObject * parent, const Client & client, int maxPlayers, int AIPlayers)
 :QObject(parent),
  m_state(STATE_AWAITING)
{
}
*/


