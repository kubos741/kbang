/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
 *   MacJariel (at) gmail.com                                              *
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
#ifndef DEBUGBLOCK_H
#define DEBUGBLOCK_H

#include <QMutex>
#include <QtDebug>

#define DEBUG_BLOCK DebugBlock uniquelyNamedStackAllocatedStandardBlock( __PRETTY_FUNCTION__ );


class DebugBlock
{
public:
    DebugBlock(const char* label);
    ~DebugBlock();

private:
    const char* mp_label;
    int         m_level;

    static int sm_level;
    static QMutex sm_mutex;
};

#endif // DEBUGBLOCK_H
