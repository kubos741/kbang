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
#ifndef CONFIG_H
#define CONFIG_H

#include <QtCore>

/**
 * The config class provides a way to handle configuration files and commandline
 * arguments. This class is a singleton.
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
*/
class Config{
private:
    Config();
    Config(const Config&);
    Config& operator=(Config&);

    static Config* smp_instance;

    bool loadCfg(const QString& filePath);

    QHash<QPair<QString, QString>, QString> m_values;

public:
    static inline Config& instance()
    {
        if (!smp_instance) smp_instance = new Config();
        return *smp_instance;
    }

    int getInt(const QString& group, const QString& key);
    QString getString(const QString& group, const QString& key);

    ~Config();
};

#endif
