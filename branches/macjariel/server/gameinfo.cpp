#include "gameinfo.h"

GameInfo::GameInfo(const StructGame& structGame):
    m_id(structGame.id),
    m_name(structGame.name),
    m_description(structGame.description),
    m_creatorId(structGame.creatorId),
    m_minPlayers(structGame.minPlayers),
    m_maxPlayers(structGame.maxPlayers),
    m_maxSpectators(structGame.maxSpectators),
    m_playerPassword(structGame.playerPassword),
    m_spectatorPassword(structGame.spectatorPassword),
    m_shufflePlayersFlag(structGame.flagShufflePlayers)
{
    Q_ASSERT(!m_name.isEmpty());
    Q_ASSERT(m_minPlayers <= m_maxPlayers);
    Q_ASSERT(m_spectatorPassword.isNull() || !m_playerPassword.isNull()); // observerPassword implies playerPassword
}

StructGame GameInfo::structGame() const
{
    StructGame x;
    x.id = m_id;
    x.creatorId = m_creatorId;
    x.name = m_name;
    x.description = m_description;
    x.minPlayers = m_minPlayers;
    x.maxPlayers = m_maxPlayers;
    x.maxSpectators = m_maxSpectators;
    x.playerPassword = m_playerPassword;
    x.spectatorPassword = m_spectatorPassword;
    x.hasPlayerPassword = (!m_playerPassword.isNull());
    x.hasSpectatorPassword = (!m_spectatorPassword.isNull());
    x.flagShufflePlayers = m_shufflePlayersFlag;
    return x;
}
