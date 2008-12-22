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
#ifndef CLIENT_H
#define CLIENT_H

#include "parser/parser.h"

#include "player.h"
#include "cards.h"

#include <QObject>
#include <QPair>


class GameServer;
class QTcpSocket;


/**
 * NOTE: There cannot be a client with id = 0.
 *
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Client : public QObject
{
Q_OBJECT
public:
    Client(GameServer* parent, int clientId, QTcpSocket* socket);
    virtual ~Client();

    inline int id() const;

signals:
    void disconnected(int clientId);


public slots: // These slots are connected to parser
    void actionCreateGame(const StructGame& game, const StructPlayer& player);
    void actionJoinGame(int gameId, const StructPlayer& player);
    void actionLeaveGame();
    void actionStartGame();

public slots: // These slots are connected to player/game
    void leavingGame(int gameId, const StructPlayer& player);
    void playerDrawedCard(Player*, CardAbstract*);

private:
    void joinGame(Game*, const StructPlayer&);

private:
    const int           m_id;
    Parser*             mp_parser;
    Player*             mp_player;

    void connectPlayer();
    void disconnectPlayer();

};

#endif
