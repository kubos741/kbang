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
#ifndef PLAYERCONTROLLERRUNNER_H
#define PLAYERCONTROLLERRUNNER_H

#include <QThread>

class Player;
class AbstractPlayerCtrl;

/**
 * The PlayerControllerRunner class provides a thread for running player controllers
 * (usually AIs). Every instance of Player class has just one PlayerControllerRunner.
 
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class PlayerControllerRunner: public QThread
{
    Q_OBJECT
public:
    PlayerControllerRunner(Player* player);
    ~PlayerControllerRunner();

    void attachPlayerController(AbstractPlayerCtrl* playerController);
    void detachPlayerController();


    /**
     * Events sent to the PlayerControllerRunner are forwarded to PlayerController.
     */
    virtual bool postEventToController(QEvent*);

    virtual void run();
    virtual void start();
    virtual void stop();

private:
    const Player* mp_player;
    AbstractPlayerCtrl* mp_playerController;
};

#endif
