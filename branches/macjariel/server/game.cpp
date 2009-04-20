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

#include <QXmlStreamWriter>
#include <QTimer>

#include <stdlib.h>

#include "game.h"
#include "gameserver.h"
#include "client.h"
#include "player.h"
#include "common.h"
#include "cards.h"
#include "util.h"
#include "gameexceptions.h"


#include "gameinfo.h"
#include "gametable.h"
#include "gamecycle.h"


Game::Game(GameServer* parent, const StructGame& structGame):
    QObject(parent),
    m_publicGameView(this),
    m_nextUnusedPlayerId(0),
    m_gameState(GAMESTATE_WAITINGFORPLAYERS),
    m_startable(0)
{
    mp_gameInfo = new GameInfo(structGame);
    mp_gameTable = new GameTable(this);
    mp_gameCycle = new GameCycle(this);
}

Game::~Game()
{
    delete mp_gameInfo;
    delete mp_gameTable;
    delete mp_gameCycle;
}

int Game::id() const
{
    return mp_gameInfo->id();
}

Player* Game::player(int playerId)
{
    if (m_playerMap.contains(playerId))
        return m_playerMap[playerId];
    return 0;
}

Player* Game::nextPlayer(Player* currentPlayer) {
    QListIterator<Player*> it(m_playerList);
    if (!it.findNext(currentPlayer))
        return 0;
    // Now the it points right after the currentPlayer

    // If the currentPlayer is last in list, rewind
    if (!it.hasNext())
        it.toFront();

    while (!it.peekNext()->isAlive()) {
        // @invariant: the player after the iterator is dead
        it.next();
        if (!it.hasNext())
            it.toFront();
    }
    // The player after the iterator is the first alive player
    // after the currentPlayer
    return it.next();
}

int Game::getDistance(Player *fromPlayer, Player *toPlayer) const
{
    static int infiniteDistance = 99;
    if (!fromPlayer->isAlive() || !toPlayer->isAlive())
        return infiniteDistance;

    int fromIndex = m_playerList.indexOf(fromPlayer);
    int toIndex   = m_playerList.indexOf(toPlayer);
    if (fromIndex == -1 || toIndex == -1)
        return infiniteDistance;

    int upIndex   = fromIndex;
    int downIndex = fromIndex;
    int baseDistance = 0;
    while (upIndex != toIndex && downIndex != toIndex) {
        upIndex++;
        if (upIndex == m_playerList.size()) upIndex = 0;
        downIndex--;
        if (downIndex == -1)
            downIndex = m_playerList.size() - 1;
        baseDistance++;
    }

    baseDistance -= fromPlayer->distanceOut();
    baseDistance += toPlayer->distanceIn();
    return baseDistance;
}

Player* Game::createPlayer(StructPlayer structPlayer,
                              GameEventHandler* gameEventHandler)
{
    if (m_gameState != GAMESTATE_WAITINGFORPLAYERS) {
        throw BadGameStateException();
    }
    while ((m_nextUnusedPlayerId == 0) || m_playerMap.contains(m_nextUnusedPlayerId))
    {
        m_nextUnusedPlayerId++;
    }
    Player* newPlayer = new Player(this, m_nextUnusedPlayerId, structPlayer.name, structPlayer.password, gameEventHandler);
    m_playerMap[m_nextUnusedPlayerId] = newPlayer;
    m_playerList.append(newPlayer);
    m_publicPlayerList.append(&newPlayer->publicView());

    // The first connected player is the creator and can start the game
    if (mp_gameInfo->creatorId() == 0) {
        mp_gameInfo->setCreatorId(m_nextUnusedPlayerId);
    }

    foreach(Player* p, m_playerList) {
        p->gameEventHandler()->onPlayerJoinedGame(newPlayer->publicView());
    }
    checkStartable();
    return newPlayer;
}

/**
 * @TODO: When the creator disconnects, cancel the game.
 */
void Game::removePlayer(Player* player)
{
    Q_ASSERT(player->game() == this);
    int playerId = player->id();
    Q_ASSERT(m_playerMap.contains(playerId));
    Q_ASSERT(m_playerMap[playerId] == player);
    qDebug(qPrintable(QString("Removing player #%1.").arg(playerId)));

    if (player->isCreator() && m_gameState == GAMESTATE_WAITINGFORPLAYERS) {
        foreach(Player* p, m_playerList) {
            p->gameEventHandler()->onPlayerExit();
        }
        GameServer::instance().removeGame(this);
        return;
    }
    m_publicPlayerList.removeAll(&player->publicView());
    m_playerList.removeAll(player);
    m_playerMap.remove(playerId);

    player->gameEventHandler()->onPlayerExit();
    foreach(Player* p, m_playerList) {
        p->gameEventHandler()->onPlayerLeavedGame(player->publicView());
    }
    checkStartable();
    player->deleteLater();
}

void Game::buryPlayer(Player* player)
{
    Q_ASSERT(player->lifePoints() == 0);
    Q_ASSERT(player->isAlive());
    player->setAlive(0);

    foreach(PlayingCard* card, player->hand())
        gameTable().playerDiscardCard(card);

    foreach(PlayingCard* card, player->table())
        gameTable().playerDiscardCard(card);

    /// @todo

    /// announce decease to family members :)
}

void Game::startGame(Player* player)
{
    if (player->id() != mp_gameInfo->creatorId()) {
        throw BadPlayerException(player->id());
    }
    if (m_gameState != GAMESTATE_WAITINGFORPLAYERS) {
        throw BadGameStateException();
    }
    if (!m_startable) {
        throw BadGameStateException();
    }
    m_gameState = GAMESTATE_PLAYING;
    if (mp_gameInfo->hasShufflePlayers())
        shufflePlayers();
    //setCharacters();
    setRoles();

    // Announce that game started
    foreach(Player* player, m_playerList) {
        player->gameEventHandler()->onGameStarted();
    }
    mp_gameTable->prepareGame(GameServer::instance().cardFactory());
    mp_gameCycle->start();
}


void Game::sendMessage(Player* player, const QString& message)
{
    foreach(Player* p, m_playerList) {
        p->gameEventHandler()->onIncomingMessage(player->publicView(), message);
    }
}





void Game::checkStartable()
{
    bool newStartable;
    if (m_playerList.count() >= mp_gameInfo->minPlayers() &&
            m_playerList.count() <= mp_gameInfo->maxPlayers())
        newStartable = 1;
    else
        newStartable = 0;
    if (m_startable != newStartable)
        m_playerMap[mp_gameInfo->creatorId()]->gameEventHandler()->onGameStartabilityChanged(newStartable);
    m_startable = newStartable;
}

void Game::shufflePlayers()
{
    shuffleList(m_playerList);
    m_publicPlayerList.clear();
    foreach(Player* player, m_playerList) {
        m_publicPlayerList.append(&player->publicView());
    }
}

void Game::setRoles()
{
    QList<PlayerRole> roles = getRoleList();
    shuffleList(roles);
    QListIterator<Player*> pIt(m_playerList);
    QListIterator<PlayerRole> rIt(roles);
    int i = 0;
    while(pIt.hasNext() && rIt.hasNext())
    {
        pIt.peekNext()->setRole(rIt.peekNext());
        i++;
        pIt.next(); rIt.next();
    }
}

QList<PlayerRole> Game::getRoleList()
{
    static char* roleSets[] = {"", "S", "SB", "SVB", "SVBR", "SVBBR", "SVVBBR", "SVVBBBR"};
    QList<PlayerRole> res;
    char* i = roleSets[m_playerList.count()];
    while(*i != '\0')
    {
        switch(*i)
        {
            case 'S': res.append(ROLE_SHERIFF); break;
            case 'B': res.append(ROLE_OUTLAW); break;
            case 'V': res.append(ROLE_DEPUTY); break;
            case 'R': res.append(ROLE_RENEGADE); break;
        }
        ++i;
    }
    return res;
}
