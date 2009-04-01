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
    m_nextPlayerId(0),
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

int Game::playersCount() const
{
    return m_playerList.size();
}

int Game::spectatorsCount() const
{
    return 0;  /// \todo spectators
}

const GameInfo& Game::gameInfo() const
{
    return *mp_gameInfo;
}

const GameCycle& Game::gameCycle() const
{
    return *mp_gameCycle;
}

const PublicGameView& Game::publicGameView() const
{
    return m_publicGameView;
}

QList<Player*> Game::playerList() const {
    return m_playerList;
}

QList<const PublicPlayerView*> Game::publicPlayerList() const {
    return m_publicPlayerList;
}

int Game::nextPlayerId(int currentPlayerId) const {
    QListIterator<Player*> it(m_playerList);
    while (it.hasNext()) {
        if (it.next()->id() == currentPlayerId)
            break;
    }

    /* TODO: Implement dead palyers */
    if (!it.hasNext())
        it.toFront();
    return it.next()->id();
}

/*
StructPlayerList Game::structPlayerList(Player* privatePlayer) const
{
    StructPlayerList r;
    foreach(Player* i, m_playerList)
    {
        r.append(i->structPlayer(privatePlayer == i));
    }
    return r;
}
*/

Player* Game::getPlayer(int playerId)
{
    if (m_playerMap.contains(playerId))
        return m_playerMap[playerId];
    return 0;
}

Player* Game::createNewPlayer(StructPlayer structPlayer,
                              GameEventHandler* gameEventHandler)
{
    qDebug(qPrintable(QString("Creating new player #%1 (%2).").arg(structPlayer.id).arg(structPlayer.name)));
    if (m_gameState != GAMESTATE_WAITINGFORPLAYERS) {
        throw BadGameStateException();
    }
    while ((m_nextPlayerId == 0) || m_playerMap.contains(m_nextPlayerId))
    {
        m_nextPlayerId++;
    }
    Player* newPlayer = new Player(this, m_nextPlayerId, structPlayer.name, structPlayer.password, gameEventHandler);
    m_playerMap[m_nextPlayerId] = newPlayer;
    m_playerList.append(newPlayer);
    m_publicPlayerList.append(&newPlayer->publicView());

    foreach(Player* p, m_playerList) {
        p->gameEventHandler()->onPlayerJoinedGame(newPlayer->publicView());
    }
    checkStartable();
    return newPlayer;
}

void Game::removePlayer(Player* player)
{
    Q_ASSERT(player->game() == this);
    int playerId = player->id();
    Q_ASSERT(m_playerMap.contains(playerId));
    Q_ASSERT(m_playerMap[playerId] == player);
    qDebug(qPrintable(QString("Removing player #%1.").arg(playerId)));
    StructPlayer structPlayer = player->structPlayer();
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


void Game::sendMessage(Player* player, const QString& message)
{
    foreach(Player* p, m_playerList) {
        p->gameEventHandler()->onIncomingMessage(player->publicView(), message);
    }
}

void Game::startGame(Player* player)
{
    if (player->id() != mp_gameInfo->creatorId()) {
        throw BadPlayerException(player->id());
    }
    if (m_gameState != GAMESTATE_WAITINGFORPLAYERS) {
        throw BadGameStateException();
    }

    // \todo: character selection first

    m_gameState = GAMESTATE_PLAYING;

    if (mp_gameInfo->hasShufflePlayers()) shufflePlayers();
    //setCharacters();
    setRoles();
    mp_gameTable->prepareGame();

    // Announce that game started
    foreach(Player* player, m_playerList) {
        player->gameEventHandler()->onGameStarted();
    }




}

void Game::shufflePlayers()
{
    shuffleList(m_playerList);
    m_publicPlayerList.empty();
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
        if (rIt.peekNext() == ROLE_SHERIFF)
            mp_gameTable->setPlayerOnTurn(pIt.peekNext());
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




/*
void Game::appendPlayedCard(CardPlayable *card)
{
    m_playedCards.append(card);
}

CardPlayable* Game::peakPlayedCards() const
{
    if (m_playedCards.isEmpty()) return 0;
    return m_playedCards.last();
}

void Game::clearPlayedCards()
{
    foreach(CardAbstract* card, m_playedCards)
    {
        m_graveyard << card;
    }
    m_playedCards.clear();
}
*/

int Game::getDistance(Player *fromPlayer, Player *toPlayer)
{
    int i = m_playerList.indexOf(fromPlayer);
    int j = m_playerList.indexOf(toPlayer);
    if (i == -1 || j == -1) return -1;
    int d = (i - j > 0) ? i - j : j - i;
    if (d > (m_playerList.size() / 2))
    {
        d = m_playerList.size() - d;
    }
    // TODO: NOW ADD EFFECTS OF HORSES
    return d;
}


void Game::checkStartable()
{
    bool newStartable;
    if (m_playerList.count() >= mp_gameInfo->minPlayers() && m_playerList.count() <= mp_gameInfo->maxPlayers())
    {
        newStartable = 1;
    }
    else
    {
        newStartable = 0;
    }
    if (m_startable != newStartable)
        emit startableChanged(id(), newStartable);
    m_startable = newStartable;
}



