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
#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>
#include <QList>

#include "gamestructs.h"

class QTcpSocket;

class Parser;
class QueryGet;

namespace client {

/**
 * The ServerConnection class ... @todo
 * @author MacJariel
 */
class ServerConnection : public QObject
{
Q_OBJECT
public:
    /**
     * Returns a reference to the singleton instance.
     */
    static ServerConnection* instance() {
        static ServerConnection singleton;
        return &singleton;
    }

    /**
     * Returns whether client is connected to a server.
     */
    bool isConnected() const;

    /**
     * Returns the name of the server to which the client is connected.
     */
    QString serverName() const;

    /**
     * Returns the hostname of the server to which the client is connected.
     */
    QString hostName() const;

    /**
     * Returns new QueryGet instance that can be used to send a get query
     * to server.
     */
    QueryGet* newQueryGet();

public slots:
    /**
     * Connects to server.
     * @param serverHost the address/hostname of the server
     * @param serverPort the TCP port on which server listens
     */
    void connectToServer(QString serverHost, int serverPort);

    /**
     * Disconnects from server.
     */
    void disconnectFromServer();

    /**
     * Sends a create-game action to server.
     */
    void createGame(const CreateGameData&, const CreatePlayerData&);

    /**
     * Sends a join-game action to server.
     */
    void joinGame(GameId gameId, PlayerId playerId, const QString& gamePassword, const CreatePlayerData&);

    /**
     * Sends a leave-game action to server.
     */
    void leaveGame();

    /**
     * Sends a start-game action to server.
     */
    void startGame();

    /**
     * Sends a chat-message action to server.
     */
    void sendChatMessage(const QString& message);

    /**
     * Sends a draw-card action.
     */
    void drawCard();

    /**
     * Sends a play-card action.
     */
    void playCard(const ActionPlayCardData&);

    /**
     * Sends a use-ability action.
     */
    void useAbility(const ActionUseAbilityData&);

    /**
     * Sends a end-turn action.
     */
    void endTurn();

    /**
     * Sends a pass action.
     */
    void pass();

    /**
     * Sends a discard-card action.
     */
    void discardCard(CardId cardId);

private slots:
    void onSocketError();
    void onSocketStateChanged();
    void onServerInfoReceived(const ServerInfoData&);


private:
    ServerConnection();
    virtual ~ServerConnection();

    void initializeParserConnections();


private:
    QTcpSocket*         mp_tcpSocket;
    Parser*             mp_parser;

    QString             m_serverHost;
    ServerInfoData      m_serverInfo;

signals:
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


};
}
#endif
