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


#include "gamestructs.h"
#include "queryget.h"
#include "queryresult.h"

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
        TerminatedState,       /**< The stream was closed. */
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
     * Constructs a Parser that uses <i>socket</i> to send and receive messages.
     */
    Parser(QTcpSocket* socket);

    /**
     * Destroys the Parser. Closes the stream, if the <i>socket</i> is still
     * alive.
     */
    virtual ~Parser();

    /**
     * The QueryId type is used to identify queries.
     */
    typedef QString QueryId;

    /**
     * Returns the version of used KBang protocol.
     */
    static QString protocolVersion();

    inline ParserState parserState() const {
        return m_parserState;
    }

    inline ParserError parserError() const {
        return m_parserError;
    }

public slots:
    /**
     * Sends the ping request to other side. As soon as response arrives,
     * <i>pongReceived</i> signal with time in miliseconds is emitted. If
     * response does not arrive sooner than pingTimeout, <i>pong</i> singal
     * with -1 is emitted.
     * @todo Implement what says the description.
     */
    void sendPing();

    /**
     * Opens the stream. This should be called after Parser is created
     * and connections to its signals are made.
     */
    void openStream();

    /**
     * Closes the stream and emits streamClosed() signal.
     */
    void closeStream();

signals:
    /**
     * This signal is emitted when both parties successfully open the stream.
     * After this, the connection is ready to transmit stanzas.
     */
    void streamOpened();

    /**
     * This signal is emitted when one of the party closes the stream. After
     * this, no other stanzas can be transmitted.
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

    /**
     * This signal is emitted when the ping response (pong) is received or
     * in case of time out.
     * @see sendPing()
     */
    void pongReceived(int time);

    ////////////
    // CLIENT //
    ////////////
public:
    /**
     * Creates a new QueryGet instance and returns a pointer to it.
     */
    QueryGet* newQueryGet();

    void actionCreateGame(const CreateGameData&, const CreatePlayerData&);
    void actionJoinGame(GameId, PlayerId, const QString& gamePassword, const CreatePlayerData&);
    void actionLeaveGame();
    void actionStartGame();
    void actionChatMessage(const ChatMessageData&);
    void actionDrawCard();
    void actionPlayCard(const ActionPlayCardData&);
    void actionUseAbility(const ActionUseAbilityData&);
    void actionEndTurn();
    void actionPass();
    void actionDiscard(CardId cardId);

signals:
    void sigEventEnterGameMode(GameId, const QString& gameName, ClientType);
    void sigEventExitGameMode();
    void sigEventPlayerJoinedGame(const PublicPlayerData&);
    void sigEventPlayerLeavedGame(PlayerId);
    void sigEventPlayerUpdate(const PublicPlayerData&);
    void sigEventGameCanBeStarted(bool canBeStarted);
    void sigEventGameStateChange(const GameState&);
    void sigEventGameContextChange(const GameContextData&);
    void sigEventGameSync(const GameSyncData&);
    void sigEventLifePointsChange(PlayerId, int lifePoints);
    void sigEventPlayerDied(PlayerId, PlayerRole role);
    void sigEventCardMovement(const CardMovementData&);
    void sigEventChatMessage(const ChatMessageData&);
    void sigEventGameMessage(const GameMessage&);

    ////////////
    // SERVER //
    ////////////
public:
    void eventEnterGameMode(GameId, const QString& gameName, ClientType);
    void eventExitGameMode();
    void eventPlayerJoinedGame(const PublicPlayerData&);
    void eventPlayerLeavedGame(PlayerId);
    void eventPlayerUpdate(const PublicPlayerData&);
    void eventChatMessage(const ChatMessageData&);
    void eventGameMessage(const GameMessage&);
    void eventGameStateChange(const GameState&);
    void eventGameContextChange(const GameContextData&);
    void eventGameSync(const GameSyncData&);
    void eventCardMovement(const CardMovementData&);
    void eventLifePointsChange(PlayerId, int lifePoints);
    void eventPlayerDied(PlayerId, PlayerRole);
    void eventGameCanBeStarted(bool canBeStarted);

signals:
    void sigQueryServerInfo(const QueryResult&);
    void sigQueryGameInfoList(const QueryResult&);
    void sigQueryGameInfo(GameId, const QueryResult&);
    void sigActionCreateGame(const CreateGameData&, const CreatePlayerData&);
    void sigActionJoinGame(GameId, PlayerId, const QString& gamePassword, const CreatePlayerData&);
    void sigActionLeaveGame();
    void sigActionStartGame();
    void sigActionChatMessage(const ChatMessageData&);
    void sigActionDrawCard();
    void sigActionPlayCard(const ActionPlayCardData&);
    void sigActionUseAbility(const ActionUseAbilityData&);
    void sigActionEndTurn();
    void sigActionPass();
    void sigActionDiscard(CardId);

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
    void processStanzaEvent();
    inline void eventStart();
    inline void eventEnd();
    inline void actionStart();
    inline void actionEnd();
    void raiseNotValidError();

    IOProxy*          mp_ioProxy;
    QTcpSocket*       mp_socket;
    QXmlStreamReader* mp_streamReader;
    QXmlStreamWriter* mp_streamWriter;
    ParserState       m_parserState;
    ParserError       m_parserError;
    int               m_readerDepth;
    XmlNode*          mp_parsedStanza;
    XmlNode*          mp_parsedXmlElement;
    QHash<QString, QueryGet*> m_getQueries;
    QueryGet*         mp_queryGet;

    int               m_keepAliveTimer;
    int               m_waitForStreamTimer;
};

#endif
