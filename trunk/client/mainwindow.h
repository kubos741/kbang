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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "serverconnection.h"


class ConnectToServerDialog;
class JoinGameDialog;
class LogWidget;
class ChatWidget;
class QLabel;

/**
 *@author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class MainWindow : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();
    
private slots:
    void connectToServer();
    void disconnectFromServer();
    void joinGame();
    void leaveGame();
    
    void serverConnectionStatusChanged(bool connected, QString serverHost, QString serverName, QString serverDescription);

private:
    ConnectToServerDialog* mp_connectToServerDialog;
    JoinGameDialog*        mp_joinGameDialog;
    LogWidget*             mp_logWidget;
    ChatWidget*            mp_chatWidget;
    ServerConnection       m_serverConnection;
    
    
    QLabel*                mp_labelStatusBarServerState;


private:
    void createStatusBar();
    void createMenu();
    void createActions();
    void createWidgets();

};

#endif
