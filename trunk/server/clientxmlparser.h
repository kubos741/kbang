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
#ifndef CLIENTXMLPARSER_H
#define CLIENTXMLPARSER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class QTcpSocket;
class Client;
class Stanza;



/**
 * The ClientXmlParser class takes care of the TcpSocket, parses incoming
 * data and forms xml data for sending back to TcpSocket. This class
 * is a part of the Client class, thus each Client and only each Client
 * has just one instance of the ClientXmlParser class.
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class ClientXmlParser : public QObject
{
Q_OBJECT
public:
    /**
     * Constructs an instance of ClientXmlParser class.
     * @param client becomes parent of the instance
     * @param socket is the TCP socket of the connection
     */
    ClientXmlParser(Client* client, QTcpSocket* socket);
    
    /**
     * Destroys instance.
     */
    virtual ~ClientXmlParser();
    

signals:
    /**
     * This signal is emitted when the other party disconnects
     * from the server.
     */
    void disconnected();
  
  
private slots:
    /**
     * This method is called either manually to force disconnection from
     * the other party or it is called as slot when the other party disconnects
     * from server. 
     */
    void disconnectFromHost();
    
    
    /**
     * Reads and parses data from the input stream.
     */
    void readData();


private:
    void parseStream();
    void parseStanza();
    void sendData(const QString& data);

private:
    QXmlStreamReader m_xmlIn;
    QXmlStreamWriter m_xmlOut;
    QTcpSocket* mp_socket;
    Client* mp_client;

    int m_depth;
    bool m_inStreamInitialized;
    bool m_outStreamInitialized;
    Stanza* mp_stanza;
    struct { quint16 major, minor; } m_protocolVersion;


public slots:
    void sendJoinGame(int gameId, int type);
    void sendLeaveGame();

};

#endif
