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
#include "player.h"
#include "game.h"
#include "client.h"
#include "cards.h"
#include "playerctrl.h"


#include "gameinfo.h"
#include "gamecycle.h"


Player::Player(Game* game,
               int id,
               const QString& name,
               const QString& password,
               GameEventHandler* gameEventHandler):
        QObject(game),
        m_id(id),
        m_name(name),
        m_password(password),
        m_role(ROLE_UNKNOWN),
        mp_game(game),
        mp_gameEventHandler(gameEventHandler),
        m_lastBangTurn(-1),
        m_publicPlayerView(this),
        m_privatePlayerView(this)
{
    qDebug(qPrintable(QString("Creating new player #%1 (%2).").arg(m_id).arg(m_name)));
    //    mp_client->mp_player = this;
    //    m_id = mp_game->appendNewPlayer(this);
    mp_playerCtrl = new PlayerCtrl(this);
    mp_gameEventHandler->onPlayerInit(mp_playerCtrl);
}

PlayerCtrl* Player::playerCtrl() const
{
    return mp_playerCtrl;
}

const int Player::id() const
{
    return (this != 0) ? m_id : 0;
}

QString Player::name() const
{
    return m_name;
}

/*
void Player::sendMessage(const QString& message)
{
    mp_game->sendMessage(this, message);
}
*/

StructPlayer Player::structPlayer(bool returnPrivateInfo)
{
    StructPlayer x;
    x.id = m_id;
    x.name = m_name;
    x.password = m_password;
    if (returnPrivateInfo || x.role == ROLE_SHERIFF)
    {
        x.role = m_role;
    } else {
        x.role = ROLE_UNKNOWN;
    }
    return x;
}

GameEventHandler* Player::gameEventHandler() const {
    return mp_gameEventHandler;
}

Game* Player::game() const
{
    return mp_game;
}

bool Player::isCreator() const
{
    return (mp_game->gameInfo().creatorId() == m_id);
}

bool Player::isOnTurn() const
{
    return (mp_game->gameCycle().currentPlayer() == this);
}

QList<CardAbstract*> Player::cardsInHand()
{
    return m_cardsInHand;
}

QList<CardAbstract*> Player::table()
{
    return m_table;
}

bool Player::hasDuplicateOnTable(CardAbstract* card)
{
    foreach(CardAbstract* c, m_table) {
        if (card->type() == c->type())
            return 1;
    }
    return 0;
}

void Player::modifyLifePoints(int x)
{
    int oldLifePoints = m_lifePoints;
    m_lifePoints += x;
    if (m_lifePoints > m_maxLifePoints)
        m_lifePoints = m_maxLifePoints;

    if (m_lifePoints < 0)
        m_lifePoints = 0;

    if (oldLifePoints == m_lifePoints)
        return;

    foreach (Player* p, mp_game->playerList()) {
        p->gameEventHandler()->onLifePointsChange(publicView(), oldLifePoints, m_lifePoints);
    }
}

void Player::appendCardToHand(CardAbstract * card)
{
    m_cardsInHand.append(card);
}

void Player::appendCardToTable(CardAbstract* card)
{
    m_table.append(card);
}

bool Player::removeCardFromHand(CardAbstract* card)
{
    return m_cardsInHand.removeOne(card);
}

bool Player::removeCardFromTable(CardAbstract* card)
{
    return m_table.removeOne(card);
}


const PublicPlayerView& Player::publicView() const
{
    return m_publicPlayerView;
}

const PrivatePlayerView& Player::privateView() const
{
    return m_privatePlayerView;
}

void Player::setRole(const PlayerRole& role)
{
    m_role = role;
    if (m_role == ROLE_SHERIFF) {
        m_maxLifePoints = 5;
    } else {
        m_maxLifePoints = 4;
    }
    // TODO: character can influence maxLifePoints

    m_lifePoints = m_maxLifePoints;
}


void Player::onBangPlayed()
{
    m_lastBangTurn = mp_game->gameCycle().turnNumber();
}

bool Player::canPlayBang()
{
    return (m_lastBangTurn != mp_game->gameCycle().turnNumber());
}

int Player::initialCardCount() const
{
    return m_maxLifePoints;
}




