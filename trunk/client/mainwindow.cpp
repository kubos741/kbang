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
#include "mainwindow.h"
#include "connecttoserverdialog.h"
#include "joingamedialog.h"
#include "logwidget.h"
#include "chatwidget.h"

MainWindow::MainWindow():
    m_serverConnection(this),
    mp_connectToServerDialog(0),
    mp_joinGameDialog(0)
{
    setupUi(this);
    createActions();
    createMenu();
    createStatusBar();
    createWidgets();
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

void MainWindow::joinGame()
{
    if (!mp_joinGameDialog)
    {
        mp_joinGameDialog = new JoinGameDialog(this, &m_serverConnection);
        // Add some connections
    }
    mp_joinGameDialog->show();
}



void MainWindow::createStatusBar()
{
    mp_labelStatusBarServerState = new QLabel;
    serverConnectionStatusChanged(0, "", "", "");
    statusBar()->addPermanentWidget(mp_labelStatusBarServerState);
}

void MainWindow::serverConnectionStatusChanged(bool connected, QString serverHost, QString serverName, QString serverDescription)
{
    qDebug("D:%s\n", qPrintable(serverName));
    if (connected)
    {
        QString text;
        if (serverName.isEmpty())
        {
            text = QString("%0: %1").arg(tr("Connected to server")).arg(serverHost);
        }
        else
        {
            text = QString("%0: %1(%2)").arg(tr("Connected to server")).arg(serverName).arg(serverHost);
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
    connect(mp_actionJoinGame, SIGNAL(triggered()),
            this, SLOT(joinGame()));
}



void MainWindow::createMenu()
{
    mp_actionDisconnectFromServer->setEnabled(0);
    connect(&m_serverConnection, SIGNAL(statusChanged(bool, QString, QString, QString)),
            mp_actionConnectToServer, SLOT(setDisabled(bool)));
    connect(&m_serverConnection, SIGNAL(statusChanged(bool, QString, QString, QString)),
            mp_actionDisconnectFromServer, SLOT(setEnabled(bool)));
    connect(&m_serverConnection, SIGNAL(statusChanged(bool, QString, QString, QString)),
            mp_actionJoinGame, SLOT(setEnabled(bool)));

}

void MainWindow::createWidgets()
{
    mp_logWidget = new LogWidget();
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(mp_logWidget);
    mp_logFrame->setLayout(layout);
    connect(&m_serverConnection, SIGNAL(logMessage(QString)),
            mp_logWidget, SLOT(appendLogMessage(QString)));
    connect(&m_serverConnection, SIGNAL(incomingXml(QString)),
            mp_logWidget, SLOT(appendIncomingXml(QString)));
    
    
    mp_chatWidget = new ChatWidget();
    layout = new QGridLayout();
    layout->addWidget(mp_chatWidget);
    mp_chatFrame->setLayout(layout);
    
    
}




