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
#include "serverquery.h"
#include "xmlnode.h"

JoinGameDialog::JoinGameDialog(QWidget *parent, ServerConnection* serverConnection)
 : QDialog(parent), mp_serverConnection(serverConnection)
{
    setupUi(this);
    connect(mp_refreshButton, SIGNAL(clicked()),
            this, SLOT(refreshGameList()));
    refreshGameList();
    doButtons();
}


JoinGameDialog::~JoinGameDialog()
{
}

void JoinGameDialog::refreshGameList()
{
    ServerQuery* serverQuery = mp_serverConnection->serverQuery("gamelist");
    connect(serverQuery, SIGNAL(responseRecieved(XmlNode*)),
            this, SLOT(recievedGameList(XmlNode*)));
    serverQuery->post();
}

void JoinGameDialog::loadGameDetails(int gameId)
{
    ServerQuery* serverQuery = mp_serverConnection->serverQuery("game");
    serverQuery->addAttribute("id", QString::number(gameId));
    connect(serverQuery, SIGNAL(responseRecieved(XmlNode*)),
            this, SLOT(recievedGameDetails(XmlNode*)));
    serverQuery->post();
}

void JoinGameDialog::recievedGameList(XmlNode* node)
{
    XmlNode* gameListNode = node->getFirstChild();
    if (gameListNode && gameListNode->name() == "gamelist")
    {
        mp_gameListView->clear();
        foreach(XmlNode* gameNode, gameListNode->getChildren())
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(mp_gameListView);
            item->setData(0, Qt::UserRole, gameNode->attribute("id").toUInt());
            item->setText(0, gameNode->attribute("name"));
            item->setText(1, "TODO");
            item->setText(2, QString("%1 - %2").arg(gameNode->attribute("minPlayers"))
                                               .arg(gameNode->attribute("maxPlayers")));
        }
    }
    delete node;
}

void JoinGameDialog::recievedGameDetails(XmlNode* node)
{
    XmlNode* gameNode = node->getFirstChild();
    if (gameNode && gameNode->name() == "game")
    {
        XmlNode* playersNode = gameNode->getFirstChild();
        if (playersNode && playersNode->name() == "players")
        {
            mp_playerListView->clear();
            foreach(XmlNode* playerNode, playersNode->getChildren())
            {
                if (!playerNode || playerNode->name() != "player") continue;
                QTreeWidgetItem* item = new QTreeWidgetItem(mp_playerListView);;
                item->setText(0, playerNode->attribute("name"));
            }
        }
    }
    delete node;
}


void JoinGameDialog::show()
{        
    refreshGameList();
    QDialog::show();
}

void JoinGameDialog::on_mp_gameListView_itemClicked(QTreeWidgetItem* item, int column)
{
    doButtons();
    int gameId = item->data(0, Qt::UserRole).toUInt();
    loadGameDetails(gameId);
}

void JoinGameDialog::doButtons()
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
    emit joinGame(gameId, gameName, 0, ""); // TODO PASSWORD
    close();
}

void JoinGameDialog::on_mp_spectateButton_clicked()
{
    Q_ASSERT(mp_gameListView->currentItem() != 0);
    int gameId = mp_gameListView->currentItem()->data(0, Qt::UserRole).toUInt();
    QString gameName = mp_gameListView->currentItem()->text(0);
    emit joinGame(gameId, gameName, 1, ""); // TODO PASSWORD
    close();
}




