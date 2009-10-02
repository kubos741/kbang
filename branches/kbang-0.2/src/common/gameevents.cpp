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

#include "gameevents.h"

QString GameEventData::typeToString(GameEventData::Type t)
{
    switch(t) {
    case UnknownType:           return "";                      break;
    case StartGameType:         return "start-game";            break;
    case FinishGameType:        return "finish-game";           break;
    case DealCardsType:         return "deal-cards";            break;
    case StartTurnType:         return "start-turn";            break;
    case CheckDeckType:         return "check-deck";            break;
    case DrawCardType:          return "draw-card";             break;
    case PlayCardType:          return "play-card";             break;
    case PlayCardOnTableType:   return "play-card-on-table";    break;
    case PlayCardOnPlayerType:  return "play-card-on-player";   break;
    case PlayCardOnCardType:    return "play-card-on-card";     break;
    case ReactionPlayCardType:  return "reaction-play-card";    break;
    case ReactionPassType:      return "reaction-pass";         break;
    case ShuffleDeckType:       return "shuffle-deck";          break;
    case KillPlayerType:        return "kill-player";           break;
    }
    return "";
}

GameEventData::Type GameEventData::stringToType(const QString& s)
{
    if (s == "start-game")          return StartGameType;
    if (s == "finish-game")         return FinishGameType;
    if (s == "deal-cards")          return DealCardsType;
    if (s == "start-turn")          return StartTurnType;
    if (s == "check-deck")          return CheckDeckType;
    if (s == "draw-card")           return  DrawCardType;
    if (s == "play-card")           return PlayCardType;
    if (s == "play-card-on-table")  return PlayCardOnTableType;
    if (s == "play-card-on-player") return PlayCardOnPlayerType;
    if (s == "play-card-on-card")   return PlayCardOnCardType;
    if (s == "reaction-play-card")  return ReactionPlayCardType;
    if (s == "reaction-pass")       return ReactionPassType;
    if (s == "shuffle-deck")        return ShuffleDeckType;
    if (s == "kill-player")         return KillPlayerType;
    return UnknownType;
}


/* static */
QString GameEventData::cardMeaningToString(GameEventData::CardMeaning c)
{
    switch (c) {
    case NoCard:
        return "";
        break;
    case PlayedCard:
        return "played-card";
        break;
    case TargetCard:
        return "target-card";
        break;
    case CausedByCard:
        return "caused-by-card";
        break;
    case CheckedCard:
        return "checked-card";
        break;
    }
    return "";
}

/* static */
GameEventData::CardMeaning GameEventData::stringToCardMeaning(const QString& s)
{
    if (s == "played-card")     return PlayedCard;
    if (s == "target-card")     return TargetCard;
    if (s == "caused-by-card")  return CausedByCard;
    if (s == "checked-card")    return CheckedCard;
    return NoCard;
}
