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

#include "selectavatarwidget.h"
#include <QMouseEvent>
#include <QFileDialog>

using namespace client;

QSize iconSize(64, 64);

SelectAvatarWidget::SelectAvatarWidget(QWidget* parent)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setLineWidth(1);
    setFixedSize(iconSize.width() + 4, iconSize.height() + 4);
}

/* virtual */
SelectAvatarWidget::~SelectAvatarWidget()
{
}

QString
SelectAvatarWidget::avatarFilePath() const
{
    return m_avatarFilePath;
}

QImage
SelectAvatarWidget::avatar() const
{
    return m_avatar;
}

void
SelectAvatarWidget::loadAvatar(const QString& filePath)
{
    if (filePath.isEmpty()) {
        unloadAvatar();
        return;
    }
    if (!QFile::exists(filePath)) {
        qWarning(qPrintable(QString("Cannot load avatar from '%1': file not found").arg(filePath)));
        unloadAvatar();
        return;
    }
    QImage avatar;
    if (!avatar.load(filePath)) {
        qWarning(qPrintable(QString("Cannot load avatar from '%1': unknown format").arg(filePath)));
        unloadAvatar();
        return;
    }
    m_avatar = avatar.scaled(iconSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_avatarFilePath = filePath;
    setPixmap(QPixmap::fromImage(m_avatar));
}

void
SelectAvatarWidget::unloadAvatar()
{
    m_avatarFilePath.clear();
    m_avatar = QImage();
    setPixmap(QPixmap());
}

void
SelectAvatarWidget::mousePressEvent(QMouseEvent* ev)
{
    if (ev->button() == Qt::LeftButton) {
        loadAvatar(QFileDialog::getOpenFileName(this,
            tr("Open Image"), m_avatarFilePath, tr("Image Files %1").
            arg("(*.png *.jpg *.gif)")));
    }
}
