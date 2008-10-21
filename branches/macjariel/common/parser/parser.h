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
#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QList>

/**
 * TODO: Write some shiny cool doc comment. :)
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Parser: public QObject
{
Q_OBJECT
public:
    Parser(QObject* parent);
    Parser(QObject* parent, QTcpSocket* socket);
    virtual ~Parser();

     
    //////////////
    /// CLIENT ///
    //////////////
    void initializeStream();
    void queryServerInfo();
    void queryGameList();
    void queryGameInfo(int gameId);
    
    void actionJoinGame(int gameId);
    void actionLeaveGame();


    
public signals:
    void sigResultServerInfo(const StructServerInfo&);
    void sigResultGameList(const StructGameList&);
    void sigResultGameInfo(const StructGame&);
    
    void sigEventJoinGame(int gameId);
    void sigEventLeaveGame();


    //////////////
    /// SERVER ///
    //////////////
    void resultServerInfo(const StructServerInfo&);
    void resultGameList(const StructGameList&);
    void resultGameInfo(const StructGame&);

    void eventJoinGame(int gameId);
    void eventLeaveGame();

public signals:
    void sigQueryServerInfo();
    void sigQueryGameList();
    void sigQueryGameInfo(int gameId);
    
    void sigActionJoinGame(int gameId);
    void sigActionLeaveGame();





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
    void sendChatMessage(int senderId, const QString& senderName, const QString& message);
};

#endif
