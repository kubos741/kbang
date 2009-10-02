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

#ifndef SERVERTYPES_H
#define SERVERTYPES_H

#include "gametypes.h"

enum PlayingCardName {
    CARD_UNKNOWN = 0,
    CARD_BANG,
    CARD_MISSED,
    CARD_BEER,
    CARD_SALOON,
    CARD_WELLSFARGO,
    CARD_DILIGENZA,
    CARD_GENERALSTORE,
    CARD_PANIC,
    CARD_CATBALOU,
    CARD_INDIANS,
    CARD_DUEL,
    CARD_GATLING,
    CARD_MUSTANG,
    CARD_APPALOSSA,
    CARD_BARREL,
    CARD_DYNAMITE,
    CARD_JAIL,
    CARD_VOLCANIC,
    CARD_SCHOFIELD,
    CARD_REMINGTON,
    CARD_CARABINE,
    CARD_WINCHESTER
};

inline PlayingCardName cardNameToPlayingCardName(const CardName& cardName)
{
    if (cardName == "bang")             return CARD_BANG;
    if (cardName == "missed")           return CARD_MISSED;
    if (cardName == "beer")             return CARD_BEER;
    if (cardName == "saloon")           return CARD_SALOON;
    if (cardName == "wellsfargo")       return CARD_WELLSFARGO;
    if (cardName == "diligenza")        return CARD_DILIGENZA;
    if (cardName == "generalstore")     return CARD_GENERALSTORE;
    if (cardName == "panic")            return CARD_PANIC;
    if (cardName == "catbalou")         return CARD_CATBALOU;
    if (cardName == "indians")          return CARD_INDIANS;
    if (cardName == "duel")             return CARD_DUEL;
    if (cardName == "gatling")          return CARD_GATLING;
    if (cardName == "mustang")          return CARD_MUSTANG;
    if (cardName == "appalossa")        return CARD_APPALOSSA;
    if (cardName == "barrel")           return CARD_BARREL;
    if (cardName == "dynamite")         return CARD_DYNAMITE;
    if (cardName == "jail")             return CARD_JAIL;
    if (cardName == "volcanic")         return CARD_VOLCANIC;
    if (cardName == "schofield")        return CARD_SCHOFIELD;
    if (cardName == "remington")        return CARD_REMINGTON;
    if (cardName == "carabine")         return CARD_CARABINE;
    if (cardName == "winchester")       return CARD_WINCHESTER;
    return CARD_UNKNOWN;
}

inline CardName playingCardNameToCardName(const PlayingCardName& c)
{
    switch(c) {
        case CARD_BANG:           return "bang";
        case CARD_MISSED:         return "missed";
        case CARD_BEER:           return "beer";
        case CARD_SALOON:         return "saloon";
        case CARD_WELLSFARGO:     return "wellsfargo";
        case CARD_DILIGENZA:      return "diligenza";
        case CARD_GENERALSTORE:   return "generalstore";
        case CARD_PANIC:          return "panic";
        case CARD_CATBALOU:       return "catbalou";
        case CARD_INDIANS:        return "indians";
        case CARD_DUEL:           return "duel";
        case CARD_GATLING:        return "gatling";
        case CARD_MUSTANG:        return "mustang";
        case CARD_APPALOSSA:      return "appalossa";
        case CARD_BARREL:         return "barrel";
        case CARD_DYNAMITE:       return "dynamite";
        case CARD_JAIL:           return "jail";
        case CARD_VOLCANIC:       return "volcanic";
        case CARD_SCHOFIELD:      return "schofield";
        case CARD_REMINGTON:      return "remington";
        case CARD_CARABINE:       return "carabine";
        case CARD_WINCHESTER:     return "winchester";
        case CARD_UNKNOWN:        return "";
    }
    return "";
}


enum CharacterType {
    CHARACTER_UNKNOWN = 0,
    CHARACTER_BART_CASSIDY,
    CHARACTER_BLACK_JACK,
    CHARACTER_CALAMITY_JANET,
    CHARACTER_EL_GRINGO,
    CHARACTER_JESSE_JONES,
    CHARACTER_JOURDONNAIS,
    CHARACTER_KIT_CARLSON,
    CHARACTER_LUCKY_DUKE,
    CHARACTER_PAUL_REGRET,
    CHARACTER_PEDRO_RAMIREZ,
    CHARACTER_ROSE_DOOLAN,
    CHARACTER_SID_KETCHUM,
    CHARACTER_SLAB_THE_KILLER,
    CHARACTER_SUZY_LAFAYETTE,
    CHARACTER_VULTURE_SAM,
    CHARACTER_WILLY_THE_KID
};

inline CharacterType stringToCharacterType(const QString& s)
{
    if (s == "slab the killer") return CHARACTER_SLAB_THE_KILLER;
    if (s == "lucky duke")      return CHARACTER_LUCKY_DUKE;
    if (s == "suzy lafayette")  return CHARACTER_SUZY_LAFAYETTE;
    if (s == "vulture sam")     return CHARACTER_VULTURE_SAM;
    if (s == "black jack")      return CHARACTER_BLACK_JACK;
    if (s == "sid ketchum")     return CHARACTER_SID_KETCHUM;
    if (s == "jourdonnais")     return CHARACTER_JOURDONNAIS;
    if (s == "el gringo")       return CHARACTER_EL_GRINGO;
    if (s == "kit carlson")     return CHARACTER_KIT_CARLSON;
    if (s == "jesse jones")     return CHARACTER_JESSE_JONES;
    if (s == "pedro ramirez")   return CHARACTER_PEDRO_RAMIREZ;
    if (s == "calamity janet")  return CHARACTER_CALAMITY_JANET;
    if (s == "rose doolan")     return CHARACTER_ROSE_DOOLAN;
    if (s == "bart cassidy")    return CHARACTER_BART_CASSIDY;
    if (s == "paul regret")     return CHARACTER_PAUL_REGRET;
    if (s == "willy the kid")   return CHARACTER_WILLY_THE_KID;
    return CHARACTER_UNKNOWN;
}

inline QString characterTypeToString(const CharacterType& t)
{
    switch(t) {
    case CHARACTER_UNKNOWN:         return "unknown";
    case CHARACTER_SLAB_THE_KILLER: return "slab the killer";
    case CHARACTER_LUCKY_DUKE:      return "lucky duke";
    case CHARACTER_SUZY_LAFAYETTE:  return "suzy lafayette";
    case CHARACTER_VULTURE_SAM:     return "vulture sam";
    case CHARACTER_BLACK_JACK:      return "black jack";
    case CHARACTER_SID_KETCHUM:     return "sid ketchum";
    case CHARACTER_JOURDONNAIS:     return "jourdonnais";
    case CHARACTER_EL_GRINGO:       return "el gringo";
    case CHARACTER_KIT_CARLSON:     return "kit carlson";
    case CHARACTER_JESSE_JONES:     return "jesse jones";
    case CHARACTER_PEDRO_RAMIREZ:   return "pedro ramirez";
    case CHARACTER_CALAMITY_JANET:  return "calamity janet";
    case CHARACTER_ROSE_DOOLAN:     return "rose doolan";
    case CHARACTER_BART_CASSIDY:    return "bart cassidy";
    case CHARACTER_PAUL_REGRET:     return "paul regret";
    case CHARACTER_WILLY_THE_KID:   return "willy the kid";
    }
    return "unknown";
}

enum ActionRequestType {
    REQUEST_DRAW,
    REQUEST_PLAY,
    REQUEST_RESPOND,
    REQUEST_DISCARD
};

#endif // SERVERTYPES_H
