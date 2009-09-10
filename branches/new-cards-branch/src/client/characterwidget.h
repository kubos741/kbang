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
#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>

#include "cardwidget.h"

namespace client {


/**
 * The CharacterWidget class provides a widget to show player's character
 * card and to show his lifepoints.
 * @author MacJariel
 */
class CharacterWidget: public QWidget
{
Q_OBJECT
public:
    /**
     * Constructs a clean CharacterWidget instance.
     */
    CharacterWidget(QWidget *parent = 0);

    /**
     * Destroys the instance.
     */
    virtual ~CharacterWidget();

    /**
     * Returns the character of this character widget.
     */
    inline QString character() const    { return m_character; }

    /**
     * Returns the life points of this character widget.
     */
    inline int     lifePoints() const   { return m_lifePoints; }

    /**
     * Sets the ownerId of this CharacterWidget.
     */
    void setOwnerId(PlayerId ownerId);

    /**
     * Sets the character of this CharacterWidget.
     */
    void setCharacter(const QString& character);

    /**
     * Sets the life points of this CharacterWidget. If life points
     * changes, an animation is started and animationFinished() signal
     * is emitted when the animation finishes.
     */
    void setLifePoints(int lifePoints);

private:
    void startAnimation();

public slots:
    void updateWidgetSize();
    void onAnimationTimeout();

signals:
    void animationFinished();

private:
    QString m_character;
    int     m_lifePoints;
    int     m_sourceY;
    int     m_targetY;

    CardWidget* mp_backCard;
    CardWidget* mp_characterCard;

    bool          m_isAnimating;

    static QTimer sm_timer;
    static int    sm_countAnimaton;
    QTime         m_time;
};

}
#endif
