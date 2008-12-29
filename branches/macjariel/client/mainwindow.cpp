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
#include "common.h"
#include "mainwindow.h"
#include "connecttoserverdialog.h"
#include "creategamedialog.h"
#include "joingamedialog.h"
#include "logwidget.h"
#include "chatwidget.h"
#include "opponentwidget.h"
#include "playerwidget.h"
#include "parser/queryget.h"
#include "game.h"

#include "card.h"

MainWindow::MainWindow():
    mp_connectToServerDialog(0),
    mp_createGameDialog(0),
    mp_joinGameDialog(0),
    m_serverConnection(this),
    mp_game(0)
{
    setupUi(this);
    Card::loadDefaultRuleset();

    createActions();
    createMenu();
    createStatusBar();
    createWidgets();
    updateActions();


    connect(&m_serverConnection, SIGNAL(statusChanged()),
            this, SLOT(serverConnectionStatusChanged()));
    connect(&m_serverConnection, SIGNAL(playerJoinedGame(int, const StructPlayer&, bool, bool)),
            this, SLOT(playerJoinedGame(int, const StructPlayer&, bool, bool)));
    connect(&m_serverConnection, SIGNAL(playerLeavedGame(int, const StructPlayer&, bool)),
            this, SLOT(playerLeavedGame(int, const StructPlayer&, bool)));

}


MainWindow::~MainWindow()
{
}

void MainWindow::connectToServer()
{
    if (!mp_connectToServerDialog)
    {
        mp_connectToServerDialog = new ConnectToServerDialog(this);
        connect(mp_connectToServerDialog, SIGNAL(connectToServer(QString, int, QString)),
                &m_serverConnection, SLOT(connectToServer(QString, int)));
    }
    mp_connectToServerDialog->show();
}

void MainWindow::disconnectFromServer()
{
    m_serverConnection.disconnectFromServer();
}

void MainWindow::showCreateGameDialog()
{
    if (!mp_createGameDialog)
    {
        mp_createGameDialog = new CreateGameDialog(this);
        connect(mp_createGameDialog,SIGNAL(createGame(const StructGame&, const StructPlayer&)),
                &m_serverConnection, SLOT(createGame(const StructGame&, const StructPlayer&)));
    }
    mp_createGameDialog->show();
}


void MainWindow::showJoinGameDialog()
{
    if (!mp_joinGameDialog)
    {
        mp_joinGameDialog = new JoinGameDialog(this, &m_serverConnection);
        connect(mp_joinGameDialog, SIGNAL(joinGame(int, const QString&, const QString&)),
                &m_serverConnection, SLOT(joinGame(int, const QString&, const QString&)));
    }
    mp_joinGameDialog->show();
}



void MainWindow::createStatusBar()
{
    mp_labelStatusBarServerState = new QLabel;
    serverConnectionStatusChanged();
    statusBar()->addPermanentWidget(mp_labelStatusBarServerState);
}

void MainWindow::serverConnectionStatusChanged()
{
    updateActions();
    if (m_serverConnection.isConnected())
    {
        const QString& serverName = m_serverConnection.serverName();
        const QString& hostName = m_serverConnection.hostName();
        QString text;
        if (serverName.isEmpty())
        {
            text = QString("%0: %1").arg(tr("Connected to server")).arg(hostName);
        }
        else
        {
            text = QString("%0: %1  (%2)").arg(tr("Connected to server")).arg(serverName).arg(hostName);
        }
        mp_labelStatusBarServerState->setText(text);
    } else {
        mp_labelStatusBarServerState->setText(tr("Not connected to server."));
    }
}


void MainWindow::createActions()
{
    connect(mp_actionConnectToServer, SIGNAL(triggered()),
            this, SLOT(connectToServer()));
    connect(mp_actionDisconnectFromServer, SIGNAL(triggered()),
            this, SLOT(disconnectFromServer()));
    connect(actionCreateGame, SIGNAL(triggered()),
            this, SLOT(showCreateGameDialog()));
    connect(mp_actionJoinGame, SIGNAL(triggered()),
            this, SLOT(showJoinGameDialog()));
    connect(mp_actionLeaveGame, SIGNAL(triggered()),
            this, SLOT(leaveGame()));
}

void MainWindow::updateActions()
{
    if (m_serverConnection.isConnected())
    {
        mp_actionConnectToServer->setEnabled(0);
        mp_actionDisconnectFromServer->setEnabled(1);
        if (mp_game != 0)
        {
            actionCreateGame->setEnabled(0);
            mp_actionJoinGame->setEnabled(0);
            mp_actionLeaveGame->setEnabled(1);
        }
        else
        {
            actionCreateGame->setEnabled(1);
            mp_actionJoinGame->setEnabled(1);
            mp_actionLeaveGame->setEnabled(0);
        }
    }
    else
    {
        mp_actionConnectToServer->setEnabled(1);
        mp_actionDisconnectFromServer->setEnabled(0);
        actionCreateGame->setEnabled(0);
        mp_actionJoinGame->setEnabled(0);
        mp_actionLeaveGame->setEnabled(0);
    }
}


void MainWindow::createMenu()
{

}

void MainWindow::createWidgets()
{
    mp_layout = new QGridLayout();
    for(int i = 0; i < 6; ++i)
    {
        OpponentWidget* w = new OpponentWidget(this);
        m_opponentWidgets.append(w);
        switch(i)
        {
        case 0: mp_layout->addWidget(w, 1, 0, 2, 1); break;
        case 1: mp_layout->addWidget(w, 0, 0, 1, 1); break;
        case 2: mp_layout->addWidget(w, 0, 1, 1, 1); break;
        case 3: mp_layout->addWidget(w, 0, 2, 1, 1); break;
        case 4: mp_layout->addWidget(w, 0, 3, 1, 1); break;
        case 5: mp_layout->addWidget(w, 1, 3, 2, 1); break;
        }
        mp_layout->setAlignment(w, Qt::AlignCenter);
    }

    mp_chatWidget = new ChatWidget();
    connect(mp_chatWidget, SIGNAL(outgoingMessage(const QString&)),
            &m_serverConnection, SLOT(sendChatMessage(const QString&)));
    connect(&m_serverConnection, SIGNAL(incomingChatMessage(int, const QString&, const QString&)),
            mp_chatWidget, SLOT(incomingMessage(int, const QString&, const QString&)));

    mp_layout->addWidget(mp_chatWidget, 3, 0, 1, 1);

    mp_logWidget = new LogWidget();
    connect(&m_serverConnection, SIGNAL(logMessage(QString)),
            mp_logWidget, SLOT(appendLogMessage(QString)));
    connect(&m_serverConnection, SIGNAL(incomingData(const QByteArray&)),
            mp_logWidget, SLOT(appendIncomingData(const QByteArray&)));
    connect(&m_serverConnection, SIGNAL(outgoingData(const QByteArray&)),
            mp_logWidget, SLOT(appendOutgoingData(const QByteArray&)));


    mp_layout->addWidget(mp_logWidget, 3, 3, 1, 1);

    mp_playerWidget = new PlayerWidget(this  );
    mp_layout->addWidget(mp_playerWidget, 3, 1, 1, 2);

    Ui::MainWindow::centralWidget->setLayout(mp_layout);
}

void MainWindow::leaveGame()
{
    m_serverConnection.leaveGame();
}

void MainWindow::playerJoinedGame(int gameId, const StructPlayer& player, bool other, bool creator)
{
    if (other == 1)
    {
        Q_ASSERT(mp_game != 0);
        mp_game->opponentJoinedGame(player);
    }
    else
    {
        // PLAYER HAS ENTERED GAME

        Q_ASSERT(mp_game == 0);
        GameWidgets x(mp_layout, mp_playerWidget, m_opponentWidgets);
        mp_game = new Game(this, gameId, player, &m_serverConnection, x);
        mp_game->setCreator(creator);
        mp_game->init();
        updateActions();
    }

}


void MainWindow::playerLeavedGame(int gameId, const StructPlayer& player, bool other)
{
    if (other == 0)
    {
        mp_game->deleteLater();
        mp_game = 0; // MEMORY LEAK JAK CIP - TODO
        updateActions();
    }
    else
    {
        Q_ASSERT(mp_game != 0);
        mp_game->opponentLeavedGame(player);
    }
}





