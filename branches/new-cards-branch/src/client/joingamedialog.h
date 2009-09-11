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
#ifndef JOINGAMEDIALOG_H
#define JOINGAMEDIALOG_H

#include <QDialog>
#include "ui_joingamedialog.h"

#include "gamestructs.h"

namespace client {

/**
 * @todo Code revision!
 * @author MacJariel
 */
class JoinGameDialog : public QDialog, public Ui::JoinGameDialog
{
Q_OBJECT
public:
    JoinGameDialog(QWidget *parent);
    ~JoinGameDialog();

    void updateGameListView();
    void updateGameView();

public slots:
    void refreshGameList();
public:
    void refreshGame(GameId gameId);
    void selectGame(GameId gameId);

    virtual void show();


public slots:
    void updateGameList(const GameInfoListData&);
    void updateGame(const GameInfoData&);

    void on_gameListView_itemClicked(QTreeWidgetItem * item, int column);
    void on_playerListView_itemClicked(QTreeWidgetItem * item, int column);
    void on_pushButtonPlay_clicked();
    void on_pushButtonSpectate_clicked();
    void setButtonsState();

signals:
    void joinGame(GameId gameId, PlayerId playerId, const QString& password, const CreatePlayerData&);

private:
    const GameInfoData* gameInfoData(GameId gameId);
    void loadConfigValues();
    void saveConfigValues();

    GameInfoListData            m_gameList;
    GameId                      m_currentGameId;
    PlayerId                    m_currentPlayerId;


};
}
#endif
