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
#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QtCore>

class GameState;
class Client;
class TcpServer;

/**
 * The GameServer class is a singleton class that represent the state of the whole
 * server. It holds all the clients and games created on the server.
 * It represents the state of the server and holds some attributes such as
 * server name, description, etc.
 * @author MacJariel <macjariel@users.sourceforge.net>
 */

class GameServer: public QObject
{
    Q_OBJECT

    GameServer();

public:
    /**
     * The singleton object accessor.
     */
    static inline GameServer& instance()
    {
        if (!sm_instance) sm_instance = new GameServer();

        return *sm_instance;
    }

    /**
     * Creates a new game.
     * @returns a pointer to GameArbiter.
     */
    QPointer<GameState> createGame(const Client& creator, int maxPlayers, int AIPlayers);


/* SETTERS AND GETTERS */
    void setName(const QString& theValue)
    {
        m_name = theValue;
    }


    QString name() const
    {
        return m_name;
    }

    void setDescription(const QString& theValue)
    {
        m_description = theValue;
    }


    QString description() const
    {
        return m_description;
    }

    bool listen();

    void exit();
    
signals:
    void aboutToQuit();
    
public slots:
    void createClient();
    void deleteClient(int clientId);

private:
    static GameServer* sm_instance;
    QList<QPointer<GameState> > m_games;
    QHash<int, QPointer<Client> > m_clients;
    int m_nextClientId;
    QString m_name;
    QString m_description;
    TcpServer* mp_tcpServer;

};

#endif
