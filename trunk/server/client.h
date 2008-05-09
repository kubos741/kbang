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

#include <QObject>
#include <QXmlStreamReader>
#include <QPair>

class GameServer;
class QTcpSocket;

enum ParsingState
{
    START,
    STREAMIN,
    ANOTHER
};


/**
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Client : public QObject
{
Q_OBJECT
public:
    Client(GameServer* parent, int clientId, QTcpSocket* socket);
    virtual ~Client();


private slots:
    void readData();
    void disconnectFromHost();
    
signals:
    void clientDisconnected(int clientId);

private:
    bool parseStart();

private:
    QTcpSocket* mp_tcpSocket;
    const int m_clientId;    
    QXmlStreamReader m_xml;
    QString m_clientName;
    QPair<int,int> m_protocolVersion;
    ParsingState m_parsingState;
};

#endif
