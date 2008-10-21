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


#include "parser.h"

#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#define PROTOCOL_VERSION "1.0"
#define ASSERT_SOCKET if (!mp_socket) return

Parser::Parser(QObject* parent):
    QObject(parent), mp_socket(0)
{

}

Parser::Parser(QObject* parent, QIODevice* socket):
    QObject(parent), mp_socket(0)
{
    attachSocket(socket);
}

Parser::~Parser()
{

}

void Parser::attachSocket(QIODevice* socket)
{
    Q_ASSERT(socket);
    if (mp_socket) detachSocket();
    mp_socket = socket;
//    connect(mp_socket, SIGNAL(disconnected()),
//            this, SLOT(detachSocket()));
    mp_streamReader = new QXmlStreamReader(mp_socket);
    mp_streamWriter = new QXmlStreamWriter(mp_socket);

}

void Parser::detachSocket()
{
    if (!mp_socket) return;
    disconnect(mp_socket, SIGNAL(disconnected()),
               this, SLOT(detachSocket()));
    delete mp_streamWriter;
    delete mp_streamReader;
}


void Parser::initializeStream()
{
    ASSERT_SOCKET;
    qDebug("WRITING\n");
    mp_streamWriter->writeStartDocument();
    mp_streamWriter->writeStartElement("stream");
    mp_streamWriter->writeAttribute("version", Parser::protocolVersion());
    mp_streamWriter->writeCharacters("");
    mp_streamWriter->writeEndElement();
}

QString Parser::protocolVersion()
{
    return QString(PROTOCOL_VERSION);
}
