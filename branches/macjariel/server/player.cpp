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
#include "gameeventbroadcaster.h"
#include "characterbase.h"

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
        mp_character(0),
        m_isAlive(1),
        mp_game(game),
        mp_gameEventHandler(0),
        m_weaponRange(1),
        m_distanceIn(0),
        m_distanceOut(0),
        m_lastBangTurn(-1),
        m_unlimitedBangs(0),
        m_bangPower(1),
        m_publicPlayerView(this),
        m_privatePlayerView(this)
{
    mp_playerCtrl = new PlayerCtrl(this);
    registerGameEventHandler(gameEventHandler);
    m_predrawChecks.append(0);
}

Player::~Player()
{
    unregisterGameEventHandler();
}


CharacterType Player::characterType() const
{
    if (mp_character == 0)
        return CHARACTER_UNKNOWN;
    return mp_character->characterType();
}

bool Player::isCreator() const
{
    return (mp_game->gameInfo().creatorId() == m_id);
}

bool Player::isOnTurn() const
{
    return (mp_game->gameCycle().currentPlayer() == this);
}

bool Player::isRequested() const
{
    return (mp_game->gameCycle().requestedPlayer() == this);
}

bool Player::hasIdenticalCardOnTable(PlayingCard* card) const
{
    foreach(PlayingCard* c, m_table) {
        if (card->type() == c->type())
            return 1;
    }
    return 0;
}

bool Player::canPlayBang() const
{
    return (m_unlimitedBangs > 0 || m_lastBangTurn != mp_game->gameCycle().turnNumber());
}

void Player::modifyLifePoints(int x, Player* causedBy, bool disableBeerRescue)
{
    int oldLifePoints = m_lifePoints;
    m_lifePoints += x;
    if (m_lifePoints > m_maxLifePoints)
        m_lifePoints = m_maxLifePoints;

    if (oldLifePoints != m_lifePoints) {
        game()->gameEventBroadcaster().onLifePointsChange(this, m_lifePoints, causedBy);
    }
    int hitPoints = oldLifePoints - m_lifePoints;

    if (m_lifePoints <= 0) {
        if (disableBeerRescue) 
            mp_game->buryPlayer(this, causedBy);
        else
            mp_game->beerRescue()->allowSaveWithBeer(causedBy, this, 1 - m_lifePoints);
    } else {

        if (hitPoints > 0)
            // TODO: tune emiting this signal when on the fly beer is used
            emit onHit(hitPoints, causedBy);
    }
}

void Player::modifyDistanceIn(int delta)
{
    m_distanceIn += delta;
}

void Player::modifyDistanceOut(int delta)
{
    m_distanceOut += delta;
}

void Player::modifyUnlimitedBangs(int delta)
{
    m_unlimitedBangs += delta;
}

void Player::setBangPower(int bangPower)
{
    m_bangPower = bangPower;
}

void Player::setWeaponRange(int weaponRange)
{
    m_weaponRange = weaponRange;
}

void Player::setAlive(bool isAlive)
{
    m_isAlive = isAlive;
}

void Player::appendCardToHand(PlayingCard * card)
{
    m_hand.append(card);
}

void Player::appendCardToTable(PlayingCard* card)
{
    m_table.append(card);
}

void Player::appendCardToSelection(PlayingCard* card)
{
    m_selection.append(card);
}

bool Player::removeCardFromHand(PlayingCard* card)
{
    return m_hand.removeOne(card);
}

PlayingCard* Player::getRandomCardFromHand()
{
    int size = m_hand.size();
    if (size == 0) return 0;
    return m_hand[rand() % size];
}

bool Player::removeCardFromTable(PlayingCard* card)
{
    return m_table.removeOne(card);
}

bool Player::removeCardFromSelection(PlayingCard* card)
{
    return m_selection.removeOne(card);
}

void Player::setRoleAndCharacter(const PlayerRole& role, CharacterBase* character)
{
    Q_ASSERT(mp_character == 0);
    m_role = role;
    mp_character = character;
    mp_character->setPlayer(this);
    m_maxLifePoints = character->maxLifePoints();
    if (m_role == ROLE_SHERIFF) {
        m_maxLifePoints++;
    }

    m_lifePoints = m_maxLifePoints;
}

void Player::registerPredrawCheck(int priority)
{
    m_predrawChecks.append(priority);
    qSort(m_predrawChecks.begin(), m_predrawChecks.end());
}

void Player::unregisterPredrawCheck(int priority)
{
    m_predrawChecks.removeAll(priority);
}

void Player::predrawCheck(int checkId)
{
    if (m_currentPredraw != checkId)
        throw BadPredrawException();
    if (checkId == 0)
        return;
    int index = m_predrawChecks.indexOf(checkId);
    Q_ASSERT(index > 0);
    m_currentPredraw = m_predrawChecks[index - 1];
}

void Player::onBangPlayed()
{
    m_lastBangTurn = mp_game->gameCycle().turnNumber();
}

void Player::onTurnStart()
{
    m_currentPredraw = m_predrawChecks.last();
}


void Player::registerGameEventHandler(GameEventHandler* gameEventHandler)
{
    Q_ASSERT(mp_gameEventHandler == 0);
    mp_gameEventHandler = gameEventHandler;
    mp_game->gameEventBroadcaster().registerHandler(mp_gameEventHandler, this);
    mp_gameEventHandler->onHandlerRegistered(mp_playerCtrl);
}

void Player::unregisterGameEventHandler()
{
    if (mp_gameEventHandler == 0) return;
    mp_game->gameEventBroadcaster().unregisterHandler(mp_gameEventHandler, this);
    mp_gameEventHandler->onHandlerUnregistered();
    mp_gameEventHandler = 0;
}


void Player::checkEmptyHand()
{
    if (m_hand.size() == 0) {
        qDebug() << "onEmptyHand()";
        emit onEmptyHand();
    }
}

