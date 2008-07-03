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
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "player.h"
#include "gamearbiter.h"
#include <QtCore>

class Client;
class GameServer;
class QXmlStreamWriter;

enum {  STATE_AWAITING = 1, // Players are connecting
        STATE_PREGAME  = 2, // The number of players is fixed - time for choosing roles
        STATE_GAME     = 3  // Game is ready
};



/**
 * The GameState class is the major class that control a bang game. Every bang game running
 * on the server has just one instance of this class. This class stores all global information
 * about the game and thus must not be accessible to player controllers, because they could
 * cheat.
 * The bang game is created by a client (creator) by sending the specified stanza. The only
 * place in code, where new GameState objects should be created is in the GameServer class.
 * @author MacJariel <macjariel@users.sourceforge.net>
 */
class GameState : public QObject
{
Q_OBJECT
public:

    /**
     * Creates an instance of GameState. The GameServer class is responsible
     * for creating instances of GameState.
     * @param parent parent of the GameState is a GameServer
     * @param gameId id of the game - the GameServer class is responsible to set it unique
     * @param name name of the game
     * @param description description of the game
     * @param creatorId id of client that creates the game (if the game is created by server, use special value 0)
     * @param minPlayers minimal count of players
     * @param maxPlayers maximal count of players
     * @param maxObservers maximal count of observers
     * @param playerPassword playerPassword (null string means no password)
     * @param observerPassword observerPassword (null string means no password)
     * @param shufflePlayers shuffle-players feature
     * @see GameServer::createGame()
     */
    GameState(GameServer* parent,
              int gameId,
              const QString& name,
              const QString& description,
              int creatorId,
              int minPlayers,
              int maxPlayers,
              int maxObservers,
              // TODO: implement rulesets
              const QString& playerPassword,
              const QString& observerPassword,
              bool shufflePlayers);



    //    GameState(QObject *parent, const Client& client, int maxPlayers, int AIPlayers);
    ~GameState();



    /**
     * Returns id of the game.
     */
    inline int gameId() const
    {
        return m_gameId;
    }

    /**
     * Returns name of the game.
     */
    inline QString name() const
    {
        return m_name;
    }

    /**
     * Returns description of the game.
     */
    inline QString description() const
    {
        return m_description;
    }

    /**
     * Returns minimal count of players.
     */
    inline int minPlayers() const
    {
        return m_minPlayers;
    }

    /**
     * Returns maximal count of players.
     */
    inline int maxPlayers() const
    {
        return m_maxPlayers;
    }

    /**
     * Returns maximal count of observers.
     */
    inline int maxObservers() const
    {
        return m_maxObservers;
    }

    /**
     * Returns count of players.
     */
    inline int playersCount() const
    {
        return m_players.size();
    }

    /**
     * Returns count of observers.
     */
    inline int observersCount() const
    {
        return 0; // TODO: implement this
    }

    /**
     * Returns 1 if player password is set,
     * otherwise returns 0.
     */
    inline bool hasPlayerPassword() const
    {
        return !m_playerPassword.isNull();
    }

    /**
     * Returns 1 if observer password is set,
     * otherwise returns 0.
     */
    inline bool hasObserverPassword() const
    {
        return !m_observerPassword.isNull();
    }

    /**
     * Returns the id of the client that created this game.
     */
    inline int creatorId() const
    {
        return m_creatorId;
    }

    /**
     * Returns true if shuffle-players feature is set, otherwise
     * returns false. This feature shuffles players after the
     * game starts.
     */
    inline bool hasShufflePlayers() const
    {
        return m_shufflePlayers;
    }

    /**
     * Writes information about this game (the game tag) to
     * XmlStreamWriter.
     * @param xmlOut QXmlStreamWriter to write into
     */
    void writeXml(QXmlStreamWriter& xmlOut);


private:
    QList<Player*> m_players;
    GameArbiter m_arbiter;
    int m_state;

    const int   m_gameId;
    QString     m_name;
    QString     m_description;
    const int   m_creatorId;
    int         m_minPlayers;
    int         m_maxPlayers;
    int         m_maxObservers;
    QString     m_playerPassword;
    QString     m_observerPassword;
    bool        m_shufflePlayers;
};

#endif
