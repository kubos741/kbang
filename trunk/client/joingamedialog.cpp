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
    refreshGameList();
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


void JoinGameDialog::recievedGameList(XmlNode* node)
{
    XmlNode* gameListNode = node->getFirstChild();
    if (gameListNode && gameListNode->name() == "gamelist")
    {
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
}

void JoinGameDialog::show()
{
    refreshGameList();
    QDialog::show();
}

void JoinGameDialog::on_mp_gameListView_itemClicked(QTreeWidgetItem* item, int column)
{

}

void JoinGameDialog::on_mp_gameListView_itemDoubleClicked(QTreeWidgetItem * item, int column)
{

}


