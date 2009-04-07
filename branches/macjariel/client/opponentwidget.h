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
#ifndef OPPONENTWIDGET_H
#define OPPONENTWIDGET_H

#include <QWidget>
#include "ui_opponentwidget.h"
#include "playerwidget.h"

#include "parser/parserstructs.h"

namespace client {
class CardList;
class PlayerCharacterWidget;

/**
 * @author MacJariel <MacJariel@gmail.com>
 */
class OpponentWidget: public PlayerWidget, public Ui::OpponentWidget {

public:
    OpponentWidget(QWidget *parent);
    ~OpponentWidget();

    void init();

    inline bool isEmpty() const { return m_id == 0; }
    inline int playerId() const { return m_id; }
    inline QString playerName() const { return m_name; }

    virtual void setFromPublicData(const PublicPlayerData&);
    virtual void setPlayer(const StructPlayer&);
    virtual void unsetPlayer();
    virtual void setActive(uint8_t progress);

    virtual CardList*              hand();
    virtual CardList*              table();
    virtual PlayerCharacterWidget* playerCharacterWidget();

    virtual bool isLocalPlayer() { return 0; }

    virtual QSize sizeHint() const;

private:
    void updateWidgets();

private:
    int m_id;
    QString m_name;
    bool    m_isSheriff;
    QString m_baseStyleSheet;

};
}
#endif
