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
#include "playerwidget.h"
#include "opponentwidget.h"
#include "cardmovement.h"

#include <QtDebug>
#include <QBoxLayout>

Game::Game(QObject* parent, int gameId, const StructPlayer& player,
           ServerConnection* serverConnection, const GameWidgets& gameWidgets):
QObject(parent), m_playerId(player.id), m_playerName(player.name), m_gameId(gameId),
mp_serverConnection(serverConnection), mp_layout(gameWidgets.layout),
m_opponentWidgets(gameWidgets.opponentWidget), mp_playerWidget(gameWidgets.playerWidget),
m_creator(0)
{
}

void Game::init()
{
    QueryGet* get = mp_serverConnection->queryGet();
    connect(get, SIGNAL(result(const StructGame&, const StructPlayerList&)),
            this, SLOT(initialGameStateRecieved(const StructGame&, const StructPlayerList&)));
    get->getGame(m_gameId);
    if (m_creator)
    {
        mp_startButton = new QPushButton(0);
        mp_layout->addWidget(mp_startButton, 1, 1, 2, 2);
        mp_layout->setAlignment(mp_startButton, Qt::AlignCenter);
        mp_startButton->setText(tr("Start game"));
        mp_startButton->setEnabled(0);
        connect(mp_startButton, SIGNAL(clicked()),
                this, SLOT(startButtonClicked()));
        connect(mp_serverConnection, SIGNAL(startableChanged(int, bool)),
                this, SLOT(startableChanged(int, bool)));
    }
    connect(mp_serverConnection, SIGNAL(gameStarted(const StructGame&, const StructPlayerList&)),
            this, SLOT(gameStarted(const StructGame&, const StructPlayerList&)));


    qDebug("You have entered the game!");
}


Game::~Game()
{

}


void Game::opponentJoinedGame(const StructPlayer& player)
{
    qDebug() << player.id;
    qDebug() << player.name;
    for(int i = 0; i < m_opponentWidgets.count(); ++i)
    {
        OpponentWidget* w = m_opponentWidgets[i];
        if (w->isEmpty())
        {
            w->setPlayer(player);
            m_opponents[player.id] = i;
            break;
        }
    }
    qDebug(qPrintable(QString("Player %1 has entered the game!").arg(player.name)));
}

void Game::opponentLeavedGame(const StructPlayer& player)
{
    if (m_opponents.contains(player.id))
    {
        m_opponentWidgets[m_opponents[player.id]]->unsetPlayer();
        m_opponents.remove(player.id);
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
        else
        {
            mp_playerWidget->setPlayer(p);
        }
    }
}

void Game::startableChanged(int, bool startable)
{
    mp_startButton->setEnabled(startable);
}

void Game::startButtonClicked()
{
    disconnect(mp_startButton, SIGNAL(clicked()),
               this, SLOT(startButtonClicked()));
    mp_serverConnection->startGame();
}

void Game::gameStarted(const StructGame&, const StructPlayerList& playerList)
{
    int pI;
    for(pI = 0; pI < playerList.count(); pI++)
    {
        if (playerList[pI].id == m_playerId) break;
    }
    qDebug() << "player: " << pI;
    mp_playerWidget->setPlayer(playerList[pI]);
    foreach(OpponentWidget* w, m_opponentWidgets)
    {
        w->unsetPlayer();
    }
    for (int i = pI + 1; i < playerList.count(); ++i)
    {
        int pos = i - (pI + 1);
        m_opponents[playerList[i].id] = pos;
        m_opponentWidgets[pos]->setPlayer(playerList[i]);
    }
    for (int i = pI - 1; i >= 0; --i)
    {
        int pos = i - pI + 6;
        m_opponents[playerList[i].id] = pos;
        m_opponentWidgets[pos]->setPlayer(playerList[i]);
    }
    if (mp_startButton)
    {
        mp_startButton->hide();
        mp_startButton->deleteLater();
    }

    mp_deck = new DeckWidget(0);
    mp_graveyard = new CardPileWidget(0);
    QBoxLayout* l = new QBoxLayout(QBoxLayout::LeftToRight);
    l->addStretch(3);
    l->addWidget(mp_graveyard);
    l->addStretch(1);
    l->addWidget(mp_deck);
    l->addStretch(3);
    mp_layout->addLayout(l, 1, 1, 2, 2);
    mp_layout->setAlignment(l, Qt::AlignCenter);
    QTimer::singleShot(1, this, SLOT(test()));
}


void Game::test()
{
    new CardMovement(mp_layout->parentWidget(),
                     mp_deck->pop(),
                     mp_graveyard);
}


