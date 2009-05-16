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
#include "console.h"
#include "consolecommand.h"
#include "gameserver.h"
#include <QIODevice>

Console::Console(GameServer* gameServer, FILE* in, FILE* out):
        QThread(gameServer),
        m_cin(in, QIODevice::ReadOnly),
        m_cout(out, QIODevice::WriteOnly),
        mp_gameServer(gameServer)
{
}


Console::~Console()
{
    if (!isFinished()) {
        exit(0);
        if (!wait(200)) {
            terminate();
            wait(500);
        }
    }
}

void Console::run()
{
    initConsole();
    QString line;
    while(1)
    {
        line = readLine();
        execLine(line);
    }
}

void Console::initConsole()
{
    console_register_commands();
    m_cout << QString("Welcome to KBang Server version %1.").arg(mp_gameServer->version()) << endl;
}

QString Console::readLine()
{
    
    m_cout << "> " << flush;
    return m_cin.readLine();
}

/**
 *
 * @param cmdString
 */
void Console::execLine(QString& cmdString)
{
    QString cmdName;
    QStringList cmdArgs;
    QTextStream ss(&cmdString, QIODevice::ReadOnly);
    QString buffer;
    ss >> cmdName;
    while (ss.status() == QTextStream::Ok)
    {
        ss >> buffer;
        if (buffer.size()) cmdArgs.push_back(buffer);
    }
    ConsoleCmd* cmd = console_get_command(cmdName);
    if (!cmd)
    {
        m_cout << cmdName << ": bad command" << endl;
        return;
    }
    (*cmd)(cmdArgs, *this); 
/*    
//    const ConsoleCmd& cmd = ConsoleCmd::instance(pair.first);
    QString result = cmd.execute(pair.first, pair.second, mp_gameServer);
    //QString result(cmd.exec(mp_gameServer));
    if (result.size())
    {
        QStringList resultLines = result.split('\n');
        for(QStringList::const_iterator it = resultLines.begin(); it != resultLines.end(); ++it)
        {
            m_cout << "   " << *it << endl;
        }
    } else {
        m_cout << flush;
    }
*/
}
