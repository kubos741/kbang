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
#include "connecttoserverdialog.h"

ConnectToServerDialog::ConnectToServerDialog(QWidget *parent)
 : QDialog(parent)
{
    setupUi(this);
    connect(mp_cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
    

}


ConnectToServerDialog::~ConnectToServerDialog()
{
}

void ConnectToServerDialog::on_mp_buttonSaveFavorite_clicked()
{
    QString profileName = mp_lineEditProfileName->text();
    QString hostName = mp_lineEditHostName->text();
    QString nickName = mp_lineEditNickName->text();
    int port = mp_spinBoxPort->value();
    QList<QTreeWidgetItem *> results = mp_favoriteList->findItems(profileName, Qt::MatchExactly);
    if (results.size() == 0)
    {
        QStringList strings;
        strings << profileName << hostName << QString(port) << nickName;
        mp_favoriteList->addTopLevelItem(new QTreeWidgetItem(mp_favoriteList, strings));
    }
    else
    {
        foreach (QTreeWidgetItem* result , results)
        {
            result->setText(1, hostName);
            result->setText(2, QString::number(port));
            result->setText(3, nickName);
        }
    }

}

void ConnectToServerDialog::on_mp_favoriteList_itemClicked(QTreeWidgetItem * item, int)
{
    mp_lineEditProfileName->setText(item->text(0));
    mp_lineEditHostName->setText(item->text(1));
    mp_spinBoxPort->setValue(item->text(2).toInt());
    mp_lineEditNickName->setText(item->text(3));

}




