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
#include "gamestructs.h"

namespace client
{

/**
 * The CardSetManager singleton class manages local CardSets.
 * @author MacJariel
 */
class CardSetManager: public QObject
{
    Q_OBJECT;
public:
    /**
     * Returns a reference to the singleton CardSetManager instance.
     */
    static CardSetManager& instance();

    /**
     * Appends the <i>slot</i> to the list of known slots.
     */
    void addKnownSlot(QString slot);

    /**
     * Returns the list of known slots.
     */
    QStringList knownSlots() {
        return m_knownSlots;
    }

    static QString slotDisplayName(const QString&);

    /**
     * Returns the information about installed card sets.
     */
    inline QList<CardSetInfo> localCardSets() const {
        return m_localCardSets;
    }

    inline QMap<QString, QString> selectedCardsets() const {
        return m_selectedCardSets;
    }

    /**
     * Returns the list of card sets that can be downloaded from server.
     */
    inline QList<CardSetInfoData> remoteCardSets() const {
        return m_remoteCardSets;
    }

    void updateRemoteCardSets(const CardSetInfoListData&);

    void updateSelectedCardsets(QMap<QString, QString> selectedCardsets);

private:
    CardSetManager();

private slots:
    /**
     * Reloads the information about installed card sets.
     */
    void refreshLocalCardSets();
    void refreshRemoteCardSets();
    void refreshKnownSlots();
    void loadSelectedCardSets();
    void saveSelectedCardSets();

signals:
    void updated();


private:
    void saveKnownSlots();

    QList<CardSetInfo>      m_localCardSets;
    CardSetInfoListData     m_remoteCardSets;
    QStringList             m_knownSlots;
    QMap<QString, QString>  m_selectedCardSets;
    //CardSetInfoListData     m_cardSetInfoListData;
    QueryResultHandler*     mp_handler;
};

}
#endif // CARDSETMANAGER_H
