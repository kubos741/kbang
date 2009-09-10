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

#include "chatwidget.h"
#include "ui_chatwidget.h"

#include <QPainter>
#include <QPaintEvent>

using namespace client;

ChatWidget::ChatWidget(QWidget *parent):
        QWidget(parent),
        mp_ui(new Ui::ChatWidget)
{
    mp_ui->setupUi(this);
    setContentsMargins(5, 5, 5, 5);
    mp_ui->chatView->setFocusPolicy(Qt::ClickFocus);
    mp_ui->messageBox->setFocusPolicy(Qt::ClickFocus);
    connect(mp_ui->messageBox, SIGNAL(returnPressed()),
            this, SLOT(sendMessage()));
}

/* virtual */
ChatWidget::~ChatWidget()
{
}

/* virtual */ void
ChatWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(event->rect().intersect(contentsRect()), QColor(0, 0, 0, 32));
}

void
ChatWidget::clear()
{
    mp_ui->chatView->clear();
}

void
ChatWidget::appendIncomingMessage(int, const QString& senderName, const QString& message)
{
    mp_ui->chatView->append(QString("<b>%1:</b> %2").arg(Qt::escape(senderName)).arg(Qt::escape(message)));
}

void
ChatWidget::sendMessage()
{
    const QString& message = mp_ui->messageBox->text();
    mp_ui->messageBox->clear();
    emit outgoingMessage(message);
}
