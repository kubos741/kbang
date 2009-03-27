#include "gameinfo.h"

GameInfo::GameInfo(const StructGame& structGame):
    m_id(structGame.id),
    m_name(structGame.name),
    m_description(structGame.description),
    m_creatorId(structGame.creatorId),
    m_minPlayers(structGame.minPlayers),
    m_maxPlayers(structGame.maxPlayers),
    m_maxObservers(structGame.maxSpectators),
    m_playerPassword(structGame.playerPassword),
    m_observerPassword(structGame.spectatorPassword),
    m_shufflePlayers(structGame.flagShufflePlayers)
{
    Q_ASSERT(!m_name.isEmpty());
    Q_ASSERT(m_minPlayers <= m_maxPlayers);
    Q_ASSERT(m_observerPassword.isNull() || !m_playerPassword.isNull()); // observerPassword implies playerPassword
}

StructGame GameInfo::structGame() const
{
    StructGame x;
    x.id = m_gameId;
    x.creatorId = m_creatorId;
    x.name = m_name;
    x.description = m_description;
    x.minPlayers = m_minPlayers;
    x.maxPlayers = m_maxPlayers;
    x.maxSpectators = m_maxObservers;
    x.playerPassword = m_playerPassword;
    x.spectatorPassword = m_observerPassword;
    x.hasPlayerPassword = (!m_playerPassword.isNull());
    x.hasSpectatorPassword = (!m_observerPassword.isNull());
    x.flagShufflePlayers = m_shufflePlayers;
    return r;
}
