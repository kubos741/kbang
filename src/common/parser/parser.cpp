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

#include "gamestructs.h"
#include "ioproxy.h"
#include "parser.h"
#include "util.h"
#include "xmlnode.h"

#include "parser/actionparser.h"
#include "parser/gameeventparser.h"
#include "parser/gamestructparser.h"
#include "parser/servereventparser.h"
#include "parser/querygetparser.h"

#include "debug/debugblock.h"


#include <QTcpSocket>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTimerEvent>


#define KBANG_PROTOCOL_VERSION 2

static const int KeepAliveInterval = 15 * 1000;
static const int WaitForStreamInterval = 5 * 1000;
static const int TerminatingInterval = 5 * 1000;

Parser::Parser(QIODevice* device, bool replay):
        QObject(device), mp_ioProxy(new IOProxy(this)),
        mp_device(device), mp_streamReader(new QXmlStreamReader(mp_device)),
        mp_streamWriter(new QXmlStreamWriter(mp_ioProxy)),
        m_parserState(WaitingForStreamState), m_parserError(NoError), m_readerDepth(0),
        mp_parsedStanza(0), /*mp_queryGet(0),*/ m_keepAliveTimer(0),
        m_waitForStreamTimer(0), m_terminatingTimer(0)
{
    DEBUG_BLOCK;
    connect(mp_ioProxy, SIGNAL(networkOut(const QByteArray&)),
            this, SLOT(sendData(const QByteArray&)));
    if (!replay) {
        connect(mp_device, SIGNAL(readyRead()), this, SLOT(readData()));
    }
    connect(this, SIGNAL(error(ParserError)), this, SLOT(closeStream()));
    mp_streamWriter->setAutoFormatting(1);
}

/* virtual */
Parser::~Parser()
{
    delete mp_streamReader;
    delete mp_streamWriter;
}

QString Parser::protocolVersion()
{
    return QString::number(KBANG_PROTOCOL_VERSION);
}

void Parser::openStream()
{
    if (mp_device->isWritable()) {
        mp_streamWriter->writeStartDocument();
        mp_streamWriter->writeStartElement("stream");
        mp_streamWriter->writeAttribute("version", Parser::protocolVersion());
        mp_streamWriter->writeCharacters("");
        m_waitForStreamTimer = startTimer(WaitForStreamInterval);
    } else {
        readData();
    }
}

void Parser::closeStream()
{
    if (m_parserState == TerminatedState) return;
    if (m_parserState == TerminatingState || !mp_device->isWritable()) {
        m_parserState = TerminatedState;
        emit streamClosed();
    } else {
        m_parserState = TerminatingState;
        m_terminatingTimer = startTimer(TerminatingInterval);
        mp_streamWriter->writeEndElement();
        mp_streamWriter->writeEndDocument();
    }
}

#if 0
QueryGet*
Parser::newQueryGet()
{
    QueryId id;
    do {
        id = randomToken(10, 10);
    } while (m_getQueries.contains(id));
    QueryGet* query = new QueryGet(this, mp_streamWriter, id);
    m_getQueries[id] = query;
    return query;
}

void
Parser::actionCreateGame(const CreateGameData& createGameData,
                         const CreatePlayerData& createPlayerData)
{

    actionStart();
    mp_streamWriter->writeStartElement(CreateGameData::elementName);
    createGameData.write(mp_streamWriter);
    createPlayerData.write(mp_streamWriter);
    mp_streamWriter->writeEndElement();
    actionEnd();
}

void
Parser::actionJoinGame(GameId gameId, PlayerId playerId,
                       const QString& gamePassword, const CreatePlayerData& player)
{
    actionStart();
    mp_streamWriter->writeStartElement("join-game");
    mp_streamWriter->writeAttribute("game-id", QString::number(gameId));
    if (playerId != 0) {
        mp_streamWriter->writeAttribute("player-id", QString::number(playerId));
    }
    if (!gamePassword.isEmpty()) {
        mp_streamWriter->writeAttribute("game-password", gamePassword);
    }
    player.write(mp_streamWriter);
    mp_streamWriter->writeEndElement();
    actionEnd();
}

void
Parser::actionLeaveGame()
{
    actionStart();
    mp_streamWriter->writeEmptyElement("leave-game");
    actionEnd();
}

void
Parser::actionStartGame()
{
    actionStart();
    mp_streamWriter->writeEmptyElement("start-game");
    actionEnd();
}

void
Parser::actionChatMessage(const ChatMessageData& chatMessageData)
{
    actionStart();
    chatMessageData.write(mp_streamWriter);
    actionEnd();
}

void
Parser::actionDrawCard()
{
    actionStart();
    mp_streamWriter->writeEmptyElement("draw-card");
    actionEnd();
}

void
Parser::actionPlayCard(const ActionPlayCardData& actionPlayCardData)
{
    actionStart();
    actionPlayCardData.write(mp_streamWriter);
    actionEnd();
}

void
Parser::actionUseAbility(const ActionUseAbilityData& actionUseAbilityData)
{
    actionStart();
    actionUseAbilityData.write(mp_streamWriter);
    actionEnd();
}

void
Parser::actionEndTurn()
{
    actionStart();
    mp_streamWriter->writeEmptyElement("end-turn");
    actionEnd();
}

void
Parser::actionPass()
{
    actionStart();
    mp_streamWriter->writeEmptyElement("pass");
    actionEnd();
}

void
Parser::actionDiscard(CardId cardId)
{
    actionStart();
    mp_streamWriter->writeStartElement("discard-card");
    mp_streamWriter->writeAttribute("id", QString::number(cardId));
    mp_streamWriter->writeEndElement();
    actionEnd();
}

#endif

void Parser::sendQueryGet(const QueryGetPtr& queryGet, QueryResultHandler* handler)
{
    if (handler->mp_parser != 0) {
        return;
    }
    Query::Id queryId;
    do {
        queryId = randomToken(10, 10);
    } while (m_queries.contains(queryId));
    QueryGetCallback callback;
    callback.handler = handler;
    callback.handler->mp_parser = this;
    callback.time.start();
    m_queries[queryId] = callback;
    queryGet->setId(queryId);
    QueryGetParser::write(mp_streamWriter, queryGet);
}

void Parser::cancelQueryGet(QueryResultHandler* handler)
{
    QHashIterator<Query::Id, QueryGetCallback> i(m_queries);
    while (i.hasNext()) {
        i.next();
        if (i.value().handler == handler) {
            m_queries.remove(i.key());
        }
    }
}

void Parser::sendGameEvent(GameEventDataPtr gameEventDataPtr)
{
    GameEventParser::write(mp_streamWriter, gameEventDataPtr);
}

void Parser::sendServerEvent(ServerEventDataPtr serverEventDataPtr)
{
    ServerEventParser::write(mp_streamWriter, serverEventDataPtr);
}

void Parser::sendAction(ActionDataPtr action)
{
	NOT_IMPLEMENTED();
}

void Parser::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_waitForStreamTimer) {
        killTimer(m_waitForStreamTimer);
        if (m_parserState == WaitingForStreamState) {
            m_parserState = ErrorState;
            m_parserError = StreamTimeoutError;
            emit error(m_parserError);
        }
    } else if (event->timerId() == m_keepAliveTimer) {
        if (mp_device->isWritable()) {
            sendKeepAlive();
        }
    } else if (event->timerId() == m_terminatingTimer) {
        killTimer(m_terminatingTimer);
        closeStream();
    }
    QObject::timerEvent(event);
}

void
Parser::sendKeepAlive()
{
    //@todo use more xml-friendly pings
    sendData(" ");
}

void
Parser::sendData(const QByteArray& data)
{
    emit outgoingData(data);
    mp_device->write(data);
}

void
Parser::readData()
{
    DEBUG_BLOCK;
    if (m_parserState == ErrorState || m_parserState == TerminatedState) {
        return;
    }
    emit incomingData(mp_device->peek(mp_device->bytesAvailable()));
    while (!mp_streamReader->atEnd()) {
        mp_streamReader->readNext();
        if (mp_streamReader->hasError()) {
            if (mp_streamReader->error() != QXmlStreamReader::PrematureEndOfDocumentError) {
                qCritical("[Parser] An error while parsing XML occured: %s",
                          qPrintable(mp_streamReader->errorString()));
                m_parserState = ErrorState;
                if (mp_streamReader->error() == QXmlStreamReader::NotWellFormedError) {
                    m_parserError = NotWellFormedError;
                } else {
                    qWarning("[Parser] Unknown QXmlStreamReader error: %s",
                             qPrintable(mp_streamReader->errorString()));
                    m_parserError = UnknownError;
                }
                emit error(m_parserError);
                return;
            }
            continue;
        }
        if (!(mp_streamReader->isStartElement() || mp_streamReader->isEndElement() ||
              (mp_streamReader->isCharacters() && !mp_streamReader->isWhitespace()))) {
            continue;
        }

        if (mp_streamReader->isEndElement()) {
            m_readerDepth--;
        }

        switch(m_parserState)
        {
        case WaitingForStreamState:
            readStreamStartElement();
            break;
        case ReadyState:
            readStanzaStartElement();
            break;
        case ParsingStanzaState:
            readStanzaNextToken();
            break;
        case TerminatingState:
            if (m_readerDepth == 0) {
                closeStream();
            }
            break;
        default:
            break;
        }

        if (m_parserState == ErrorState || m_parserState == TerminatedState) {
            return;
        }

        if (mp_streamReader->isStartElement()) {
            m_readerDepth++;
        }
    }
}

void
Parser::readStreamStartElement()
{
    DEBUG_BLOCK;
    Q_ASSERT(m_readerDepth == 0);
    killTimer(m_waitForStreamTimer);
    if (mp_streamReader->isStartElement() &&
        mp_streamReader->name() == "stream") {
        QString version = mp_streamReader->attributes().value("version").toString();
        if (version != Parser::protocolVersion()) {
            m_parserState = ErrorState;
            m_parserError = ProtocolVersionError;
            emit error(m_parserError);
            return;
        }
        emit streamOpened();
        m_parserState = ReadyState;
        m_keepAliveTimer = startTimer(KeepAliveInterval);
    } else {
        m_parserState = ErrorState;
        m_parserError = NotValidError;
        emit error(m_parserError);
    }
}

void
Parser::readStanzaStartElement()
{
    DEBUG_BLOCK;
    Q_ASSERT(m_readerDepth <= 1);
    if (mp_streamReader->isEndElement()) {
        // received end of stream
        if (m_parserState == TerminatingState) {

        } else {
            closeStream();
        }
    } else if (!mp_streamReader->isStartElement()) {
        m_parserState = ErrorState;
        m_parserError = NotValidError;
        emit error(m_parserError);
    } else {
        // starting to read new stanza
        Q_ASSERT(mp_parsedStanza == 0);
        mp_parsedXmlElement = mp_parsedStanza = new XmlNode(0, mp_streamReader->name().toString());
        mp_parsedXmlElement->createAttributes(mp_streamReader->attributes());
        m_parserState = ParsingStanzaState;
    }
}

void
Parser::readStanzaNextToken()
{
    DEBUG_BLOCK;
    if (mp_streamReader->isStartElement()) {
        // start element inside of stanza
        mp_parsedXmlElement = mp_parsedXmlElement->
                              createChildNode(mp_streamReader->name(),
                                              mp_streamReader->attributes());
    } else if (mp_streamReader->isEndElement() && m_readerDepth > 1) {
        // end element inside of stanza
        mp_parsedXmlElement = mp_parsedXmlElement->parentNode();
    } else if (mp_streamReader->isCharacters()) {
        // text token inside of stanza
        mp_parsedXmlElement->createChildTextNode(mp_streamReader->text());
    } else if (mp_streamReader->isEndElement() && m_readerDepth == 1) {
        // end of stanza
        if (mp_parsedStanza->name() == "query") {
            processStanzaQuery();
        } else if (mp_parsedStanza->name() == "action") {
            processStanzaAction();
        } else if (mp_parsedStanza->name() == "server-event") {
            emit serverEventReceived(ServerEventParser::read(mp_parsedStanza));
        } else if (mp_parsedStanza->name() == "game-event") {
            emit gameEventReceived(GameEventParser::read(mp_parsedStanza));
        } else {
            raiseNotValidError();
        }
        delete mp_parsedStanza;
        mp_parsedStanza = mp_parsedXmlElement = 0;
        m_parserState = ReadyState;
    }
}


void Parser::processStanzaQuery()
{
    if (mp_parsedStanza->attribute("type") == "get") {
        QueryGetPtr queryGet = QueryGetParser::read(mp_parsedStanza);
        if (!queryGet.isNull()) {
            emit queryGetReceived(queryGet);
        }
    } else if (mp_parsedStanza->attribute("type") == "result") {
        const Query::Id queryId = mp_parsedStanza->attribute("id");
        if (m_queries.contains(queryId)) {
            const QueryGetCallback& callback = m_queries[queryId];
            GameStructPtr gameStruct;
            XmlNode* gameStructNode = mp_parsedStanza->getFirstChild();
            if (gameStructNode != 0) {
                gameStruct = GameStructPtr(GameStructParser::read(gameStructNode));
            }
            callback.handler->resultReceived(gameStruct);
            callback.handler->mp_parser = 0;
            m_queries.remove(queryId);
        }
    }
}

void
Parser::processStanzaAction()
{
    XmlNode* actionNode = mp_parsedStanza->getFirstChild();
    ActionDataPtr actionData = ActionParser::read(actionNode);
    if (!actionData.isNull()) {
        emit actionReceived(actionData);
    } else {
        // recoverable error
    }
}

void
Parser::raiseNotValidError()
{
    if (m_parserState == ErrorState) {
        qWarning("[Parser] Trying to set readerError, but error already set.");
        return;
    }
    m_parserState = ErrorState;
    m_parserError = NotValidError;
    emit error(m_parserError);
}
