/***************************************************************************
 *   Copyright (C) 2008-2009 by MacJariel                                  *
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
#ifndef ACTIONS_H
#define ACTIONS_H

#include "gametypes.h"
#include "gamestructs.h"
#include <QSharedPointer>

struct ActionData {
    enum Type {
        InvalidType = 0,
        CreateGameType,
        JoinGameType,
        LeaveGameType,
        StartGameType,
        ChatMessageType,
        DrawCardType,
        PlayCardType,
        UseAbilityType,
        EndTurnType,
        PassType,
        DiscardType
    };
    ActionData(Type type): m_type(type) {}
    inline Type t() const {
        return m_type;
    }
private:
    Type m_type;
};

struct ActionCreateGameData: public ActionData {
    ActionCreateGameData(): ActionData(CreateGameType) {}

    CreateGameData      createGameData;
    CreatePlayerData    createPlayerData;
};

struct ActionJoinGameData: public ActionData {
    ActionJoinGameData(): ActionData(JoinGameType), gameId(0), playerId(0) {}

    GameId              gameId;
    PlayerId            playerId;
    QString             gamePassword;
    CreatePlayerData    createPlayerData;
    GameParticipantType participantType;    ///@todo update parser
};


struct ActionLeaveGameData: public ActionData {
    ActionLeaveGameData(): ActionData(LeaveGameType) {}

    ///@todo this action should contain information about privilege delegation
};

struct ActionStartGameData: public ActionData {
    ActionStartGameData(): ActionData(StartGameType) {}
};

struct ActionChatMessageData: public ActionData {
    ActionChatMessageData(): ActionData(ChatMessageType) {}

    QString     message;
};

struct ActionDrawCardData: public ActionData {
    ActionDrawCardData(): ActionData(DrawCardType) {}
};

struct ActionPlayCardData: public ActionData {
    ActionPlayCardData(): ActionData(PlayCardType), playedCardId(0),
                          targetCardId(0), discardCardId(0),
                          targetPlayerId(0) {}

    CardId      playedCardId;   /**< The id of card to be played. */
    CardId      targetCardId;   /**< The id of target card. */
    CardId      discardCardId;  /**< The id of card to be discarded. */
    PlayerId    targetPlayerId; /**< The id of target player. */
};

struct ActionUseAbilityData: public ActionData {
    ActionUseAbilityData(): ActionData(UseAbilityType), targetPlayerId(0) {}

    PlayerId        targetPlayerId; /**< The id of target player. */
    QList<CardId>   targetCardsId;  /**< The list of target cards. */
};

struct ActionEndTurnData: public ActionData {
    ActionEndTurnData(): ActionData(EndTurnType) {}
};

struct ActionPassData: public ActionData {
    ActionPassData(): ActionData(PassType) {}
};

struct ActionDiscardData: public ActionData {
    ActionDiscardData(): ActionData(DiscardType), cardId(0) {}

    CardId      cardId;
};

#endif // ACTIONS_H
