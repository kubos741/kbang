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
#ifndef LOCALPLAYERWIDGET_H
#define LOCALPLAYERWIDGET_H



#include <QWidget>
#include <ui_localplayerwidget.h>

#include "parser/parserstructs.h"
#include "playerwidget.h"

namespace client {

/**
 * The LocalPlayerWidget instance represent the PlayerWidget that belongs to
 * the local player.
 * @author MacJariel <MacJariel@gmail.com>
 */
class LocalPlayerWidget: public PlayerWidget, public Ui::LocalPlayerWidget
{
Q_OBJECT
public:
    LocalPlayerWidget(QWidget* parent);
    virtual ~LocalPlayerWidget();

    virtual void setPlayer(const StructPlayer&);
    virtual void unsetPlayer();
    virtual bool isLocalPlayer() { return 0; }

private:
    void updateWidgets();

private:
    int     m_id;
    QString m_name;
};
}
#endif
