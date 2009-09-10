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
#include "gamestructs.h"

namespace client
{

/**
 * The CardWidget class represents a visual element that displays the face
 * (or back) of a card.
 * @author MacJariel <MacJariel (at) gmail.com>
 */
class CardWidget: public QLabel
{
Q_OBJECT
public:
    CardWidget(QWidget *parent);
    ~CardWidget();

    inline const CardData&  cardData()      const { return m_cardData;   }
    inline CardData&        cardData()            { return m_cardData;   }
    inline PocketType       pocketType()    const { return m_pocketType; }
    inline PlayerId         ownerId()       const { return m_ownerId; }
    inline CardSizeRole     cardSizeRole()  const { return m_cardSizeRole; }
    inline bool             hasHighlight()  const { return m_hasHighlight; }

    QPoint center() const;

    void clone(CardWidget*);
    void clear();

    void setCardData(const CardData&);
    void setPocketType(const PocketType&);
    void setOwnerId(PlayerId ownerId);
    void setCardSizeRole(CardSizeRole cardSizeRole);
    void setHighlight(bool highlight);

    void setPlayerRoleCard(PlayerRole);
    void setCharacterCard(QString character = QString());

public slots:
    void updatePixmap();

protected:
    virtual void mousePressEvent(QMouseEvent *ev);

private:
    virtual void paintEvent (QPaintEvent *event);

    CardData        m_cardData;
    PocketType      m_pocketType;
    PlayerId        m_ownerId;
    CardSizeRole    m_cardSizeRole;
    bool            m_hasHighlight;
};
}

#endif
