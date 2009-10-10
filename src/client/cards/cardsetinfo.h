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

#ifndef CARDSETINFO_H
#define CARDSETINFO_H

#include <QDir>
#include <QLocale>
#include <QPoint>

namespace client {

/**
 * The CardSetInfo class provides an information about an installed CardSet.
 *
 * @author MacJariel
 */
class CardSetInfo
{
public:
    /// Constructs a local CardSetInfo that refers to CardSet that is in dir.
    CardSetInfo(const QDir& dir);
  
    /// Returns the id of the CardSet.
    QString id() const              { return m_id; }
    
    /// Returns the name of the CardSet.
    QString name() const            { return m_name; }

    /// Returns the slot it of the CardSet.
    QString slotId() const          { return m_slotId; }
    
    /// Returns the list of locales of the CardSet.
    QList<QLocale> locales() const  { return m_locales; }
    
    /// Returns the revision of the CardSet.
    quint16 revision() const        { return m_revision; }
    
    /// Returns the directory of the CardSet
    QDir dir() const                { return m_dir; }

    /// Returns the full path to CardSet xml file, or empty string
    /// in case of remote CardSet.
    QString cardSetFilePath() const { return m_cardSetFilePath; }

    /// Returns whether CardSet should globally render signs.
    bool renderSigns() const        { return m_renderSigns; }

    /// Returns the origin position for sing rendering.
    QPoint renderSignsPosition() const { return m_renderSignsPosition; }

private:
    bool    m_isLocal;
    QDir    m_dir;
    QString m_cardSetFilePath;
    QString m_id;
    QString m_name;
    QString m_slotId;
    QList<QLocale> m_locales;
    bool    m_renderSigns;
    QPoint  m_renderSignsPosition;
    quint16 m_revision;
};

}
#endif // CARDSETINFO_H
