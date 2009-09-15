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

#include "serverconnection.h"
#include "parser/parser.h"
#include "parser/queryget.h"
#include "mainwindow.h"
#include "game.h"
#include "logwidget.h"
#include "debug/debugblock.h"

#include <QTcpSocket>
#include <QMessageBox>
#include <QApplication>

using namespace client;

ServerConnection::ServerConnection()
        : QObject(0),
        mp_tcpSocket(new QTcpSocket(this)),
        mp_parser(0)
{
    connect(mp_tcpSocket, SIGNAL(disconnected()),
            this, SLOT(onDisconnect()));
    connect(mp_tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(onSocketStateChanged()));
    connect(mp_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError()));
}


/* virtual */
ServerConnection::~ServerConnection()
{
}

bool
ServerConnection::isConnected() const
{
    return (mp_parser != 0);
}

QString
ServerConnection::serverName() const
{
    return m_serverInfo.name;
}

QString
ServerConnection::hostName() const
{
    return m_serverHost;
}

QueryGet*
ServerConnection::newQueryGet()
{
    if (mp_parser == 0) {
        return 0;
    }
    return mp_parser->newQueryGet();
}

void
ServerConnection::connectToServer(QString serverHost, int serverPort)
{
    if (mp_tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        m_serverHost = serverHost;
        MainWindow::instance()->logWidget()->appendLogMessage(
            tr("Connecting to %1.").arg(LogWidget::formatServerName(m_serverHost)));
        mp_tcpSocket->connectToHost(serverHost, serverPort);
    }
}

void
ServerConnection::disconnectFromServer()
{
    if (mp_parser != 0) {
        mp_parser->closeStream();
    }
}

void
ServerConnection::createGame(const CreateGameData& game, const CreatePlayerData& player)
{
    if (mp_parser == 0) {
        return;
    }
#if 0
    emit logMessage(tr("Creating game \"%1\".").arg(game.name));
#endif
    mp_parser->actionCreateGame(game, player);
}

void
ServerConnection::joinGame(GameId gameId, PlayerId playerId,
                           const QString& gamePassword, const CreatePlayerData& player)
{
    if (mp_parser == 0) {
        return;
    }
#if 0
    emit logMessage(tr("Joining game."));
#endif
    mp_parser->actionJoinGame(gameId, playerId, gamePassword, player);
}

void
ServerConnection::leaveGame()
{
    if (mp_parser == 0) {
        return;
    }
    mp_parser->actionLeaveGame();
}

void ServerConnection::startGame()
{
    if (mp_parser == 0) {
        return;
    }
    mp_parser->actionStartGame();
}


void ServerConnection::sendChatMessage(const QString& message)
{
    if (mp_parser == 0) {
        return;
    }
    ChatMessageData chatMessageData;
    chatMessageData.text = message;
    mp_parser->actionChatMessage(chatMessageData);
}

void ServerConnection::drawCard()
{
    if (mp_parser == 0) {
        return;
    }
    mp_parser->actionDrawCard();
}

void ServerConnection::playCard(const ActionPlayCardData& actionPlayCardData)
{
    if (mp_parser == 0) {
        return;
    }
    mp_parser->actionPlayCard(actionPlayCardData);
}

void ServerConnection::useAbility(const ActionUseAbilityData& actionUseAbilityData)
{
    if (mp_parser == 0) {
        return;
    }
    mp_parser->actionUseAbility(actionUseAbilityData);
}

void ServerConnection::endTurn()
{
    if (mp_parser == 0) {
        return;
    }
    mp_parser->actionEndTurn();
}

void ServerConnection::pass()
{
    if (mp_parser == 0) {
        return;
    }
    mp_parser->actionPass();
}

void ServerConnection::discardCard(CardId cardId)
{
    if (mp_parser == 0) {
        return;
    }
    mp_parser->actionDiscard(cardId);
}



/* slot */ void
ServerConnection::onDisconnect()
{
    mp_parser->deleteLater();
    mp_parser = 0;
}


/**
 * @todo
 */
/* slot */ void
ServerConnection::onSocketError()
{
    switch(mp_tcpSocket->error()) {
        case QAbstractSocket::ConnectionRefusedError:
        case QAbstractSocket::HostNotFoundError:
            MainWindow::instance()->showWarningMessage(
                    tr("Cannot connect to server: %1").
                    arg(mp_tcpSocket->errorString()));
            break;
        default:
            break;
    }
}

/* slot */ void
ServerConnection::onParserError()
{
    switch (mp_parser->parserError()) {
        case Parser::ProtocolVersionError:
            MainWindow::instance()->showWarningMessage(
                    tr("Cannot connect to server. Remote server uses different "
                       "protocol version. Please make sure you use the latest "
                       "client version."));
            break;
        case Parser::StreamTimeoutError:
            MainWindow::instance()->showWarningMessage(
                    tr("Cannot connect to server. Server did not open the stream."));
            break;
        default:
            break;
    }
}

/* slot */ void
ServerConnection::onSocketStateChanged()
{
    switch(mp_tcpSocket->state()) {
        case QAbstractSocket::UnconnectedState:
            MainWindow::instance()->logWidget()->appendLogMessage(
                    tr("Disconnected from %1.").
                    arg(LogWidget::formatServerName(m_serverHost)));
            break;
        case QAbstractSocket::ConnectedState:
            mp_parser = new Parser(mp_tcpSocket);
            connectParser();
            mp_parser->openStream();
            break;
        default:
            break;
    }

#if 0
    emit statusChanged();
    emit logMessage(tr("Connected to <i>%1</i>.").arg(m_serverHost));
    mp_parser = new Parser(this, mp_tcpSocket);
    initializeParserConnections();
    mp_parser->initializeStream();

#endif
}

/* socket */ void
ServerConnection::onStreamOpened()
{
    MainWindow::instance()->logWidget()->appendLogMessage(
        tr("Connected to %1.").
        arg(LogWidget::formatServerName(m_serverHost)));

    QueryGet* query = newQueryGet();
    connect(query, SIGNAL(result(ServerInfoData)),
            this, SLOT(onServerInfoReceived(ServerInfoData)));
    query->getServerInfo();
}

#if 0
void ServerConnection::disconnected()
{
    if (mp_parser == 0)
        return;
    mp_parser->deleteLater();
    mp_parser = 0;
    emit statusChanged();
    emit logMessage(tr("Disconnected from <i>%1</i>.").arg(m_serverHost));
    m_serverHost = "";
}
#endif

/* slot */ void
ServerConnection::onServerInfoReceived(const ServerInfoData& serverInfo)
{
    m_serverInfo = serverInfo;
}

/*
void ServerConnection::recievedEventJoinGame(int gameId, const StructPlayer& player, bool other)
{
    if (!other)
    {
        m_gameId = gameId;
        emit statusChanged();
        emit logMessage(tr("You have entered the game."));
    }
    else
    {
        emit logMessage(tr("%1 has entered the game.").arg(player.name));
    }
}

void ServerConnection::recievedEventLeaveGame(int gameId, const StructPlayer& player, bool other)
{
    if (!other)
    {
        m_gameId = 0;
        emit statusChanged();
        emit logMessage(tr("You have left the game."));
    }
    else
    {
        emit logMessage(tr("%1 has left the game.").arg(player.name));
    }
}
*/

void ServerConnection::connectParser()
{
    connect(mp_parser, SIGNAL(incomingData(QByteArray)),
            this, SIGNAL(incomingData(QByteArray)));
    connect(mp_parser, SIGNAL(outgoingData(QByteArray)),
            this, SIGNAL(outgoingData(QByteArray)));
    connect(mp_parser, SIGNAL(error(ParserError)),
            this, SLOT(onParserError()));
    connect(mp_parser, SIGNAL(streamOpened()),
            this, SLOT(onStreamOpened()));

    connect(mp_parser, SIGNAL(sigEventEnterGameMode(GameId,QString,ClientType)),
            MainWindow::instance(), SLOT(enterGameMode(GameId,QString,ClientType)));
    connect(mp_parser, SIGNAL(sigEventExitGameMode()),
            MainWindow::instance(), SLOT(exitGameMode()));
    ///@todo
#if 0
    connect(mp_parser, SIGNAL(sigEventChatMessage(ChatMessageData)),



            this, SIGNAL(incomingChatMessage(int, const QString&, const QString&)));
    connect(mp_parser, SIGNAL(sigEventGameCanBeStarted(bool)),
            this, SIGNAL(gameCanBeStarted(bool)));
    connect(mp_parser, SIGNAL(sigEventCardMovement(const CardMovementData&)),
            this, SIGNAL(eventCardMovement(const CardMovementData&)));
#endif
}

