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
#ifndef PARSER_H
#define PARSER_H


#include "actions.h"
#include "gameevents.h"
#include "serverevents.h"
#include "queries.h"
#include "gamestructs.h"

#include <QObject>
#include <QHash>

class IOProxy;
class QTcpSocket;
class QXmlStreamReader;
class QXmlStreamWriter;
class QTimerEvent;
class XmlNode;


/**
 * The Parser class provides for both client and server a mean to communicate
 * with each other. An instance of this class is created above the socket to
 * the other side and then messages are sent to the other side by calling
 * methods. As soon as a recognized message is received from other side,
 * according signal is emitted.
 * @author MacJariel
 */
class Parser: public QObject
{
Q_OBJECT
public:
    typedef enum {
        UnconnectedState = 0,  /**< The socket is not connected. */
        WaitingForStreamState, /**< Parser is waiting for <i>stream</i> opening tag. */
        ReadyState,            /**< The stream is opened, parser is waiting for stanzas. */
        ParsingStanzaState,    /**< The parser is parsing a stanza. */
        TerminatingState,      /**< The stream was closed on local side. */
        TerminatedState,       /**< The stream was closed on both sides. */
        ErrorState             /**< Fatal error occured. */
    } ParserState;

    typedef enum {
        NoError = 0,            /**< No fatal error has occured. */
        UnknownError,           /**< Unknown error has occured. */
        StreamTimeoutError,     /**< The peer did not open a stream. */
        ProtocolVersionError,   /**< The peer uses different protocol version. */
        NotWellFormedError,     /**< Read XML is not well-formed. */
        NotValidError           /**< Read XML is not valid. */
    } ParserError;

    /**
     * Constructs a parser that uses <i>socket</i> to send and receive messages.
     */
    Parser(QIODevice* device, bool replay = 0);

    /**
     * Destroys the parser. Closes the stream, if the <i>socket</i> is still
     * alive.
     */
    virtual ~Parser();

    /**
     * Opens the stream. This should be called after Parser is created
     * and connections to its signals are made.
     */
    void openStream();

    /**
     * Closes the stream and emits streamClosed() signal.
     */
    void closeStream();

    /**
     * Returns the state of the parser.
     */
    inline ParserState parserState() const {
        return m_parserState;
    }

    /**
     * Returns the type of the current error, or Parser::NoError if no error occured.
     */
    inline ParserError parserError() const {
        return m_parserError;
    }

    /**
     * Returns the version of used KBang protocol.
     */
    static QString protocolVersion();

signals:
    /**
     * This signal is emitted when both parties successfully open the stream.
     * After this, the connection is ready to transmit stanzas.
     */
    void streamOpened();

    /**
     * This signal is emitted when both parties closed the stream. After
     * this, no other stanzas can be transmitted. It is also emitted if
     * the local party closed the stream and the waiting for the other
     * party to close its stream timed out.
     */
    void streamClosed();

    /**
     * This signal is emitted when error is raised.
     */
    void error(ParserError);

    /**
     * This signal is emitted when Parser receives data from the other party.
     */
    void incomingData(const QByteArray&);

    /**
     * This signal is emitted when Parser sends data to the other party.
     */
    void outgoingData(const QByteArray&);

public:
    void sendQueryGet(const QueryGetPtr&, QueryResultHandler*);

    void cancelQueryGet(QueryResultHandler*);

    void sendQueryResult(const QueryGet&, const GameStruct&);

    /**
     * Sends a game event specified by <i>event</i> to the peer. This method
     * be used exclusively by server.
     */
    void sendGameEvent(GameEventDataPtr event);

    /**
     * Sends a server event specified by <i>event</i> to the peer. This method
     * be used exclusively by server.
     */
    void sendServerEvent(ServerEventDataPtr event);

    void sendAction(ActionDataPtr action);

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

    void actionReceived(const ActionDataPtr& action);

    void queryResultReceived(const GameStructPtr&);

    void queryGetReceived(const QueryGetPtr&);

protected:
    void timerEvent(QTimerEvent* event);

private:
    void sendKeepAlive();

private slots:
    void sendData(const QByteArray&);
    void readData();


private:
    void readStreamStartElement();
    void readStanzaStartElement();
    void readStanzaNextToken();
    void processStanzaQuery();
    void processStanzaAction();
    inline void eventStart();
    inline void eventEnd();
    inline void actionStart();
    inline void actionEnd();
    void raiseNotValidError();

    IOProxy*          mp_ioProxy;
    QIODevice*        mp_device;
    QXmlStreamReader* mp_streamReader;
    QXmlStreamWriter* mp_streamWriter;
    ParserState       m_parserState;
    ParserError       m_parserError;
    int               m_readerDepth;
    XmlNode*          mp_parsedStanza;
    XmlNode*          mp_parsedXmlElement;

    struct QueryGetCallback {
        QueryResultHandler* handler;
        QTime               time;
    };

    QHash<Query::Id, QueryGetCallback> m_queries;

    int               m_keepAliveTimer;
    int               m_waitForStreamTimer;
    int               m_terminatingTimer;
};

#endif
