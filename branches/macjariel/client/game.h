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
#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QHash>
#include "parser/parserstructs.h"

class ServerConnection;
class QLayout;
class OpponentWidget;

/**
 * @author MacJariel <MacJariel@gmail.com>
 */
class Game: public QObject {
Q_OBJECT;
public:
    Game(QObject* parent, int gameId, const StructPlayer& player, ServerConnection* serverConnection);

    /* for MainWindow */
    void init();
    void delegateVisualElements(QLayout* opponentsLayout);

    virtual ~Game();

private:
    const int m_playerId;
    const QString m_playerName;
    const int m_gameId;
    ServerConnection* mp_serverConnection;
    QHash<int, OpponentWidget*> m_opponentWidgets;
    
/*  Visual elements - provided by MainWindow */
    QLayout* mp_opponentsLayout;
    

    
public slots:
    void opponentJoinedGame(const StructPlayer& player);
    void opponentLeavedGame(const StructPlayer& player);    
    
    void initialGameStateRecieved(const StructGame&, const StructPlayerList& playerList);
    
    
};

#endif
