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

#include <QTcpSocket>

using namespace client;

ServerConnection::ServerConnection()
        : QObject(0), mp_parser(0)
{
    mp_tcpSocket = new QTcpSocket(this);
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
    if (mp_tcpSocket->state() == QAbstractSocket::UnconnectedState)
    {
#if 0
        emit logMessage(tr("Connecting to <i>%1</i>...").arg(serverHost));
#endif
        mp_tcpSocket->connectToHost(serverHost, serverPort);
        m_serverHost = serverHost;
    }
}

void
ServerConnection::disconnectFromServer()
{
    if (mp_parser != 0 && mp_tcpSocket->state() != QAbstractSocket::UnconnectedState) {
        mp_parser->terminate();
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
    mp_parser->actionChatMessage(message);
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




/**
 * @todo
 */
/* slot */ void
ServerConnection::onSocketError()
{
    switch(mp_tcpSocket->error()) {
        case QAbstractSocket::ConnectionRefusedError:
            break;
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            break;
        default:

            break;
    }
}

/**
 * @todo
 */
/* slot */ void
ServerConnection::onSocketStateChanged()
{
    switch(mp_tcpSocket->state()) {
        case QAbstractSocket::UnconnectedState:
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            break;
        case QAbstractSocket::BoundState:
            break;
        case QAbstractSocket::ClosingState:
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

    QueryGet* query = queryGet();
    connect(query, SIGNAL(result(const ServerInfoData&)),
            this, SLOT(recievedServerInfo(const ServerInfoData&)));
    query->getServerInfo();
#endif
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

void ServerConnection::initializeParserConnections()
{
    connect(mp_parser, SIGNAL(sigEventEnterGameMode(int,QString,ClientType)),
            this,      SIGNAL(enterGameMode(int,QString,ClientType)));
    connect(mp_parser, SIGNAL(sigEventExitGameMode()),
            this,      SIGNAL(exitGameMode()));
    connect(mp_parser, SIGNAL(sigEventChatMessage(int, const QString&, const QString&)),
            this, SIGNAL(incomingChatMessage(int, const QString&, const QString&)));
    connect(mp_parser, SIGNAL(sigEventGameCanBeStarted(bool)),
            this, SIGNAL(gameCanBeStarted(bool)));
    connect(mp_parser, SIGNAL(incomingData(const QByteArray&)),
            this, SIGNAL(incomingData(const QByteArray&)));
    connect(mp_parser, SIGNAL(outgoingData(const QByteArray&)),
            this, SIGNAL(outgoingData(const QByteArray&)));
    connect(mp_parser, SIGNAL(sigEventCardMovement(const CardMovementData&)),
            this, SIGNAL(eventCardMovement(const CardMovementData&)));
}

