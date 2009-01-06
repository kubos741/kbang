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
#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QLabel>

namespace client
{

/**
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class CardWidget: public QLabel
{
Q_OBJECT
public:
    typedef enum { SIZE_NORMAL, SIZE_SMALL } Size;

    CardWidget(QWidget *parent = 0);
    ~CardWidget();

    QPoint absPos() const;

    void setCardClass(const QString& cardClassId);
    void setServerCardId(const QString& serverCardId);
    void setCardSize(Size size);
    void applyNewProperties();

    static QSize smallSize();
    static QSize normalSize();
    static QSize bigSize();

private:
    QString m_cardClassId;  /* of Card class */
    QString m_serverCardId; /* for communication with server */
    Size    m_size;
};
}

#endif
