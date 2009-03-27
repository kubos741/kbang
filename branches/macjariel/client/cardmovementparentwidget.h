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

#ifndef CARDMOVEMENTPARENTWIDGET_H
#define CARDMOVEMENTPARENTWIDGET_H



#include <QWidget>
#include "cardmovement.h"

namespace client
{


class CardMovementParentWidget : public QWidget
{
public:
    CardMovementParentWidget(QWidget* parent = 0): QWidget(parent) {}
    //void addCardMovement(QPointer<CardMovement> cardMovement);
    //virtual void paintEvent (QPaintEvent *event);

private:
    QList<QPointer<CardMovement> > m_movementsList;

};


}
#endif // CARDMOVEMENTPARENTWIDGET_H
