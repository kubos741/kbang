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
#ifndef CLIENTCARDLIST_H
#define CLIENTCARDLIST_H

#include <cardpocket.h>
#include <cardwidget.h>

#include <QList>

namespace client {

/**
 * @author MacJariel <MacJariel@gmail.com>
 */
class CardList: public CardPocket
{
Q_OBJECT
public:
    CardList(QWidget *parent, const CardWidget::Size& cardSize);
    virtual ~CardList();

    virtual void push(CardWidget* card);
    virtual QPoint newCardPosition() const;

    virtual CardWidget* get(int id);
    virtual CardWidget* pop();

protected:
    QList<CardWidget*> m_cards;

private:
    CardWidget::Size m_cardSize;
    bool             m_revealed;
    int              m_moveFactor;
    int              m_hPadding, m_vPadding;
};

}

#endif
