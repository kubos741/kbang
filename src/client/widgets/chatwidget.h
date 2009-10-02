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
#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

namespace Ui {
class ChatWidget;
}

namespace client
{

/**
 * The ChatWidget class provides a widget that displays incoming chat messages
 * and allows user to write messages.
 * @author MacJariel
 */
class ChatWidget: public QWidget
{
Q_OBJECT
public:
    /**
     * Constructs a ChatWidget instance.
     */
    ChatWidget(QWidget* parent = 0);

    /**
     * Destroys the ChatWidget instance.
     */
    virtual ~ChatWidget();

    /**
     * Paints the background of the ChatWidget.
     */
    virtual void paintEvent(QPaintEvent* event);

    /**
     * Clears the content of the ChatWidget.
     */
    void clear();

public slots:
    /**
     * Appends incoming message to the chat.
     */
    void appendIncomingMessage(int senderId, const QString& senderName, const QString& message);

    /**
     * Sends the message typed in messageBox.
     */
    void sendMessage();

signals:
    /**
     * This signal is emitted when user wants to send a message through the ChatWidget.
     */
    void outgoingMessage(const QString& message);

private:
    Ui::ChatWidget* mp_ui;
};
}
#endif
