/***************************************************************************
 *   Copyright (C) 2008-2009 by MacJariel                                  *
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
#ifndef JOINGAMEDIALOG_H
#define JOINGAMEDIALOG_H

#include <QDialog>
#include "gamestructs.h"

class QTreeWidgetItem;

namespace Ui {
    class JoinGameDialog;
}

namespace client {

/**
 * The JoinGameDialog class provides a dialog for listing games on server and
 * joining them.
 * @author MacJariel
 */
class JoinGameDialog: public QDialog
{
Q_OBJECT
public:
    JoinGameDialog(QWidget* parent);
    virtual ~JoinGameDialog();

    virtual void show();

    void setGameList(const GameInfoListData&);

private slots:
    void doClickGameListItem(QTreeWidgetItem*, int column);
    void doClickPlayerListItem(QTreeWidgetItem*, int column);

    void doRefresh();
    void doPlay();
    void doSpectate();

    void updateButtons();

signals:
    void joinGame(ActionDataPtr);

private:
    static QString gameStateDisplayString(GameState);

    void updateGameListView();
    void updateGameView();


    void doJoinGame(bool spectate);

    void loadConfigValues();
    void saveConfigValues();

    GameInfoListData            m_gameList;
    GameId                      m_currentGameId;
    PlayerId                    m_currentPlayerId;
    QueryResultHandler*         mp_handler;
    Ui::JoinGameDialog*         mp_ui;
};
}
#endif
