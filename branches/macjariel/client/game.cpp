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

Game::Game(QObject* parent, int gameId, ClientType clientType,
           ServerConnection* serverConnection, const GameWidgets& gameWidgets):
        QObject(parent),
        m_gameId(gameId),
        m_playerId(0),
        m_isCreator(0),
        m_gameState(GAMESTATE_INVALID),
        mp_serverConnection(serverConnection),
        mp_localPlayerWidget(gameWidgets.localPlayerWidget),
        m_opponentWidgets(gameWidgets.opponentWidget),
        mp_mainWidget(gameWidgets.mainWidget),
        mp_middleWidget(gameWidgets.middleWidget),
        mp_startButton(0),
        m_cardWidgetFactory(this),
        m_gameObjectClickHandler(this)

{
    mp_localPlayerWidget->init(&m_gameObjectClickHandler, &m_cardWidgetFactory);
    foreach(OpponentWidget* w, m_opponentWidgets) {
        w->init(&m_gameObjectClickHandler, &m_cardWidgetFactory);
    }
    mp_gameEventHandler = new GameEventHandler(this);
    mp_gameEventHandler->connectSlots(mp_serverConnection->parser());
}

Game::~Game()
{
}


void Game::setPlayerId(int playerId)
{
    m_playerId = playerId;
}

void Game::setGameState(const GameState& gameState)
{
    m_gameState = gameState;
}

void Game::setGameContext(const GameContextData& gameContextData)
{
    m_gameContextData = gameContextData;
}

void Game::setIsCreator(bool isCreator)
{
    m_isCreator = isCreator;
    if (m_gameState != GAMESTATE_WAITINGFORPLAYERS)
        return;
    if (m_isCreator && mp_startButton == 0) {
        mp_startButton = new QPushButton(mp_middleWidget);
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
        return;
    }
    if (!m_isCreator && mp_startButton != 0) {
        mp_startButton->deleteLater();
        mp_startButton = 0;
        mp_middleWidget->layout()->deleteLater();
        return;
    }
}

void Game::playerJoinedGame(const PublicPlayerData& player)
{
    int i;
    for(i = 0; i < m_opponentWidgets.count(); ++i)
    {
        OpponentWidget* w = m_opponentWidgets[i];
        if (w->isVoid()) {
            w->setFromPublicData(player);
            m_players[player.id] = w;
            break;
        }
    }
    if (i == m_opponentWidgets.count()) {
        qCritical("Too many players connected to the game.");
    }
}

void Game::playerLeavedGame(int playerId)
{
    if (m_players.contains(playerId))
    {
        m_players[playerId]->clear();
        m_players.remove(playerId);
    }
}

void Game::startableChanged(bool isStartable)
{
    mp_startButton->setEnabled(isStartable);
}

void Game::startButtonClicked()
{
    disconnect(mp_startButton, SIGNAL(clicked()),
               this, SLOT(startButtonClicked()));
    mp_serverConnection->startGame();
}

//void Game::gameStarted(const StructGame&, const StructPlayerList&)
//{
//    /*
//    int pI;
//    for(pI = 0; pI < playerList.count(); pI++)
//    {
//        if (playerList[pI].id == m_playerId) break;
//    }
//    qDebug() << "player: " << pI;
//    //mp_localPlayerWidget->setPlayer(playerList[pI]);
//    foreach(OpponentWidget* w, m_opponentWidgets)
//    {
//        w->clear();
//    }
//    for (int i = pI + 1; i < playerList.count(); ++i)
//    {
//        int pos = i - (pI + 1);
//        m_players[playerList[i].id] = m_opponentWidgets[pos];
//        m_opponentWidgets[pos]->setPlayer(playerList[i]);
//    }
//    for (int i = pI - 1; i >= 0; --i)
//    {
//        int pos = i - pI + 6;
//        m_players[playerList[i].id] = m_opponentWidgets[pos];
//        m_opponentWidgets[pos]->setPlayer(playerList[i]);
//    }*/
//    if (mp_startButton)
//    {
//        mp_startButton->hide();
//        mp_startButton->deleteLater();
//    }
//
//    mp_deck = new DeckWidget(0);
//    mp_deck->init(&m_cardWidgetFactory);
//    mp_graveyard = new CardPileWidget(0);
//    mp_graveyard->setPocketType(POCKET_GRAVEYARD);
//    mp_selection = new CardList(0);
//    mp_selection->setPocketType(POCKET_SELECTION);
//    mp_selection->setCardSize(CardWidget::SIZE_NORMAL);
//    mp_selection->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//
//
//    if (mp_middleWidget->layout() != 0) {
//        delete mp_middleWidget->layout();
//    }
//
//    QBoxLayout* l = new QBoxLayout(QBoxLayout::LeftToRight);
//    l->addStretch(3);
//    l->addWidget(mp_graveyard);
//    l->addStretch(1);
//    l->addWidget(mp_deck);
//    l->addStretch(3);
//
//    QBoxLayout* l2 = new QBoxLayout(QBoxLayout::LeftToRight);
//    l2->addStretch(3);
//    l2->addWidget(mp_selection);
//    l2->addStretch(3);
//
//    QBoxLayout* l3 = new QVBoxLayout();
//    l3->addLayout(l);
//    l3->addStretch(1);
//    l3->addLayout(l2);
//    mp_middleWidget->setLayout(l3);
//}

CharacterType Game::character() const
{
    return mp_localPlayerWidget->characterWidget()->character();
}


void Game::assignPlayerWidget(int playerId, PlayerWidget* playerWidget)
{
    m_players[playerId] = playerWidget;
}


