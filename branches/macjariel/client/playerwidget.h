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
#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include "parser/parserstructs.h"

namespace client {
class CardList;
class PlayerCharacterWidget;
class CardWidgetFactory;
class GameObjectClickHandler;

/**
 * The PlayerWidget class provides the abstraction for a widget that contains
 * a representation of player properties and state, like his name, his cards, etc.
 *
 * @author MacJariel <MacJariel@gmail.com>
 */
class PlayerWidget: public QWidget {
Q_OBJECT
public:
    PlayerWidget(QWidget* parent);
    virtual ~PlayerWidget() {}

    inline int      id()        const { return m_id; }
    inline QString  name()      const { return m_name; }
    inline bool     isSheriff() const { return m_isSheriff; }
    inline bool     isVoid()    const { return (m_id == 0); }

    virtual void init(GameObjectClickHandler*, CardWidgetFactory*);

    void setPlayer(const StructPlayer&);
    virtual void setFromPublicData(const PublicPlayerData&) = 0;
    virtual void dieAndRevealRole(const PlayerRole& role) = 0;
    virtual void clear() = 0;

    virtual CardList* hand() = 0;
    virtual CardList* table() = 0;
    virtual PlayerCharacterWidget* characterWidget() = 0;

    virtual bool isLocalPlayer() = 0;
    virtual void setActive(uint8_t progress) = 0;

protected:
    void setId(int id);
    void setName(const QString& name);
    void setSheriff(bool isSheriff);

    void mousePressEvent(QMouseEvent *ev);

    GameObjectClickHandler* mp_gameObjectClickHandler;
    CardWidgetFactory*      mp_cardWidgetFactory;

private:
    int         m_id;
    QString     m_name;
    bool        m_isSheriff;

};
}
#endif
