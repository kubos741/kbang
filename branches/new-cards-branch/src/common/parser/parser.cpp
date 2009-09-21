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
#include "queryget.h"
#include "util.h"
#include "xmlnode.h"

#include "parser/gameeventparser.h"
#include "parser/servereventparser.h"

#include "debug/debugblock.h"


#include <QTcpSocket>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QTimerEvent>


#define KBANG_PROTOCOL_VERSION 2

static const int KeepAliveInterval = 15 * 1000;
static const int WaitForStreamInterval = 5 * 1000;

Parser::Parser(QIODevice* device, bool replay):
        QObject(device), mp_ioProxy(new IOProxy(this)),
        mp_device(device), mp_streamReader(new QXmlStreamReader(mp_device)),
        mp_streamWriter(new QXmlStreamWriter(mp_ioProxy)),
        m_parserState(WaitingForStreamState), m_parserError(NoError), m_readerDepth(0),
        mp_parsedStanza(0), mp_queryGet(0), m_keepAliveTimer(0),
        m_waitForStreamTimer(0)
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
#if 0
    if (mp_device->state() == QAbstractSocket::ConnectedState) {
        closeStream();
    }
    mp_device->disconnectFromHost();
#endif
    delete mp_streamReader;
    delete mp_streamWriter;
}

QString
Parser::protocolVersion()
{
    return QString::number(KBANG_PROTOCOL_VERSION);
}

/* slot */ void
Parser::sendPing()
{
    QueryGet* query = newQueryGet();
    connect(query, SIGNAL(pong(int)), this, SIGNAL(pongReceived(int)));
    query->getPing();
}

void
Parser::openStream()
{
    if (mp_device->isWritable()) {
        mp_streamWriter->writeStartDocument();
        mp_streamWriter->writeStartElement("stream");
        mp_streamWriter->writeAttribute("version", Parser::protocolVersion());
        mp_streamWriter->writeCharacters("");
        m_waitForStreamTimer = startTimer(WaitForStreamInterval);
        //mp_device->flush();
    } else {
        readData();
    }
}

void
Parser::closeStream()
{
    mp_streamWriter->writeEndElement();
    mp_streamWriter->writeEndDocument();
    emit streamClosed();
#if 0
    if (mp_device->state() == QAbstractSocket::ConnectedState) {
        mp_device->disconnectFromHost();
    }
#endif
}

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

void Parser::sendGameEvent(GameEventDataPtr gameEventDataPtr)
{
    GameEventParser::write(mp_streamWriter, gameEventDataPtr);
}

void Parser::sendServerEvent(ServerEventDataPtr serverEventDataPtr)
{
    ServerEventParser::write(mp_streamWriter, serverEventDataPtr);
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
    }
    QObject::timerEvent(event);
}

void
Parser::sendKeepAlive()
{
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
        m_parserState = TerminatedState;
        if (mp_device->isWritable()) {
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


void
Parser::processStanzaQuery()
{
    const QueryId& id = mp_parsedStanza->attribute("id");
    if (mp_parsedStanza->attribute("type") == "get") {
        XmlNode* query = mp_parsedStanza->getFirstChild();
        if (query == 0) {
            raiseNotValidError();
        } else if (query->name() == ServerInfoData::elementName) {
            emit sigQueryServerInfo(QueryResult(mp_streamWriter, id));
        } else if (query->name() == GameInfoData::elementName) {
            GameId gameId = query->attribute("id").toInt();
            emit sigQueryGameInfo(gameId, QueryResult(mp_streamWriter, id));
        } else if (query->name() == GameInfoListData::elementName) {
            emit sigQueryGameInfoList(QueryResult(mp_streamWriter, id));
        } else if (query->name() == "ping") {
            QueryResult pong(mp_streamWriter, id);
            pong.sendPong();
        } else {
            qWarning("[Parser] Unknown query: %s", qPrintable(query->name()));
        }
    } else if (mp_parsedStanza->attribute("type") == "result") {
        if (m_getQueries.contains(id)) {
            m_getQueries[id]->parseResult(mp_parsedStanza->getFirstChild());
            m_getQueries[id]->deleteLater();
            m_getQueries.remove(id);
        } else {
            qWarning("[Parser] Result with unknown id received.");
        }
    } else {
        raiseNotValidError();
    }
}

void
Parser::processStanzaAction()
{
    XmlNode* action = mp_parsedStanza->getFirstChild();
    if (action == 0) {
        raiseNotValidError();
    } else if (action->name() == "create-game") {
        XmlNode* game = action->getChildren()[0];
        XmlNode* player = action->getChildren()[1];
        if (!game || game->name() != CreateGameData::elementName ||
            !player || player->name() != CreatePlayerData::elementName) {
            raiseNotValidError();
        } else {
            CreateGameData createGameData;
            createGameData.read(game);
            CreatePlayerData createPlayerData;
            createPlayerData.read(player);
            emit sigActionCreateGame(createGameData, createPlayerData);
        }
    } else if (action->name() == "join-game") {
        GameId gameId = action->attribute("game-id").toInt();
        PlayerId playerId = action->attribute("player-id").toInt();
        QString gamePassword = action->attribute("game-password");
        XmlNode* player = action->getFirstChild();
        if (!player || player->name() != CreatePlayerData::elementName) {
            raiseNotValidError();
        } else {
            CreatePlayerData createPlayerData;
            createPlayerData.read(player);
            emit sigActionJoinGame(gameId, playerId, gamePassword, createPlayerData);
        }
    } else if (action->name() == "leave-game") {
        emit sigActionLeaveGame();
    } else if (action->name() == "start-game") {
        emit sigActionStartGame();
    } else if (action->name() == ChatMessageData::elementName) {
        ChatMessageData chatMessageData;
        chatMessageData.read(action);
        emit sigActionChatMessage(chatMessageData);
    } else if (action->name() == "draw-card") {
        emit  sigActionDrawCard();
    } else if (action->name() == ActionPlayCardData::elementName) {
        ActionPlayCardData actionPlayCardData;
        actionPlayCardData.read(action);
        emit sigActionPlayCard(actionPlayCardData);
    } else if (action->name() == ActionUseAbilityData::elementName) {
        ActionUseAbilityData actionUseAbilityData;
        actionUseAbilityData.read(action);
        emit sigActionUseAbility(actionUseAbilityData);
    } else if (action->name() == "end-turn") {
        emit sigActionEndTurn();
    } else if (action->name() == "pass") {
        emit sigActionPass();
    } else if (action->name() == "discard-card") {
        CardId cardId = action->attribute("id").toInt();
        emit sigActionDiscard(cardId);
    } else {
        qWarning("[Parser] Unknown action: %s", qPrintable(action->name()));
    }
}
void
Parser::eventStart()
{
    mp_streamWriter->writeStartElement("event");
}

void
Parser::eventEnd()
{
    mp_streamWriter->writeEndElement();
}

void
Parser::actionStart()
{
    mp_streamWriter->writeStartElement("action");
}

void
Parser::actionEnd()
{
    mp_streamWriter->writeEndElement();
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
