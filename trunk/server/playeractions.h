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
#ifndef PLAYERACTIONS_H
#define PLAYERACTIONS_H

#include <QObject>

class Player;

/**
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class PlayerActions: public QObject {
    Q_OBJECT;
    friend class Player;
protected:
    PlayerActions(Player* player);
    ~PlayerActions();
private:
    PlayerActions(const PlayerActions&);
    PlayerActions& operator=(const PlayerActions&);

public slots:
    void leaveGame() const;
    void sendMessage(const QString& message) const;
    
signals:
    void leaveGameSignal() const;
    void sendMessageSignal(const QString& message) const;

private:
    mutable Player* mp_player;

};

#endif
