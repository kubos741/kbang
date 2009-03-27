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
 * @author MacJariel <MacJariel (at) gmail.com>
 */
class CardWidget: public QLabel
{
Q_OBJECT
public:
    enum Size {
        SIZE_SMALL, SIZE_NORMAL, SIZE_BIG
    };


    CardWidget(QWidget *parent = 0);
    ~CardWidget();

    QPoint absPos() const;

    void setCardClass(const QString& cardClassId);
    void setServerCardId(const QString& serverCardId);
    void setSize(Size size);
    void applyNewProperties();

    inline void setShadowMode()    { m_shadowMode = 1; }
    inline void unsetShadowMode()  { m_shadowMode = 0; }

    inline static QSize smallSize()  { return sm_qsizeSmall;  }
    inline static QSize normalSize() { return sm_qsizeNormal; }
    inline static QSize bigSize()    { return sm_qsizeBig;    }

    inline Size  size()  const { return m_size; }
    inline QSize qsize() const { return m_qsize; }

    static QSize qSize(Size size);

private:
    virtual void paintEvent (QPaintEvent *event);


private:
    const static QSize sm_qsizeSmall, sm_qsizeNormal, sm_qsizeBig;
    QString m_cardClassId;  /* of Card class */
    QString m_serverCardId; /* for communication with server */
    Size    m_size;
    QSize   m_qsize;
    bool    m_shadowMode;
};
}

#endif
