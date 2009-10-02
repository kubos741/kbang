/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
 *   MacJariel (at) gmail.com                                              *
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

#include "gametypes.h"
#include "util.h"


CardSuit stringToCardSuit(const QString& s)
{
    if (s == "spades")      return SUIT_SPADES;
    if (s == "hearts")      return SUIT_HEARTS;
    if (s == "diamonds")    return SUIT_DIAMONDS;
    if (s == "clubs")       return SUIT_CLUBS;
    return SUIT_INVALID;
}

QString cardSuitToString(const CardSuit& suit)
{
    switch(suit) {
        case SUIT_SPADES:   return "spades";
        case SUIT_HEARTS:   return "hearts";
        case SUIT_DIAMONDS: return "diamonds";
        case SUIT_CLUBS:    return "clubs";
        case SUIT_INVALID:  return "";
    }
    return "";
}

CardRank stringToCardRank(QString s)
{
    s = s.toUpper();
    if (s == "A") return 14;
    if (s == "K") return 13;
    if (s == "Q") return 12;
    if (s == "J") return 11;
    return s.toInt();
}

QString cardRankToString(const CardRank& rank)
{
    if (rank <= 10) return QString::number(rank);
    if (rank == 11) return "J";
    if (rank == 12) return "Q";
    if (rank == 13) return "K";
    if (rank == 14) return "A";
    return "";
}

PlayerRole stringToPlayerRole(const QString& s)
{
    if (s == "unknown")  return ROLE_UNKNOWN;
    if (s == "outlaw")   return ROLE_OUTLAW;
    if (s == "deputy")   return ROLE_DEPUTY;
    if (s == "sheriff")  return ROLE_SHERIFF;
    if (s == "renegade") return ROLE_RENEGADE;
    return ROLE_INVALID;
}

QString playerRoleToString(const PlayerRole& r)
{
    switch(r) {
        case ROLE_UNKNOWN:  return "unknown";
        case ROLE_OUTLAW:   return "outlaw";
        case ROLE_DEPUTY:   return "deputy";
        case ROLE_SHERIFF:  return "sheriff";
        case ROLE_RENEGADE: return "renegade";
        case ROLE_INVALID:  return "invalid";
    }
    return "invalid";
}


GamePlayState stringToGamePlayState(const QString& s)
{
    if (s == "draw")     return GAMEPLAYSTATE_DRAW;
    if (s == "turn")     return GAMEPLAYSTATE_TURN;
    if (s == "response") return GAMEPLAYSTATE_RESPONSE;
    if (s == "discard")  return GAMEPLAYSTATE_DISCARD;
    return GAMEPLAYSTATE_INVALID;
}

QString gamePlayStateToString(const GamePlayState& s)
{
    switch(s) {
        case GAMEPLAYSTATE_DRAW:     return "draw";
        case GAMEPLAYSTATE_TURN:     return "turn";
        case GAMEPLAYSTATE_RESPONSE: return "response";
        case GAMEPLAYSTATE_DISCARD:  return "discard";
        case GAMEPLAYSTATE_INVALID:  return "invalid";
    }
    return "invalid";
}

CardType stringToCardType(const QString& s)
{
    if (s == "playing")         return CARDTYPE_PLAYING;
    if (s == "character")       return CARDTYPE_CHARACTER;
    if (s == "role")            return CARDTYPE_ROLE;
    return CARDTYPE_UNKNOWN;
}

QString cardTypeToString(const CardType& t)
{
    switch(t) {
        case CARDTYPE_PLAYING:      return "playing";
        case CARDTYPE_CHARACTER:    return "character";
        case CARDTYPE_ROLE:         return "role";
        case CARDTYPE_UNKNOWN:      return "";
    }
    return "";
}

ReactionType stringToReactionType(const QString& s)
{
    if (s == "bang")            return REACTION_BANG;
    if (s == "gatling")         return REACTION_GATLING;
    if (s == "indians")         return REACTION_INDIANS;
    if (s == "duel")            return REACTION_DUEL;
    if (s == "general-store")   return REACTION_GENERALSTORE;
    if (s == "last-save")       return REACTION_LASTSAVE;
    if (s == "lucky-duke")      return REACTION_LUCKYDUKE;
    if (s == "kit-carlson")     return REACTION_KITCARLSON;
    return REACTION_NONE;
}

QString reactionTypeToString(const ReactionType& r)
{
    switch(r) {
    case REACTION_BANG:         return "bang";
    case REACTION_GATLING:      return "gatling";
    case REACTION_INDIANS:      return "indians";
    case REACTION_DUEL:         return "duel";
    case REACTION_GENERALSTORE: return "general-store";
    case REACTION_LASTSAVE:     return "last-save";
    case REACTION_LUCKYDUKE:    return "lucky-duke";
    case REACTION_KITCARLSON:   return "kit-carlson";
    case REACTION_NONE:         return "";
    }
    return "";
}

ClientType stringToClientType(const QString& s)
{
    if (s == "player")      return CLIENTTYPE_PLAYER;
    if (s == "spectator")   return CLIENTTYPE_SPECTATOR;
    return CLIENTTYPE_SPECTATOR;
}

QString clientTypeToString(ClientType clientType)
{
    switch(clientType) {
        case CLIENTTYPE_PLAYER:     return "player";
        case CLIENTTYPE_SPECTATOR:  return "spectator";
    }
    return "";
}

PocketType stringToPocketType(const QString& s)
{
    if (s == "deck")      return POCKET_DECK;
    if (s == "graveyard") return POCKET_GRAVEYARD;
    if (s == "hand")      return POCKET_HAND;
    if (s == "table")     return POCKET_TABLE;
    if (s == "selection") return POCKET_SELECTION;
    return POCKET_INVALID;
}

QString pocketTypeToString(const PocketType& p)
{
    switch(p) {
        case POCKET_DECK:       return "deck";
        case POCKET_GRAVEYARD:  return "graveyard";
        case POCKET_HAND:       return "hand";
        case POCKET_TABLE:      return "table";
        case POCKET_SELECTION:  return "selection";
        case POCKET_INVALID:    return "";
    }
    return "";
}


GameState stringToGameState(const QString& s)
{
    if (s == "waiting-for-players") return GAMESTATE_WAITINGFORPLAYERS;
    if (s == "playing")             return GAMESTATE_PLAYING;
    if (s == "finished")            return GAMESTATE_FINISHED;
    return GAMESTATE_INVALID;
}

QString gameStateToString(const GameState& s)
{
    switch(s) {
    case GAMESTATE_WAITINGFORPLAYERS:   return "waiting-for-players";
    case GAMESTATE_PLAYING:             return "playing";
    case GAMESTATE_FINISHED:            return "finished";
    default:                            break;
    }
    return "Invalid";
}

GameParticipantType stringToGameParticipantType(const QString& s)
{
    if (s == "player") return GAMEPARTICIPANT_PLAYER;
    else return GAMEPARTICIPANT_SPECTATOR;
}

QString gameParticipantTypeToString(const GameParticipantType& t)
{
    switch(t) {
        case GAMEPARTICIPANT_PLAYER:     return "player";
        case GAMEPARTICIPANT_SPECTATOR:  return "spectator";
    }
    return "";
}

