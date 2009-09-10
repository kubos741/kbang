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
#ifndef CARDWIDGETSIZEMANAGER_H
#define CARDWIDGETSIZEMANAGER_H

#include <QObject>
#include <QSize>
#include <QMap>

#include "clienttypes.h"

class QWidget;

namespace client
{

/**
 * The ClassWidgetSizeManager singleton class manages the size of CardWidgets.
 * @author MacJariel
 */
class CardWidgetSizeManager : public QObject {
Q_OBJECT
public:
    /**
     * Returns a reference to the singleton CardWidgetSizeManager instance.
     */
    static inline CardWidgetSizeManager& instance() {
        static CardWidgetSizeManager singleton;
        return singleton;
    }

    /**
     * Returns the size of CardWidget for given CardSizeRole.
     */
    QSize cardSize(CardSizeRole) const;

    /**
     * Returns the y coordinate of character card to mark given <i>livePoints</i>.
     * @note This value should be stored in CardSets in the future.
     */
    int lifeLevel(int lifePoints) const;

signals:
    /**
     * This signal is emitted when card size is changed. Each CardWidget (and
     * widgets that use CardWidget size to compute its own size) should connect
     * to this signal.
     */
    void cardSizeChanged();

private:
    CardWidgetSizeManager();
    int width(int height);

    QMap<CardSizeRole, QSize> m_sizes;

    static qreal sm_cardRatio;
    static qreal sm_lifePointCardRatio[];
    static int sm_initialHeight;
};

}
#endif // CARDWIDGETSIZEMANAGER_H
