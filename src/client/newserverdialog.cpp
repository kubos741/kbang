/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
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

#include "newserverdialog.h"
#include "ui_newserverdialog.h"

using namespace client;

NewServerDialog::NewServerDialog(QWidget* parent):
        QDialog(parent),
        mp_ui(new Ui::NewServerDialog)
{
    mp_ui->setupUi(this);
    mp_ui->spinBoxPort->setMinimum(1);
    mp_ui->spinBoxPort->setMaximum(65535);
    mp_ui->spinBoxPort->setValue(6543);
}

/* virtual */
NewServerDialog::~NewServerDialog()
{
    delete mp_ui;
}

void
NewServerDialog::setupForNewServer()
{
    setWindowTitle(tr("Add Server"));
}

void
NewServerDialog::setupForEditServer(const QString& host, int port)
{
    setWindowTitle(tr("Edit Server"));
    mp_ui->lineEditHost->setText(host);
    mp_ui->spinBoxPort->setValue(port);
}

QString
NewServerDialog::host() const
{
    return mp_ui->lineEditHost->text();
}

int
NewServerDialog::port() const
{
    return mp_ui->spinBoxPort->value();
}
