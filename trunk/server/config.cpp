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

#include "config.h"

Config* Config::smp_instance = 0;

Config::Config()
{
    loadCfg(QDir::current().filePath("kbang.conf"));
    // TODO: only config file from current directory is loaded
    //       in future there will be system-wide and user locations added
}



bool Config::loadCfg(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << filePath << ": cannot open config file";
        return 0;
    }
    QTextStream in(&file);
    QString currentGroup;
    int lineNum = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        lineNum++;
        int commentChar = line.indexOf('#');
        if (commentChar != -1) line = line.left(commentChar);
        if (line.isEmpty()) continue;
        line = line.trimmed();

        if (line.startsWith('[') && line.endsWith(']'))
        {
            QString token = line.mid(1, line.size() - 2).trimmed();
            if (token.contains('[') || token.contains(']'))
            {
                qWarning() << filePath << ":" << lineNum
                    << ": invalid group";
                continue;
            }
            currentGroup = token;
        } else {
            if (currentGroup.isEmpty())
            {
                qWarning() << filePath << ":" << lineNum
                    << ": no group defined";
                continue;
            }
            QStringList tokens = line.split('=');
            if (tokens.size() != 2)
            {
                qWarning() << filePath << ":" << lineNum
                    << ": invalid line";
                continue;
            }
            QString key = tokens[0].trimmed();
            QString value = tokens[1].trimmed();
            m_values[qMakePair(currentGroup, key)] = value;
            //qDebug() << "config: (" << currentGroup << "," << key << ") = " << value;
        }
    }
    return 1;
}

QString Config::getString(const QString & group, const QString & key)
{
    if (m_values.contains(qMakePair(group, key)))
    {
        return m_values[qMakePair(group, key)];
    }
    return QString();
}

int Config::getInt(const QString & group, const QString & key)
{
    return getString(group, key).toInt();
}

