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
#include "logwidget.h"
#include "serverconnection.h"
#include "ui_logwidget.h"


#include <QPainter>
#include <QPaintEvent>
#include <QtDebug>
#include <QTextDocument>    // Qt::escape()


using namespace client;

LogWidget::LogWidget(QWidget *parent):
        QWidget(parent),
        m_lastDataType(NoData),
        mp_ui(new Ui::LogWidget())
{
    mp_ui->setupUi(this);
    mp_ui->xmlView->setFontPointSize(8);
    connect(ServerConnection::instance(), SIGNAL(incomingData(QByteArray)),
            this, SLOT(appendIncomingData(QByteArray)));
    connect(ServerConnection::instance(), SIGNAL(outgoingData(QByteArray)),
            this, SLOT(appendOutgoingData(QByteArray)));
}

/* virtual */
LogWidget::~LogWidget()
{
}

/* static */ QString
LogWidget::formatServerName(const QString& serverName)
{
    return "<font color=\"blue\">" + Qt::escape(serverName) +
           "</font>";
}

/* virtual */ void
LogWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(event->rect().
                     intersect(contentsRect()), QColor(0, 0, 0, 32));
}


/* slot */ void
LogWidget::appendLogMessage(QString message)
{
    mp_ui->logView->append(message);
}

/* slot */ void
LogWidget::appendIncomingData(const QByteArray& data)
{
    mp_ui->xmlView->moveCursor(QTextCursor::End);
    if (m_lastDataType == OutgoingData) {
        mp_ui->xmlView->insertHtml("<br />");
    }
    if (m_lastDataType != IncomingData) {
        mp_ui->xmlView->setTextColor(Qt::blue);
    }
    mp_ui->xmlView->insertPlainText(data);
    mp_ui->xmlView->moveCursor(QTextCursor::End);
    m_lastDataType = IncomingData;
}

/* slot */ void
LogWidget::appendOutgoingData(const QByteArray& data)
{
    mp_ui->xmlView->moveCursor(QTextCursor::End);
    if (m_lastDataType == IncomingData) {
        mp_ui->xmlView->insertHtml("<br />");
    }
    if (m_lastDataType != OutgoingData) {
        mp_ui->xmlView->setTextColor(Qt::white);
    }
    mp_ui->xmlView->insertPlainText(data);
    mp_ui->xmlView->moveCursor(QTextCursor::End);
    m_lastDataType = OutgoingData;
}
