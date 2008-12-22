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
 *   Free Software Foundation, Inc.,                         mp_streamWriter->writeAttribute("senderName", senderName);
                  *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QXmlStreamWriter>

#include <stdlib.h>

#include "game.h"
#include "gameserver.h"
#include "client.h"
#include "player.h"
#include "common.h"
#include "cards.h"
#include "util.h"


Game::Game(GameServer* parent, const StructGame& g):
QObject(parent),
m_gameId(g.id),
m_name(g.name),
m_description(g.description),
m_creatorId(g.creatorId),
m_minPlayers(g.minPlayers),
m_maxPlayers(g.maxPlayers),
m_maxObservers(g.maxSpectators),
m_playerPassword(g.playerPassword),
m_observerPassword(g.spectatorPassword),
m_shufflePlayers(g.flagShufflePlayers),
m_nextPlayerId(0),
m_gameState(WaitingForPlayers),
m_publicGameView(this)

{
    Q_ASSERT(!m_name.isEmpty());
    Q_ASSERT(m_minPlayers <= m_maxPlayers);
    Q_ASSERT(m_observerPassword.isNull() || !m_playerPassword.isNull()); // observerPassword implies playerPassword
}


Game::~Game()
{
}


Player* Game::createNewPlayer(StructPlayer player)
{
    qDebug(qPrintable(QString("Creating new player #%1 (%2).").arg(player.id).arg(player.name)));
    if (m_gameState != WaitingForPlayers) return 0;
    while (!m_nextPlayerId || m_players.contains(m_nextPlayerId))
    {
        m_nextPlayerId++;
    }
    Player* newPlayer = new Player(m_nextPlayerId, player.name, player.password, this);
    m_players[m_nextPlayerId] = newPlayer;
    m_playerList.append(newPlayer);
    emit playerJoinedGame(m_gameId, newPlayer->structPlayer());
    return newPlayer;
}

void Game::removePlayer(int playerId)
{
    Q_ASSERT(m_players.contains(playerId));
    qDebug(qPrintable(QString("Removing player #%1.").arg(playerId)));
    StructPlayer p = m_players[playerId]->structPlayer();
    Player* plr = m_players[playerId];
    m_playerList.removeAll(m_players[playerId]);
    m_players.remove(playerId);
    emit playerLeavedGame(m_gameId, p);
    plr->deleteLater();
    // TODO: other states of game
}




QList<Player *> Game::playerList()
{
    return m_playerList;
}

void Game::sendMessage(Player* player, const QString& message)
{
    emit incomingMessage(player->id(), player->name(), message);
}

StructGame Game::structGame() const
{
    StructGame r;
    r.id = m_gameId;
    r.creatorId = m_creatorId;
    r.name = m_name;
    r.description = m_description;
    r.minPlayers = m_minPlayers;
    r.maxPlayers = m_maxPlayers;
    r.maxSpectators = m_maxObservers;
    r.playerPassword = m_playerPassword;
    r.spectatorPassword = m_observerPassword;
    r.hasPlayerPassword = (!m_playerPassword.isNull());
    r.hasSpectatorPassword = (!m_observerPassword.isNull());
    r.flagShufflePlayers = m_shufflePlayers;
    return r;
}


StructPlayerList Game::structPlayerList() const
{
    StructPlayerList r;
    foreach(Player* i, m_playerList)
    {
        r.append(i->structPlayer());
    }
    return r;
}



void Game::startGame()
{
    qDebug() << "Start Game";
    if (m_gameState != WaitingForPlayers) return; /* TODO: error handling */
    // TODO: character selection first
    qDebug() << "Start Game #2";
    m_gameState = Playing;
    if (m_shufflePlayers) shufflePlayers();
    setRoles();
    generateCards();
    dealCards();
    statusChanged(m_gameState);
    // TODO: start game
}

void Game::shufflePlayers()
{
    shuffleList(m_playerList);
}

void Game::shuffleDeck()
{
    shuffleList(m_deck);
}

void Game::dealCards()
{
    int cardCount = 0, players = 0;
    do {
        players = 0;
        foreach(Player* p, m_playerList)
        {
            if (p->initialCardCount() > cardCount)
            {
                drawCard(p);
                players++;
            }
        }
        cardCount++;
    } while(players != 0);
}


void Game::setRoles()
{
    QList<PlayerRole> roles = getRoleList();
    // TODO: shuffle roles list
    QListIterator<Player*> pIt(m_playerList);
    QListIterator<PlayerRole> rIt(roles);
    int i = 0;
    while(pIt.hasNext() && rIt.hasNext())
    {
        pIt.peekNext()->setRole(rIt.peekNext());
        if (rIt.peekNext() == ROLE_SHERIFF)
            m_playerOnTurnId = i;
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
            case 'B': res.append(ROLE_BANDITA); break;
            case 'V': res.append(ROLE_DEPUTY); break;
            case 'R': res.append(ROLE_RENEGADE); break;
        }
        ++i;
    }
    return res;
}

void Game::generateCards()
{
    static const int nBang = 20;
    static const int nMissed = 20;
    for(int i = 0; i < nBang; ++i)
    {
        int id = uniqueCardId();
        m_cards[id] = new CardBang(this, id);
    }
    for(int i = 0; i < nMissed; ++i)
    {
        int id = uniqueCardId();
        m_cards[id] = new CardMissed(this, id);
    }
    m_deck << m_cards.values();
}

int Game::uniqueCardId()
{
    int id;
    do {
        id = (int)random();
    } while(m_cards.contains(id));
    return id;
}



bool Game::isBaseTurn() const
{
    return m_playedCards.isEmpty();
}

Player* Game::playerOnTurn() const
{
    return m_playerList[m_playerOnTurnId];
}

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

void Game::drawCard(Player *p, int count)
{
    for(int i = 0; i < count; ++i)
    {
        CardAbstract* card = popCardFromDeck();
        p->appendCardToHand(card);
        emit playerDrawedCard(p, card);
    }
}

CardAbstract* Game::popCardFromDeck()
{
    if (m_deck.isEmpty()) regenerateDeck();
    return m_deck.takeFirst();
}

void Game::regenerateDeck()
{
    Q_ASSERT(m_deck.isEmpty());
    Q_ASSERT(!m_graveyard.isEmpty());
    m_deck << m_graveyard;
    m_graveyard.clear();
    m_graveyard << m_deck.takeLast();
    shuffleList(m_graveyard);
}



