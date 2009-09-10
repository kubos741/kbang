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


#include <QApplication>         // To obtain application name/version
#include "aboutdialog.h"        // AboutDialog header file
#include "parser/parser.h"      // To obtain the protocol version
#include "ui_aboutdialog.h"     // AboutDialog generated UI file

using namespace client;

AboutDialog::AboutDialog(QWidget* parent):
        QDialog(parent),
        mp_ui(new Ui::AboutDialog)
{
    mp_ui->setupUi(this);
    mp_ui->labelAppName->setText(QApplication::instance()->applicationName());
    mp_ui->labelAppVersion->setText(QString("Version: %1").arg(
            QApplication::instance()->applicationVersion()));
    mp_ui->labelProtocolVersion->setText(QString("Protocol version: %1").arg(Parser::protocolVersion()));
}

AboutDialog::~AboutDialog()
{
    delete mp_ui;
}

/* virtual */ void
AboutDialog::changeEvent(QEvent* e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        mp_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
