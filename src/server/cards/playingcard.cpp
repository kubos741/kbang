/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
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

#include "cards/playingcard.h"
#include "game.h"
#include "gametable.h"
#include "gameexceptions.h"
#include "player.h"
#include "util.h"

PlayingCard::PlayingCard(Game *game, CardId id, PlayingCardName name,
                         CardSuit suit, CardRank rank):
        QObject(game),
        m_cardData(id, playingCardNameToCardName(name),
                   CARDTYPE_PLAYING, suit, rank, 0),
        m_name(name),
        mp_owner(0),
        m_pocket(POCKET_INVALID),
        mp_game(game),
        m_isRevealed(0),
        m_isVirtual(0)
{
}

/* virtual */
PlayingCard::~PlayingCard()
{
}

/* virtual */ void
PlayingCard::play()
{
   throw BadUsageException();
}

/* virtual */ void
PlayingCard::play(Player* targetPlayer)
{
    Q_UNUSED(targetPlayer);
    throw BadUsageException();
}

/* virtual */
void PlayingCard::play(PlayingCard* targetCard)
{
    Q_UNUSED(targetCard);
    throw BadUsageException();
}

void
PlayingCard::assertInHand() const
{
    if (pocketType() != POCKET_HAND) {
        throw BadCardException();
    }
}

void
PlayingCard::assertOnTable() const
{
    if (pocketType() != POCKET_TABLE) {
        throw BadCardException();
    }
}

void
PlayingCard::setVirtual(PlayingCard* master)
{
    mp_master       = master;
    m_cardData      = master->cardData();
    m_cardData.id   = 0;
    m_isVirtual     = 1;
    mp_owner        = master->owner();
    m_pocketType    = master->pocketType();
    mp_game         = master->game();
}

void
PlayingCard::setVirtual(Player* owner, PocketType pocketType)
{
    mp_master     = 0;
    m_isVirtual   = 1;
    m_cardData.id = 0;
    mp_owner      = owner;
    m_pocketType  = pocketType;
}

GameTable*
PlayingCard::gameTable() const
{
    return mp_game->ga
            &mp_game->gameTable();
}

GameCycle*
PlayingCard::gameCycle() const
{
    return &mp_game->gameCycle();
}

void
PlayingCard::setName(PlayingCardName name)
{
    m_name = name;
    m_cardData.name = playingCardNameToCardName(m_name);
}

void
PlayingCard::discard()
{
    Q_ASSERT(!isVirtual());
    move(0, POCKET_GRAVEYARD);
}


void
PlayingCard::move(Player* newOwner, PocketType newPocketType)
{
    removeFromPocket();
    mp_owner = newOwner;
    m_pocketType = newPocketType;
    insertIntoPocket();
    ///@todo Emit cardMovementEvent
}

void
PlayingCard::insertIntoPocket()
{
    switch(pocketType()) {
        case POCKET_DECK:
            gameTable()->appendCardToDeck(this);
            m_isRevealed = 0;
            break;
        case POCKET_GRAVEYARD:
            gameTable()->appendCardToGraveyard(this);
            m_isRevealed = 1;
            break;
        case POCKET_HAND:
            owner()->appendCardToHand(this);
            m_isRevealed = 0;
            break;
        case POCKET_TABLE:
            owner()->appendCardToTable(this);
            m_isRevealed = 1;
            break;
        case POCKET_SELECTION:
            gameTable()->appendCardToSelection(this);
            m_isRevealed = (owner() == 0);
            break;
        default:
            NOT_REACHED();
    }
}

void
PlayingCard::removeFromPocket()
{
    switch(pocketType()) {
        case POCKET_INVALID:
        case POCKET_DECK:
        case POCKET_GRAVEYARD:
            break;
        case POCKET_HAND:
            owner()->removeCardFromHand(this);
            break;
        case POCKET_TABLE:
            owner()->removeCardFromTable(this);
            break;
        case POCKET_SELECTION:
            gameTable()->removeFromSelection(this);
            break;
    }
    m_pocketType = POCKET_INVALID;
    mp_owner = 0;
    m_isRevealed = 0;
}
