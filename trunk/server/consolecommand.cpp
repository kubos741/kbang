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

#include <QTextStream>
#include "consolecommand.h"
#include "gameserver.h"


QMap<QString, ConsoleCmd*> ConsoleCmd::mp_commands;
ConsoleCmd* ConsoleCmd::mp_cmdNotFound = 0;

void ConsoleCmd::initialize()
{
    ConsoleCmdGet::initialize();
    ConsoleCmdNotFound::initialize();
    ConsoleCmdHelp::initialize();
}

QPair<QString, QStringList> ConsoleCmd::parse(QString command)
{
    QPair<QString, QStringList> aResult;
    QTextStream ss(&command, QIODevice::ReadOnly);
    QString buffer;
    ss >> aResult.first;
    while (ss.status() == QTextStream::Ok)
    {
        ss >> buffer;
        if (buffer.size()) aResult.second.push_back(buffer);
    }
    return aResult;
    //int i;
    //for(i=0;i<m_params.size();++i)
    //    QTextStream(stdout) << m_params[i] << endl;
}

QString ConsoleCmdNotFound::execute(const QString& cmdName, const QStringList &, const GameServer*) const
{
    if (cmdName.length() == 0) return QString("");
    return QString(cmdName + ": command not found\n");
}

ConsoleCmdHelp::ConsoleCmdHelp()
{
    m_cmdName = "help";
    m_help = "Displays this help";
}

QString ConsoleCmdHelp::execute(const QString&, const QStringList& attributes, const GameServer*) const
{
    const QMap<QString, ConsoleCmd*>& map = ConsoleCmd::commands();
    QMapIterator<QString, ConsoleCmd*> i(map);
    QStringList rows;
    while(i.hasNext())
    {
        i.next();
        rows.push_back(i.key()  + ": " + i.value()->help());
    }
    return rows.join("\n");

}



void ConsoleCmdHelp::initialize()
{
    ConsoleCmd::appendCommand("help", new ConsoleCmdHelp());
}

QString ConsoleCmdGet::execute(const QString&, const QStringList& params, const GameServer* gs) const
{
    if (params.count() == 0) return QString("use: get [VAR]");
    if (params[0] == "name") return gs->name();

        return QString("This is the get command.");
        }




