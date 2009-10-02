/***************************************************************************
 *   Copyright (C) 2008-2009 by MacJariel                                  *
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
#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include "gametypes.h"

#include <QObject>
#include <QString>
#include <QList>

class QTcpSocket;

class Parser;
class ServerInfoData;


namespace client {

/**
 * The ServerConnection singleton class provides a singleton class for
 * interaction with server.
 * @author MacJariel
 */
class ServerConnection: public QObject
{
Q_OBJECT
public:
    /**
     * Returns a reference to the singleton instance.
     * @warning The returned pointer is invalid after MainWindow's destructor
     * was called.
     */
    static ServerConnection* instance() {
        if (!smp_instance) {
            smp_instance = new ServerConnection();
        }
        return smp_instance;
    }

    /**
     * Returns whether client is connected to a server.
     */
    inline bool isConnected() const {
        return mp_parser != 0;
    }

    /**
     * Returns the name of the server to which the client is connected.
     */
    QString serverName() const;

    /**
     * Returns the hostname of the server to which the client is connected.
     */
    inline QString hostName() const {
        return m_serverHost;
    }

    void connectToServer(const QString& serverHost, int serverPort);

    void disconnectFromServer();

    void sendQueryGet(const QueryGetPtr&, QueryResultHandler*);

    void cancelQueryGet(QueryResultHandler*);

    void sendAction(const ActionDataPtr&);


signals:
    /**
     * This signal is emitted after a game event is received. The gameEvent
     * parameter describes the received game event.
     */
    void gameEventReceived(const GameEventDataPtr& gameEvent);

    /**
     * This signal is emitted after a server event is received. The serverEvent
     * parameter describes the received server event.
     */
    void serverEventReceived(const ServerEventDataPtr& serverEvent);

    /**
     * This signal is emitted after client receives data from server.
     * It can be used for debugging purposes.
     */
    void incomingData(const QByteArray&);

    /**
     * This signal is emitted after client sends data to server.
     * It can be used for debugging purposes.
     */
    void outgoingData(const QByteArray&);

private slots:
    // callbacks from parser:
    void onStreamOpened();
    void onStreamClosed();
    void onParserError();

    // callbacks from socket
    void onSocketStateChanged();
    void onSocketError();

private:
    ServerConnection();
    virtual ~ServerConnection();

    class QueryHandler;
    friend class QueryHandler;

    QueryHandler*       mp_handler;
    QTcpSocket*         mp_tcpSocket;
    Parser*             mp_parser;
    QString             m_serverHost;
    ServerInfoData*     mp_serverInfo;

    static ServerConnection* smp_instance;
};
}
#endif
