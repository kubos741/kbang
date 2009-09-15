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
#ifndef SELECTAVATARWIDGET_H
#define SELECTAVATARWIDGET_H

#include <QLabel>
#include <QImage>

namespace client {
/**
 * The SelectAvatarWidget class provides a widget that displays player's
 * avatar and allows user to change it by clicking on it.
 */
class SelectAvatarWidget: public QLabel
{
public:
    /**
     * Constructs a SelectAvatarWidget.
     */
    SelectAvatarWidget(QWidget* parent);

    /**
     * Destroys the SelectAvatarWidget.
     */
    virtual ~SelectAvatarWidget();

    /**
     * Returns path to the selected avatar.
     */
    QString avatarFilePath() const;

    /**
     * Returns the selected avatar.
     */
    QImage avatar() const;

    /**
     * Loads avatar from file specified by <i>filePath</i>.
     */
    void loadAvatar(const QString& filePath);

    /**
     * Unloads the current avatar.
     */
    void unloadAvatar();

protected:
    virtual void mousePressEvent(QMouseEvent* ev);

private:
    QString m_avatarFilePath;
    QImage  m_avatar;
};
}

#endif // SELECTAVATARWIDGET_H
