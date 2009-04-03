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
#include "publicgameview.h"
#include "parser/parserstructs.h"


class Client;
class Player;
class GameServer;
class Game;
class CardAbstract;
class CardPlayable;
class GameEventHandler;

class PublicPlayerView;


class GameInfo;
class GameTable;
class GameCycle;

/**
 * The Game class represents a bang game. It handles creating and destroying players and generates
 * signals about global events in game.
 * @author MacJariel <macjariel@users.sourceforge.net>
 */
class Game: public QObject
{
    Q_OBJECT;
public:

    /**
     * Creates an instance of Game. The GameServer class is responsible
     * for creating instances of Game.
     * \param parent parent of the Game is a GameServer
     * \param structGame the game structure from parser
     * \see GameServer::createGame()
     */
    Game(GameServer* parent, const StructGame& structGame);
    ~Game();

    /**
     * Returns the id of the game. The id is a non-zero integral value.
     */
    int id() const;

    /**
     * Returns the count of (currently alive) players in the game.
     * In the "before game" state returns the count of all players.
     */
    int playersCount() const;

    /**
     * Returns the count of spectators in the game.
     */
    int spectatorsCount() const;

    /**
     * Returns the GameInfo object, that contains information
     * about the game.
     * \note Remember, that the lifetime of the returned
     * object is controlled by the Game instance, so don't
     * keep a reference for too long.
     */
    GameInfo& gameInfo();

    GameCycle& gameCycle();

    GameTable& gameTable();

    const PublicGameView& publicGameView() const;


    /**
     * Returns the list of players. The order determines the
     * order around the table.
     */
    QList<Player*>                  playerList() const;

    QList<const PublicPlayerView*>  publicPlayerList() const;

    Player* nextPlayer(Player* currentPlayer) const;

    Player* getPlayer(int playerId);

    /**
     * Creates a new player, adds him into the list of players and
     * returns the pointer to it. Creating players is reasonable only
     * before the game is started.
     */
    Player* createNewPlayer(StructPlayer player, GameEventHandler* gameEventHandler);

    /**
     * Removes a player from the game. This can be used in anytime and
     * the game should recover ftom it.
     */
    void removePlayer(Player* player);

    /**
     * Tries to start the game.
     * \param player The game is started only if specified player is creator. Otherwise
     *               throws BadPlayerException. If player is null, no condition is tested.
     */
    void startGame(Player* player);

    /**
     * Returns the distance from one player to another. The effect
     * of "horse" cards is considered and therefore this function
     * does not have to be symmetric. Generally getDistance(A,B) !=
     * getDistance(B,A).
     */
    int getDistance(Player* fromPlayer, Player* toPlayer);

    void sendMessage(Player* player, const QString& message);

/// Signals to player controllers
signals:
    void gameStarted();

    void playerJoinedGame(int gameId, const StructPlayer&);
    void playerLeavedGame(int gameId, const StructPlayer&);
    void incomingMessage(int senderId, const QString& senderName, const QString& message);
    void chatMessage(int senderId, const QString& senderName, const QString& message);
    void startableChanged(int gameId, bool startable);



private slots:
    void checkStartable();
private:

    void shufflePlayers();
    void setRoles();
    void dealCards();

    int uniqueCardId();
    QList<PlayerRole> getRoleList();

public:


private:
    GameInfo*                       mp_gameInfo;
    GameTable*                      mp_gameTable;
    GameCycle*                      mp_gameCycle;
    PublicGameView                  m_publicGameView;
    int                             m_nextPlayerId;
    QMap<int, Player*>              m_playerMap;
    QList<Player*>                  m_playerList;
    QList<const PublicPlayerView*>  m_publicPlayerList;
    int                             m_currentPlayerIndex;
    GameState                       m_gameState;

    bool                            m_startable;
};

#endif
