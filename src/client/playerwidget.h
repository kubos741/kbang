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
#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>                  // inheritance
#include <QPixmap>                  // composition
#include "gametypes.h"              // typedefs and enums
#include "gamestructs.h"            // QList<CardData>

class QLabel;

namespace client {

class CardListWidget;
class CardWidget;
class CharacterWidget;
class Game;
class GameActionManager;

/**
 * The PlayerWidget class provides common base class for opponents' widgets
 * and local player widget.
 *
 * @author MacJariel
 */
class PlayerWidget: public QWidget {
Q_OBJECT
protected:
    /**
     * Constructs a PlayerWidget instance.
     */
    PlayerWidget(QWidget* parent);

    /**
     * Destroys the PlayerWidget instance.
     */
    virtual ~PlayerWidget();

public:

    inline PlayerId     id()        const { return m_id;            }
    inline QString      name()      const { return m_name;          }
    inline bool         isAI()      const { return m_isAI;          }
    inline bool         isAlive()   const { return m_isAlive;       }
    inline bool         isSheriff() const { return m_isSheriff;     }
    inline bool         isWinner()  const { return m_isWinner;      }
    inline bool         isVoid()    const { return (m_id == 0);     }
    inline PlayerRole   role()      const { return m_playerRole;    }

    /**
     * Sets the state of the instance to the default clear state.
     */
    virtual void clear();

    void setCurrent(bool);
    void setRequested(bool);

    void setFromPublicData(const PublicPlayerData&);   
    void dieAndRevealRole(PlayerRole);

    virtual CardListWidget* hand() = 0;
    virtual CardListWidget* table() = 0;
    virtual CharacterWidget* characterWidget() = 0;
    virtual QLabel* avatarLabel() = 0;
    virtual QLabel* playerNameLabel() = 0;
    virtual bool isLocalPlayer() = 0;
    virtual void moveWinnerIcon() = 0;


protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);

    GameActionManager* gameActionManager() const;

    virtual void setRoleFromPublicData(PlayerRole);
    virtual void setHandSize(int handSize);
    virtual void setTable(QList<CardData>);
    virtual void updateWidgets();

    void updateAvatarLabel();
    void createWinnerIcon();
    void updateWinnerIcon();

    PlayerId                m_id;
    QString                 m_name;
    bool                    m_hasController;
    bool                    m_isAI;
    bool                    m_isAlive;
    bool                    m_isSheriff;
    bool                    m_isWinner;
    bool                    m_isCurrent;
    bool                    m_isRequested;

    QPixmap                 m_avatar;
    PlayerRole              m_playerRole;
    QLabel*                 mp_winnerIcon;
    Game*                   mp_game;
};
}
#endif
