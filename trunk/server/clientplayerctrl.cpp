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
#include "clientplayerctrl.h"
#include "client.h"

ClientPlayerCtrl::ClientPlayerCtrl(Client* owner):
mp_client(owner)
{

}


ClientPlayerCtrl::~ClientPlayerCtrl()
{
}

void ClientPlayerCtrl::playTurn()
{
}

void ClientPlayerCtrl::underAttack(const PublicPlayerView & attacker, const PlayingCard & card)
{
}

const CharacterCard & ClientPlayerCtrl::pickACharacter(const CharacterCardList & characterList)
{
}

const PlayingCard & ClientPlayerCtrl::pickACard(const PlayingCardList & cardList)
{
}

void ClientPlayerCtrl::playerRecievesCards(const PublicPlayerView & player, const PlayingCardList & cardList)
{
}

void ClientPlayerCtrl::playerPlaysCard(const PublicPlayerView & player, const PlayingCard & card, const PublicPlayerView * targetPlayer, const PlayingCard * targetCard)
{
}

void ClientPlayerCtrl::playerDiscardsCard(const PublicPlayerView & player, const PlayingCardList & cardList)
{
}



