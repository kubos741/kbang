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
#include "game.h"
#include "serverconnection.h"
#include "parser/queryget.h"
#include "opponentwidget.h"

Game::Game(QObject* parent, int gameId, const StructPlayer& player, ServerConnection* serverConnection):
    QObject(parent), m_playerId(player.id), m_playerName(player.name), m_gameId(gameId), mp_serverConnection(serverConnection)
{
}

void Game::init()
{
    QueryGet* get = mp_serverConnection->queryGet();
    connect(get, SIGNAL(result(const StructGame&, const StructPlayerList&)),
            this, SLOT(initialGameStateRecieved(const StructGame&, const StructPlayerList&)));
    get->getGame(m_gameId);
    qDebug("You have entered the game!");
}


Game::~Game()
{
    foreach(int i, m_opponentWidgets.keys())
    {
        m_opponentWidgets[i]->deleteLater();
    }
}


void Game::opponentJoinedGame(const StructPlayer& player)
{
    m_opponentWidgets[player.id] = new OpponentWidget(0, player);
    mp_opponentsLayout->addWidget(m_opponentWidgets[player.id]);
    qDebug(qPrintable(QString("Player %1 has entered the game!").arg(player.name)));
}

void Game::opponentLeavedGame(const StructPlayer& player)
{
    if (m_opponentWidgets.contains(player.id))
    {
        m_opponentWidgets[player.id]->deleteLater();
        m_opponentWidgets.remove(player.id);
    }
}


void Game::initialGameStateRecieved(const StructGame&, const StructPlayerList& playerList)
{
    foreach(StructPlayer p, playerList)
    {
        if (p.id != m_playerId)
        {
            opponentJoinedGame(p);
        }
    }
}

void Game::delegateVisualElements(QLayout* opponentsLayout)
{
    mp_opponentsLayout = opponentsLayout;
}





