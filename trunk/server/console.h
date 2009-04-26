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
#ifndef CONSOLE_H
#define CONSOLE_H

#include "consolecommand.h"
#include "gameserver.h"
#include <QtCore>





/**
 * @author MacJariel <macjariel@users.sourceforge.net>
 */
class Console: public QThread
{
    Q_OBJECT
protected:
    void run();
public:
    Console(GameServer* gameServer, FILE* in, FILE* out);
    ~Console();
    QTextStream& Cout() { return m_cout; }
private:
    QTextStream m_cin;
    QTextStream m_cout;


private:
    void initConsole();
    QString readLine();
    void execLine(QString& cmd);
};

#endif
