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
#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>

namespace Ui {
class LogWidget;
}

namespace client {

/**
 * The LogWidget class provides a widget that displays the game log. Moreover,
 * this widget can display useful debug information.
 * @author MacJariel
 */
class LogWidget: public QWidget
{
Q_OBJECT
public:
    /**
     * Constructs a LogWidget.
     */
    LogWidget(QWidget* parent = 0);

    /**
     * Destroys the LogWidget.
     */
    ~LogWidget();


    static QString formatServerName(const QString&);

protected:
    virtual void paintEvent(QPaintEvent* event);

public slots:
    void appendLogMessage(QString message);
    void appendIncomingData(const QByteArray& data);
    void appendOutgoingData(const QByteArray& data);

private:
    enum {
        NoData = 0,
        IncomingData,
        OutgoingData
    } m_lastDataType;
    Ui::LogWidget* mp_ui;
};
}
#endif
