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
#include "localplayerwidget.h"
#include "opponentwidget.h"
#include "cardlist.h"
#include "gameeventhandler.h"


#include <QtDebug>
#include <QBoxLayout>

using namespace client;

Game::Game(QObject* parent, int gameId, const StructPlayer& player,
           ServerConnection* serverConnection, const GameWidgets& gameWidgets):
        QObject(parent),
        m_playerId(player.id),
        m_playerName(player.name),
        m_gameId(gameId),
        mp_serverConnection(serverConnection),
        m_currentPlayerId(0),
        m_requestedPlayerId(0),
        mp_mainWidget(gameWidgets.mainWidget),
        mp_middleWidget(gameWidgets.middleWidget),
        m_opponentWidgets(gameWidgets.opponentWidget),
        mp_localPlayerWidget(gameWidgets.localPlayerWidget),
        mp_startButton(0),
        m_creator(0),
        m_cardWidgetFactory(this),
        m_gameObjectClickHandler(this)

{
    m_players[m_playerId] = mp_localPlayerWidget;
    mp_localPlayerWidget->init(&m_gameObjectClickHandler, &m_cardWidgetFactory);
    foreach(OpponentWidget* w, m_opponentWidgets) {
        w->init(&m_gameObjectClickHandler, &m_cardWidgetFactory);
    }
    mp_gameEventHandler = new GameEventHandler(this);
}

void Game::init()
{
    QueryGet* get = mp_serverConnection->queryGet();
    connect(get, SIGNAL(result(const StructGame&, const StructPlayerList&)),
            this, SLOT(initialGameStateRecieved(const StructGame&, const StructPlayerList&)));
    get->getGame(m_gameId);
    if (m_creator)
    {
        mp_startButton = new QPushButton(mp_middleWidget);

   //     mp_middleWidget->layout()->setAlignment(mp_startButton, Qt::AlignCenter);
        QBoxLayout* l = new QBoxLayout(QBoxLayout::LeftToRight);
        mp_startButton->setText(tr("Start game"));
        mp_startButton->setEnabled(0);
        connect(mp_startButton, SIGNAL(clicked()),
                this, SLOT(startButtonClicked()));
        connect(mp_serverConnection, SIGNAL(startableChanged(int, bool)),
                this, SLOT(startableChanged(int, bool)));
                l->addStretch(1);
        l->addWidget(mp_startButton);
        l->addStretch(1);        
        mp_middleWidget->setLayout(l);

    }
    mp_gameEventHandler->connectSlots(mp_serverConnection->parser());

    connect(mp_serverConnection, SIGNAL(gameStarted(const StructGame&, const StructPlayerList&)),
            this, SLOT(gameStarted(const StructGame&, const StructPlayerList&)));



    qDebug("You have entered the game!");

}


Game::~Game()
{

}

void Game::setCurrentPlayerId(int currentPlayerId)
{
    m_currentPlayerId = currentPlayerId;
}

void Game::setRequestedPlayerId(int requestedPlayerId)
{
    m_requestedPlayerId = requestedPlayerId;
}

void Game::setGamePlayState(const GamePlayState& gamePlayState)
{
    m_gamePlayState = gamePlayState;
}

void Game::opponentJoinedGame(const StructPlayer& player)
{
    int i;
    for(i = 0; i < m_opponentWidgets.count(); ++i)
    {
        OpponentWidget* w = m_opponentWidgets[i];
        if (w->isVoid()) {
            w->setPlayer(player);
            m_players[player.id] = w;
            break;
        }
    }
    if (i == m_opponentWidgets.count()) {
        qCritical("Too many players connected to the game.");
    }
    qDebug(qPrintable(QString("[Game]   Player '%1' entered the game!").arg(player.name)));
}

void Game::opponentLeavedGame(const StructPlayer& player)
{
    if (m_players.contains(player.id))
    {
        m_players[player.id]->clear();
        m_players.remove(player.id);
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
            mp_localPlayerWidget->setPlayer(p);
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
    /*
    int pI;
    for(pI = 0; pI < playerList.count(); pI++)
    {
        if (playerList[pI].id == m_playerId) break;
    }
    qDebug() << "player: " << pI;
    //mp_localPlayerWidget->setPlayer(playerList[pI]);
    foreach(OpponentWidget* w, m_opponentWidgets)
    {
        w->clear();
    }
    for (int i = pI + 1; i < playerList.count(); ++i)
    {
        int pos = i - (pI + 1);
        m_players[playerList[i].id] = m_opponentWidgets[pos];
        m_opponentWidgets[pos]->setPlayer(playerList[i]);
    }
    for (int i = pI - 1; i >= 0; --i)
    {
        int pos = i - pI + 6;
        m_players[playerList[i].id] = m_opponentWidgets[pos];
        m_opponentWidgets[pos]->setPlayer(playerList[i]);
    }*/
    if (mp_startButton)
    {
        mp_startButton->hide();
        mp_startButton->deleteLater();
    }

    mp_deck = new DeckWidget(0);
    mp_deck->init(&m_cardWidgetFactory);
    mp_graveyard = new CardPileWidget(0);
    mp_graveyard->setPocketType(POCKET_GRAVEYARD);
    if (mp_middleWidget->layout() != 0) {
        delete mp_middleWidget->layout();
    }

    QBoxLayout* l = new QBoxLayout(QBoxLayout::LeftToRight);
    l->addStretch(3);
    l->addWidget(mp_graveyard);
    l->addStretch(1);
    l->addWidget(mp_deck);
    l->addStretch(3);
    mp_middleWidget->setLayout(l);
}


void Game::assignPlayerWidget(int playerId, PlayerWidget* playerWidget)
{
    m_players[playerId] = playerWidget;
}


void Game::test()
{
/*
    new CardMovement(mp_cardMovementParentWidget,
                     mp_deck->pop(),
                     mp_graveyard);
    new CardMovement(mp_cardMovementParentWidget,
                     mp_deck->pop(),
                     m_opponentWidgets[2]->hand());
  */

}




