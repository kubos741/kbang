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

#include <QObject>
#include "parser/parserstructs.h"

class QTcpSocket;
class QXmlStreamReader;
class QXmlStreamWriter;
class ServerQuery;
class XmlNode;

/**
 *	@author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class ServerConnection : public QObject
{
Q_OBJECT
public:
    ServerConnection(QObject *parent);    
    virtual ~ServerConnection();
    

    ServerQuery* serverQuery(const QString& elementName);


public slots:
    void connectToServer(QString serverHost, int serverPort);
    void disconnectFromServer();
    void joinGame(int gameId, QString gameName, bool spectate, QString password);
    void leaveGame();
    void sendChatMessage(const QString& message);



private slots:
    void connected();
    void disconnected();
    void readData();
    
    
    void recievedServerInfo(const StructServerInfo&);
    void recievedEventJoinGame(int gameId, const StructPlayer&, bool other);
    void recievedEventLeaveGame(XmlNode* node);
    void recievedEventChatMessage(XmlNode* node);

private:
    void processStanza(XmlNode* rootNode);


private:
    QTcpSocket*         mp_tcpSocket;
    QXmlStreamReader*   mp_xmlStreamReader;
    QXmlStreamWriter*   mp_xmlStreamWriter;
    int                 m_depth;
    XmlNode*            mp_rootNode;
    XmlNode*            mp_currentNode;
    
    QString             m_serverHost;
    QString             m_serverName;
    QString             m_serverDescription;
    
signals:
    void statusChanged(bool connected, QString serverHost, QString serverName, QString serverDescription);
    void logMessage(QString message);
    void incomingXml(QString message);
    
    void incomingChatMessage(int senderId, const QString& senderName,const QString& message);

};

#endif
