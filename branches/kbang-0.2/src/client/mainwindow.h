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

#include <QMainWindow>
#include <QList>

#include "gametypes.h"

namespace Ui {
class MainWindow;
}

namespace client {

// Dialogs:
class ConnectToServerDialog;
class CreateGameDialog;
class JoinGameDialog;
class AboutDialog;
class OptionsDialog;

// Widgets:
class PlayerWidget;
class LocalPlayerWidget;
class LogWidget;

/**
 * The MainWindow singleton class represents the main window of the KBang
 * client.
 */
class MainWindow: public QMainWindow

{
Q_OBJECT
public:
    /**
     * Constructs the MainWindow instance.
     */
    MainWindow();

    /**
     * Destroys the MainWindow instance.
     */
    virtual ~MainWindow();

    /**
     * Returns a reference to the MainWindow singleton instance.
     */
    inline static MainWindow* instance() {
        return smp_singleton;
    }

    /**
     * Returns the LocalPlayerWidget.
     */
    LocalPlayerWidget* localPlayerWidget() const;

    /**
     * Returns the list of OpponentWidget instances.
     */
    QList<PlayerWidget*> opponentWidgets() const { return m_opponentWidgets; }

    /**
     * Returns a pointer to the middle widget.
     */
    QWidget* middleWidget() const;

    /**
     * Returns a pointer to LogWidget.
     */
    LogWidget* logWidget() const;

public slots:
    void test();

    /**
     * Shows the ConnectToServerDialog.
     */
    void showConnectToServerDialog();

    /**
     * Shows the CreateGameDialog.
     */
    void showCreateGameDialog();

    /**
     * Shows the JoinGameDialog.
     */
    void showJoinGameDialog();

    /**
     * Shows the AboutDialog.
     */
    void showAboutDialog();
    
    void showOptionsDialog();

    /**
     * Shows a dialog with warning message. This method doesn't block the thread,
     * instead schedules showing modal dialog window.
     */
    void showWarningMessage(const QString& message);

    void enterGameMode(GameId gameId, const QString& gameName, ClientType);
    void exitGameMode();

    void serverConnectionStatusChanged();

protected:
    virtual void paintEvent(QPaintEvent* event);


private:
    void createActions();
    void createWidgets();
    void updateActions();

    ConnectToServerDialog* mp_connectToServerDialog;
    CreateGameDialog*      mp_createGameDialog;
    JoinGameDialog*        mp_joinGameDialog;
    AboutDialog*           mp_aboutDialog;
    OptionsDialog*         mp_optionsDialog;

    QList<PlayerWidget*>   m_opponentWidgets;

    Ui::MainWindow*        mp_ui;
    static MainWindow*     smp_singleton;
};
}
#endif
