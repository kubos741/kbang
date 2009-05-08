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
#include "joingamedialog.h"
#include "serverconnection.h"

#include "parser/queryget.h"
#include "util.h"

using namespace client;

JoinGameDialog::JoinGameDialog(QWidget *parent, ServerConnection* serverConnection)
 : QDialog(parent), mp_serverConnection(serverConnection)
{
    setupUi(this);
    connect(mp_refreshButton, SIGNAL(clicked()),
            this, SLOT(refreshGameList()));
    refreshGameList();
    setButtonsState();
}


JoinGameDialog::~JoinGameDialog()
{
}

void JoinGameDialog::refreshGameList()
{
    QueryGet* query = mp_serverConnection->queryGet();
    connect(query,  SIGNAL(result(const GameInfoListData&)),
            this,   SLOT(recievedGameList(const GameInfoListData&)));
    query->getGameList();
}

void JoinGameDialog::loadGameDetails(int gameId)
{
    QueryGet* query = mp_serverConnection->queryGet();
    connect(query, SIGNAL(result(const GameInfoData&)),
            this, SLOT(recievedGame(const GameInfoData&)));
    query->getGame(gameId);
}


void JoinGameDialog::recievedGameList(const GameInfoListData& gameList)
{
    mp_gameListView->clear();
    foreach(const GameInfoData& gameInfo, gameList)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(mp_gameListView);
        item->setData(0, Qt::UserRole, gameInfo.id);
        item->setText(0, gameInfo.name);
        switch(gameInfo.state) {
        case GAMESTATE_WAITINGFORPLAYERS:
            item->setText(1, "Waiting");
            item->setText(2, QString("%1 / %2").arg(gameInfo.totalPlayersCnt).arg(gameInfo.maxPlayers));
            break;
        case GAMESTATE_PLAYING:
            item->setText(1, "Playing");
            item->setText(2, QString("%1 / %2").arg(gameInfo.alivePlayersCnt).arg(gameInfo.totalPlayersCnt));
            break;
        case GAMESTATE_FINISHED:
            item->setText(1, "Finished");
            item->setText(2, "");
            break;
        default:
            NOT_REACHED();
        }
    }
}

/*
void JoinGameDialog::recievedGameDetails(const StructGame& game, const StructPlayerList& playerList)
{
    mp_playerListView->clear();
    foreach(StructPlayer player, playerList)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(mp_playerListView);;
        item->setText(0, player.name);
    }
}
*/


void JoinGameDialog::show()
{
    refreshGameList();
    QDialog::show();
}

void JoinGameDialog::on_mp_gameListView_itemClicked(QTreeWidgetItem* item, int)
{
    doButtons();
    int gameId = item->data(0, Qt::UserRole).toUInt();
    loadGameDetails(gameId);
}

void JoinGameDialog::setButtonsState()
{
    bool ok = (mp_gameListView->currentItem() == 0);
    mp_playButton->setEnabled(!ok);
    mp_spectateButton->setEnabled(!ok);
}

void JoinGameDialog::on_mp_playButton_clicked()
{
    Q_ASSERT(mp_gameListView->currentItem() != 0);
    int gameId = mp_gameListView->currentItem()->data(0, Qt::UserRole).toUInt();
    QString gameName = mp_gameListView->currentItem()->text(0);
    QString playerName = mp_playerNameEdit->text();
    emit joinGame(gameId, "", playerName); // TODO: gamePassword, playerName
    close();
}

// TODO: SPECTATE
void JoinGameDialog::on_mp_spectateButton_clicked()
{
    Q_ASSERT(mp_gameListView->currentItem() != 0);
    int gameId = mp_gameListView->currentItem()->data(0, Qt::UserRole).toUInt();
    QString gameName = mp_gameListView->currentItem()->text(0);
    emit joinGame(gameId, "", "Player"); // TODO: gamePassword, playerName
    close();
}




