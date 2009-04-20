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

#include <QtDebug>
#include "card.h"

using namespace client;

QMap<PlayingCardType, Card*> Card::sm_playingCards;
QMap<PlayerRole,      Card*> Card::sm_roleCards;
QMap<CharacterType,   Card*> Card::sm_characterCards;

Card::Card(const QString& name, PlayingCardType playingCardType, const QString& imageFileName):
        m_name(name),
        m_type(Card::Playing),
        m_imageFileName(imageFileName)

{
    if (sm_playingCards.contains(playingCardType)) {
        qCritical("Unable to create a playing card. Given type already created.");
        return;
    }
    loadPixmap();
    sm_playingCards[playingCardType] = this;
}

Card::Card(const QString& name, PlayerRole role, const QString& imageFileName):
        m_name(name),
        m_type(Card::Role),
        m_imageFileName(imageFileName)

{
    if (sm_roleCards.contains(role)) {
        qCritical("Unable to create a role card. Given role card already created.");
        return;
    }
    loadPixmap();
    sm_roleCards[role] = this;
}

Card::Card(const QString& name, CharacterType character, const QString& imageFileName):
        m_name(name),
        m_type(Card::Character),
        m_imageFileName(imageFileName)
{
    if (sm_characterCards.contains(character)) {
        qCritical("Unable to create a character card. Given character card already created.");
        return;
    }
    loadPixmap();
    sm_characterCards[character] = this;
}

void Card::loadDefaultRuleset()
{
    new Card("Bang!",       CARD_BANG,       ":/cards/gfx/cards/bang.png");
    new Card("Mancato",     CARD_MISSED,     ":/cards/gfx/cards/missed.png");
    new Card("Birra",       CARD_BEER,       ":/cards/gfx/cards/beer.png");
    new Card("Mustang",     CARD_MUSTANG,    ":/cards/gfx/cards/mustang.png");
    new Card("Appaloosa",   CARD_APPALOSSA,  ":/cards/gfx/cards/appaloosa.png");
    new Card("Barrel",      CARD_BARREL,     ":/cards/gfx/cards/barrel.png");

    new Card("Volcanic",    CARD_VOLCANIC,   ":/cards/gfx/cards/volcanic.png");
    new Card("Schofield",   CARD_SCHOFIELD,  ":/cards/gfx/cards/schofield.png");
    new Card("Winchester",  CARD_WINCHESTER, ":/cards/gfx/cards/winchester.png");
    new Card("Remington",   CARD_REMINGTON,  ":/cards/gfx/cards/remington.png");
    new Card("Carabine",    CARD_CARABINE,   ":/cards/gfx/cards/carabine.png");




    new Card("",         CARD_UNKNOWN, ":/cards/gfx/cards/back-bang.png");

    new Card("Sheriff",  ROLE_SHERIFF,    "");
    new Card("Renegade", ROLE_RENEGADE,   "");
    new Card("Outlaw",   ROLE_OUTLAW,     "");
    new Card("Deputy",   ROLE_DEPUTY,     "");

    new Card("Back Bullets", CHARACTER_UNKNOWN,    ":/cards/gfx/cards/back-bullets.png");
    }


const Card* Card::findPlayingCard(PlayingCardType id)
{
    return (sm_playingCards.contains(id) ? sm_playingCards[id] : 0);
}

const Card* Card::findRoleCard(PlayerRole id)
{
    return (sm_roleCards.contains(id) ? sm_roleCards[id] : 0);
}

const Card* Card::findCharacterCard(CharacterType id)
{
    return (sm_characterCards.contains(id) ? sm_characterCards[id] : 0);
}

void Card::loadPixmap()
{
    if (!m_image.load(m_imageFileName)) {
        qWarning(qPrintable(QString("Cannot load pixmap: %1").arg(m_imageFileName)));
    }
}
