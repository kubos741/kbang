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

#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "gamestructs.h"

class GameInfo
{
public:
    GameInfo(const CreateGameData&);

    inline QString name() const {
        return m_createGameData.name;
    }

    inline QString desc() const {
        return m_createGameData.desc;
    }

    inline int playersMin() const {
        return m_createGameData.playersMin;
    }

    inline int playersMax() const {
        return m_createGameData.playersMax;
    }

    inline int spectatorsMax() const {
        return m_createGameData.spectatorsMax;
    }

    inline int aiPlayersCnt() const {
        return m_createGameData.aiPlayersCnt;
    }

    inline bool hasPlayerPassword() const {
        return !m_createGameData.playerPassword.isEmpty();
    }

    inline bool hasSpectatorPassword() const {
        return !m_createGameData.spectatorPassword.isEmpty();
    }

    inline PlayerId creatorId() const {
        return m_creatorId;
    }

    inline bool hasShufflePlayers() const {
        return m_createGameData.flagShufflePlayers;
    }

    inline bool comparePlayerPassword(const QString& password) const {
        return password == m_createGameData.playerPassword;
    }

    inline bool compareSpectatorPassword(const QString& password) const {
        return (password == m_createGameData.playerPassword ||
                password == m_createGameData.spectatorPassword);
    }

    inline void setCreatorId(int creatorId) {
        m_creatorId = creatorId;
    }


private:
    CreateGameData m_createGameData;
    PlayerId       m_creatorId;
};

#endif // GAMEINFO_H
