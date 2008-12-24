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
#include <QHash>
#include "parserstructs.h"
#include "queryget.h"
#include "queryresult.h"

class QIODevice;
class QXmlStreamReader;
class QXmlStreamWriter;
class XmlNode;

/**
 * TODO: Write some shiny cool doc comment. :)
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Parser: public QObject
{
Q_OBJECT
public:
    Parser(QObject* parent);
    Parser(QObject* parent, QIODevice* socket);
    virtual ~Parser();

    typedef QString QueryId;

public slots:
    void attachSocket(QIODevice* socket);
    void detachSocket();


signals:
    void streamInitialized();
    void terminated();


public slots:
    void terminate();


    //////////////
    /// CLIENT ///
    //////////////
    void initializeStream();
    QueryGet* queryGet();
//    void queryGameList();
//    void queryGameInfo(int gameId);

    void actionCreateGame(const StructGame&, const StructPlayer&);
    void actionJoinGame(int gameId, const QString& gamePassword, const StructPlayer& player);
    void actionLeaveGame();
    void actionStartGame();
    void actionMessage(const QString& message);



signals:
    void sigResultServerInfo(const StructServerInfo&);
    //void sigResultGameList(const StructGameList&);
    //void sigResultGameInfo(const StructGame&);

    void sigEventJoinGame(int gameId, const StructPlayer&, bool other, bool creator);
    void sigEventLeaveGame(int gameId, const StructPlayer&, bool other = 1);
    void sigEventGameStartable(int gameId, bool startable);
    void sigEventMessage(int senderId, const QString& senderName, const QString& message);


    //////////////
    /// SERVER ///
    //////////////
public slots:
    void eventJoinGame(int gameId, const StructPlayer&, bool other = 1, bool creator = 0);
    void eventLeaveGame(int gameId, const StructPlayer&, bool other = 1);
    void eventMessage(int senderId, const QString& senderName, const QString& message);

    void eventCardMovement(const StructCardMovement&);

    void eventGameStartable(int gameId, bool startable);

    //void resultServerInfo(const StructServerInfo&);
    //void resultGameList(const StructGameList&);
    //void resultGameInfo(const StructGame&);

    //void eventJoinGame(int gameId);
    //void eventLeaveGame();

signals:
    void sigQueryServerInfo(QueryResult);
    void sigQueryGameList(QueryResult);
    void sigQueryGame(int gameId, QueryResult);
    //void sigQueryGameList();
    //void sigQueryGameInfo(int gameId);

    void sigActionCreateGame(StructGame game, StructPlayer player);
    void sigActionJoinGame(int gameId, StructPlayer player);
    void sigActionLeaveGame();
    void sigActionStartGame();
    void sigActionMessage(const QString& message);


public:
    static QString protocolVersion();


private slots:
    void readData();

private:
    void stateStart();
    void stateReady();
    void stateStanza();

    void processStanza();

    void sendInitialization();
    void sendTermination();

    void eventStart();
    void eventEnd();
    void actionStart();
    void actionEnd();


    void streamError();


private:
    typedef enum {
        S_Start = 0,
        S_Ready,
        S_Stanza,
        S_Terminated,
        S_Error
    } ReaderState;
    QIODevice*        mp_socket;
    QXmlStreamReader* mp_streamReader;
    QXmlStreamWriter* mp_streamWriter;

    bool              m_streamInitialized;

    ReaderState       m_readerState;
    int               m_readerDepth;

    XmlNode*          mp_parsedStanza;
    XmlNode*          mp_parsedXmlElement;

    QHash<QString, QueryGet*> m_getQueries;
    QueryGet*         mp_queryGet;
};

#endif
