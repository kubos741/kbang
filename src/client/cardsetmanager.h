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
#ifndef CARDSETMANAGER_H
#define CARDSETMANAGER_H

#include <QObject>
#include <QList>
#include <QStringList>

#include "cardsetinfo.h"

namespace client {

/**
 * The CardSetManager singleton class manages local CardSets.
 * @author MacJariel
 */
class CardSetManager: public QObject
{
public:
    /**
     * Returns a reference to the singleton CardSetManager instance.
     */
    static CardSetManager& instance();


    /**
     * Returns the information about installed card sets.
     */
    inline QList<CardSetInfo> localCardSets() {
        return m_localCardSets;
    }

    /**
     * Appends the <i>slot</i> to the list of known slots.
     */
    void addKnownSlot(QString slot);

    /**
     * Returns the list of known slots.
     */
    QStringList knownSlots() { return m_knownSlots; }

    /**
     * Returns the list of card sets that can be downloaded from server.
     */
    QList<CardSetInfo> remoteCardSets();

private:
    CardSetManager();

private slots:
    /**
     * Reloads the information about installed card sets.
     */
    void refreshLocalCardSets();
    void refreshKnownSlots();

private:
    void saveKnownSlots();

    QList<CardSetInfo>  m_localCardSets;
    QStringList         m_knownSlots;
};

}
#endif // CARDSETMANAGER_H
