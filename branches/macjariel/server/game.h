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
     * @param parent parent of the Game is a GameServer
     * @see GameServer::createGame()
     */
    Game(GameServer* parent, const StructGame&);

    /**
     * Destroys the Game instance.
     */
    ~Game();



    inline int      gameId() const { return m_gameId; }
    inline QString  name() const { return m_name; }
    inline QString  description() const { return m_description; }
    inline int      minPlayers() const { return m_minPlayers; }
    inline int      maxPlayers() const { return m_maxPlayers; }
    inline int      maxObservers() const { return m_maxObservers; }
    inline int      playersCount() const { return m_players.size(); }
    inline int      observersCount() const { return 0; /*TODO:implement this*/ }
    inline bool     hasPlayerPassword() const { return !m_playerPassword.isNull(); }
    inline bool     hasObserverPassword() const { return !m_observerPassword.isNull(); }
    inline int      creatorId() const { return m_creatorId; }
    inline bool     hasShufflePlayers() const { return m_shufflePlayers; }

    inline bool comparePlayerPassword(const QString& password) const
    {
        return password == m_playerPassword;
    }

    inline bool compareObserverPassword(const QString& password) const
    {
        return (password == m_playerPassword || password == m_observerPassword);
    }

    StructGame structGame() const;
    StructPlayerList structPlayerList() const;

    /**
     * Creates a new player, enters it into the list of players and
     * returns a pointer to it. This method can be called only in the initialization state.
     */
    Player* createNewPlayer(StructPlayer player);

    void removePlayer(int playerId);

    QList<Player*> playerList();

    /**
     * If the game is in the 'waiting for players' state, it is started.
     */
    void startGame();

    const PublicGameView* publicGameView() const
    {
        return &m_publicGameView;
    }

    /**
     * Returns true, if the player that is on turn has the right
     * to decide what to do. The opposite situation means that
     * there has been a card played and we are still waiting for
     * the resolution of the card effect.
     */
    bool isBaseTurn() const;

    /**
     * Returns the pointer to Player that is currently on turn.
     */
    Player* playerOnTurn() const;

    /**
     * Appends a playable card to the playedCards list. This should
     * be exclusively used by CardPlayable::play methods.
     */
    void appendPlayedCard(CardPlayable* card);

    /**
     * Returns the last played card.
     */
    CardPlayable* peakPlayedCards() const;

    /**
     * Clears the playedCards list by appending its content
     * to the graveyard.
     */
    void clearPlayedCards();


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
    void playerJoinedGame(int gameId, const StructPlayer&);
    void playerLeavedGame(int gameId, const StructPlayer&);
    void incomingMessage(int senderId, const QString& senderName, const QString& message);
    void chatMessage(int senderId, const QString& senderName, const QString& message);
    void statusChanged(const GameState&);
    void gameStarted(const StructGame&, const StructPlayerList&);
    void startableChanged(int gameId, bool startable);

    void playerDrawedCard(Player* player, CardAbstract* card);

private slots:
    void checkStartable();
private:

    void shufflePlayers();
    void shuffleDeck();
    void setRoles();
    void generateCards();
    void dealCards();
    CardAbstract* popCardFromDeck();
    int uniqueCardId();
    QList<PlayerRole> getRoleList();
    void regenerateDeck();

public:
    void drawCard(Player* p, int count = 1);


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
    bool                 m_startable;

    int m_playerOnTurnId; /// index to m_playerList

    QList<CardAbstract*> m_deck;
    QList<CardAbstract*> m_graveyard;
    QList<CardPlayable*> m_playedCards;
    QMap<int, CardAbstract*> m_cards;

signals:


};

#endif
