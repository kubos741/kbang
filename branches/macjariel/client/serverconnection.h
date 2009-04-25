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
#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include "parser/parserstructs.h"
#include <QObject>



/// Forward declarations
class QTcpSocket;

class Parser;

class QueryGet;
namespace client {

/**
 *	@author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class ServerConnection : public QObject
{
Q_OBJECT
public:
    ServerConnection(QObject *parent);
    virtual ~ServerConnection();

    QueryGet* queryGet();
    bool isConnected() const;
    QString serverName() const;
    QString hostName() const;

    QObject* parser() const;

public slots:
    void connectToServer(QString serverHost, int serverPort);
    void disconnectFromServer();

    void createGame(const StructGame&, const StructPlayer&);
    void joinGame(int gameId, const QString& gamePassword, const QString& playerName);
    void leaveGame();
    void startGame();
    void sendChatMessage(const QString& message);


    void drawCard(int numCards = 1, bool revealCard = 0);
    void playCard(int cardId);
    void playCardWithPlayer(int cardId, int playerId);
    void playCardWithCard(int cardId, int otherCardId);

    void endTurn();
    void pass();
    void discardCard(int cardId);




private slots:
    void connected();
    void disconnected();

    void recievedServerInfo(const StructServerInfo&);


private:
    void initializeParserConnections();



private:
    QTcpSocket*         mp_tcpSocket;
    Parser*             mp_parser;

    QString             m_serverHost;
    QString             m_serverName;
    QString             m_serverDescription;

signals:
    void statusChanged();//bool connected, QString serverHost, QString serverName, QString serverDescription);
    void logMessage(QString message);

    void incomingData(const QByteArray&);
    void outgoingData(const QByteArray&);


    void incomingChatMessage(int senderId, const QString& senderName,const QString& message);



    void playerJoinedGame(int gameId, const StructPlayer& player, bool other, bool creator);
    void playerLeavedGame(int gameId, const StructPlayer& player, bool other);
    void startableChanged(int gameId, bool startable);
    void gameStarted(const StructGame&, const StructPlayerList&);
    void eventCardMovement(const CardMovementData&);


};
}
#endif
