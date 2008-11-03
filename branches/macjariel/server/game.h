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
#ifndef GAME_H
#define GAME_H

#include <QtCore>
#include "gamearbiter.h"
#include "publicgameview.h"
#include "parser/parserstructs.h"


class Client;
class Player;
class GameServer;
class Game;
class QXmlStreamWriter;

/**
 * The Game class is the major class that control a bang game. Every bang game running
 * on the server has just one instance of this class. This class stores all global information
 * about the game and thus must not be accessible to player controllers, because they could
 * cheat.
 * The bang game is created by a client (creator) by sending the specified stanza. The only
 * place in code, where new Game objects should be created is in the GameServer class.
 * @author MacJariel <macjariel@users.sourceforge.net>
 */
class Game: public QObject
{
    Q_OBJECT;
public:
    enum GameState {
        Invalid = 0,
        WaitingForPlayers,
        WaitingForCharacters,
        Playing,
        Finished
    };

    /**
     * Creates an instance of Game. The GameServer class is responsible
     * for creating instances of Game.
     * @param parent parent of the Game is a GameServer
     * @see GameServer::createGame()
     */
    Game(GameServer* parent, const StructGame&);
    
    /**
     * Destroys the Game instance.
     */
    ~Game();



    /**
     * Returns the id of the game.
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

    inline bool comparePlayerPassword(const QString& password) const
    {
        return password == m_playerPassword;
    }

    inline bool compareObserverPassword(const QString& password) const
    {
        return (password == m_playerPassword || password == m_observerPassword);
    }

    /** DEPRECATED
     * Writes information about this game (the game tag) to
     * XmlStreamWriter. A verbosity can be specified. The default
     * value is 0.
     * @param xmlOut QXmlStreamWriter to write into
     */
    void writeXml(QXmlStreamWriter& xmlOut, int level = 0);

    StructGame structGame() const;

    /**
     * Creates a new player, enters it into the list of players and
     * returns a pointer to it.
     */
    Player* createNewPlayer(StructPlayer player);

    QList<Player*> playerList();


    const PublicGameView* publicGameView() const
    {
        return &m_publicGameView;
    }


    void postMessage(Player* player, const QString& message);

private:
    QMap<int, Player*>   m_players;     // look-up player
    QList<Player*>       m_playerList;  // player order
//    int m_state;

    const int            m_gameId;
    QString              m_name;
    QString              m_description;
    const int            m_creatorId;
    int                  m_minPlayers;
    int                  m_maxPlayers;
    int                  m_maxObservers;
    QString              m_playerPassword;
    QString              m_observerPassword;
    bool                 m_shufflePlayers;
    int                  m_nextPlayerId;
    GameState            m_gameState;
    const PublicGameView m_publicGameView;
    
signals:
    void chatMessage(int senderId, const QString& senderName, const QString& message);

};

#endif
