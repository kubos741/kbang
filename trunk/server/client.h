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

#include "clientxmlparser.h"

#include "player.h"


#include <QObject>
#include <QPair>


class GameServer;
class QTcpSocket;
class QXmlStreamWriter;
class AbstractPlayerCtrl;
class ClientPlayerCtrl;
class ClientController;


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

    friend class Player;

    inline int id() const
    {
        return m_clientId;
    }
    Player* player();
    ClientController* clientController() const;
    AbstractPlayerCtrl* playerController() const;
    void setPlayer(Player* player);
    void postEventToController(QEvent* event);

signals:
    void disconnected(int clientId);

private:

    const int           m_clientId;
    ClientXmlParser     m_xmlParser;
    ClientController*   mp_clientController;
    QString             m_clientName;
    QPair<int,int>      m_protocolVersion;
    ClientPlayerCtrl*   mp_clientPlayerCtrl;
    Player*             mp_player;

    // STATE REPRESENTATION:
    // m_gameId =  0 => client is not connected to a game
    // m_gameId != 0 => client is connected to the game
    //    int m_gameId;

public:
    bool isInGame() const;




public:
    /**
     * Writes the xml output about this client.
     */
    void writeXml(QXmlStreamWriter&);
};

#endif
