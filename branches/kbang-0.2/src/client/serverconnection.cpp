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
#include "common.h"
#include "parser/parser.h"
#include "mainwindow.h"
#include "game.h"
#include "logwidget.h"

#include <QTcpSocket>
#include <QMessageBox>
#include <QApplication>

using namespace client;

class ServerConnection::QueryHandler: public QueryResultHandler {
public:
    QueryHandler(ServerConnection* s): mp_s(s) {}
    virtual void resultReceived(const GameStructPtr& data) {
        if (data->t() == GameStruct::ServerInfoDataType) {
            *(mp_s->mp_serverInfo) = *data.staticCast<ServerInfoData>();
        }
    }
    ServerConnection* mp_s;
};

ServerConnection* ServerConnection::smp_instance(0);

ServerConnection::ServerConnection():
        QObject(MainWindow::instance()),
        mp_handler(new ServerConnection::QueryHandler(this)),
        mp_tcpSocket(new QTcpSocket(this)),
        mp_parser(0),
        mp_serverInfo(new ServerInfoData())
{
    connect(mp_tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(onSocketStateChanged()));
    connect(mp_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError()));
}

/* virtual */
ServerConnection::~ServerConnection()
{
    delete mp_serverInfo;
    delete mp_handler;
}

QString ServerConnection::serverName() const
{
    return mp_serverInfo->name;
}

void ServerConnection::connectToServer(const QString& serverHost, int serverPort)
{
    if (mp_tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        m_serverHost = serverHost;
        ///@todo log message? "connecting to host.."
        mp_tcpSocket->connectToHost(serverHost, serverPort);
    }
}

void ServerConnection::disconnectFromServer()
{
    if (mp_parser != 0) {
        mp_parser->closeStream();
    }
}

void ServerConnection::sendQueryGet(const QueryGetPtr& q, QueryResultHandler* r)
{
    if (mp_parser) {
        mp_parser->sendQueryGet(q ,r);
    }
}

void ServerConnection::cancelQueryGet(QueryResultHandler* r)
{
    if (mp_parser) {
        mp_parser->cancelQueryGet(r);
    }
}

void ServerConnection::sendAction(const ActionDataPtr& action)
{
    if (mp_parser) {
        mp_parser->sendAction(action);
    }
}

/* private slot */
void ServerConnection::onStreamOpened()
{
    mp_parser->sendQueryGet(QueryGetPtr(new QueryServerInfoGet()), mp_handler);
}

/* private slot */
void ServerConnection::onStreamClosed()
{
    if (mp_tcpSocket->state() != QAbstractSocket::UnconnectedState) {
        mp_tcpSocket->disconnectFromHost();
    }
}

/* private slot */
void ServerConnection::onParserError()
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
        MainWindow::instance()->showWarningMessage(
                tr("The protocol parser encountered error in incoming stream."));
        break;
    }
    if (mp_tcpSocket->state() != QAbstractSocket::UnconnectedState) {
        mp_tcpSocket->disconnectFromHost();
    }
}

/* private slot */
void ServerConnection::onSocketStateChanged()
{
    switch(mp_tcpSocket->state()) {
    case QAbstractSocket::UnconnectedState:
        //@todo log message: disconneted
        mp_parser->deleteLater();
        mp_parser = 0;
        break;
    default:
        break;
    }
}

/* slot */
void ServerConnection::onSocketError()
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
