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
#include "console.h"
#include "gameserver.h"
#include "game.h"

#include "voidai.h"


#define CMDDEF(name) bool name(const QStringList& args, Console& console)
#define CMDREG(name, function) cmdHash.insert(name, function)
#define CMDALIAS(name, alias) cmdHash.insert(name, cmdHash[alias])
#define CMD_ASSERT_ARG_CNT(cnt) if (args.size() != cnt) { console.Cout() << QString("Bad arguments count, expected %1.").arg(cnt); return 1; }



QHash<QString, ConsoleCmd*> cmdHash;


ConsoleCmd* console_get_command(const QString& cmdName)
{
    if (cmdHash.contains(cmdName))
    {
        return cmdHash.value(cmdName);
    }
    return 0;
}

CMDDEF(console_help)
{
    (void) args;
    console.Cout() << "Help" << endl;
    return 1;
}

CMDDEF(console_quit)
{
    (void) args;
    (void) console;
    GameServer::instance().exit();
    return 1;
}

CMDDEF(console_create_test_player)
{
    CMD_ASSERT_ARG_CNT(2);

    int gameId;
    bool ok;
    gameId = args[0].toInt(&ok);
    if (!ok) {
        console.Cout() << QString("Expected int as the first argument.");
        return 1;
    }
    Game* game = GameServer::instance().game(gameId);
    if (game == 0) {
        console.Cout() << QString("The game id %1 does not exist.").arg(gameId);
        return 1;
    }
    new VoidAI(gameId);
    return 0;
}


void console_register_commands()
{
    CMDREG("help", &console_help);
    CMDREG("quit", &console_quit);
    CMDREG("create_test_player", &console_create_test_player);
    CMDALIAS("exit", "quit");
}


/*
QMap<QString, ConsoleCmd*> ConsoleCmd::mp_commands;
ConsoleCmd* ConsoleCmd::mp_cmdNotFound = 0;

void ConsoleCmd::initialize()
{
    ConsoleCmdGet::initialize();
    ConsoleCmdNotFound::initialize();
    ConsoleCmdHelp::initialize();
    ConsoleCmdQuit::initialize();
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

void ConsoleCmdHelp::quit()
{
    ConsoleCmd::appendCommand("quit", new ConsoleCmdQuit());
}
*/



