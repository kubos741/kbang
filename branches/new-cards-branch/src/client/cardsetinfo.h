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

namespace client {

/**
 * The CardSetInfo class provides an information about a CardSet. The referred
 * CardSet can be either local or remote. You can use local CardSetInfo to
 * load cards into CardBank and you can use remote CardSetInfo to display info
 * about availible CardSets and to download them.
 *
 * @todo The downloading of CardSets is currently not implemented.
 * @author MacJariel
 */
class CardSetInfo
{
public:
    /**
     * Constructs a local CardSetInfo that refers to CardSet that is in <i>dir</i>.
     */
    CardSetInfo(QDir dir);

    /**
     * Returns, whether the referred CardSet is local or not.
     */
    bool    isLocal() const         { return m_isLocal; }

    /**
     * Returns the full path to CardSet xml file, or empty string
     * in case of remote CardSet.
     */
    QString cardSetFilePath() const { return m_cardSetFilePath; }

    /**
     * Returns the name of the CardSet.
     */
    QString name() const            { return m_name; }

    /**
     * Returns the name of the slot that CardSet provides.
     */
    QString slot() const            { return m_slot; }

    /**
     * Returns the locale of the CardSet.
     */
    QLocale locale() const          { return m_locale; }

    /**
     * Returns whether CardSet should globally render signs.
     */
    bool    renderSigns() const     { return m_renderSigns; }


private:
    bool    m_isLocal;
    QDir    m_dir;
    QString m_cardSetFilePath;
    QString m_name;
    QString m_slot;
    QLocale m_locale;
    bool    m_renderSigns;

};

}
#endif // CARDSETINFO_H
