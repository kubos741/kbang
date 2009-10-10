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

/*[[[cog
import cog
from actiondefs import *
]]]
[[[end]]]*/


struct ActionData {
    enum Type {
        InvalidType = 0,
        /*[[[cog
        cog.outl(",\n".join([a["actionType"] for a in Actions]))
        ]]]*/
        ChatMessageType,
        CreateGameType,
        DiscardType,
        DrawCardType,
        EndTurnType,
        JoinGameType,
        LeaveGameType,
        PassType,
        PlayCardType,
        StartGameType,
        UseAbilityType
        //[[[end]]]
    };
    ActionData(Type type): m_type(type) {}
    inline Type t() const {
        return m_type;
    }
private:
    Type m_type;
};

/*[[[cog
for action in Actions:
    cog.outl(action.genDef())
]]]*/

/**
 * @author: MacJariel
 */
struct ActionChatMessageData: public ActionData {
    ActionChatMessageData(): ActionData(ChatMessageType) {}
    QString message; ///
};


/**
 * @author: MacJariel
 */
struct ActionCreateGameData: public ActionData {
    ActionCreateGameData(): ActionData(CreateGameType) {}
    CreateGameData createGameData; ///
    CreatePlayerData createPlayerData; ///
};


/**
 * @author: MacJariel
 */
struct ActionDiscardData: public ActionData {
    ActionDiscardData(): ActionData(DiscardType), cardId(0) {}
    CardId cardId; ///Discarded card.
};


/**
 * @author: MacJariel
 */
struct ActionDrawCardData: public ActionData {
    ActionDrawCardData(): ActionData(DrawCardType) {}
};


/**
 * @author: MacJariel
 */
struct ActionEndTurnData: public ActionData {
    ActionEndTurnData(): ActionData(EndTurnType) {}
};


/**
 * @author: MacJariel
 */
struct ActionJoinGameData: public ActionData {
    ActionJoinGameData(): ActionData(JoinGameType), gameId(0),
         playerId(0), gamePassword(0),
         gameParticipantType(GAMEPARTICIPANT_INVALID) {}
    GameId gameId; ///
    PlayerId playerId; ///
    QString gamePassword; ///
    GameParticipantType gameParticipantType; ///
    CreatePlayerData createPlayerData; ///
};


/**
 * @author: MacJariel
 */
struct ActionLeaveGameData: public ActionData {
    ActionLeaveGameData(): ActionData(LeaveGameType) {}
};


/**
 * @author: MacJariel
 */
struct ActionPassData: public ActionData {
    ActionPassData(): ActionData(PassType) {}
};


/**
 * @author: MacJariel
 */
struct ActionPlayCardData: public ActionData {
    ActionPlayCardData(): ActionData(PlayCardType), playedCardId(0),
         targetCardId(0), discardCardId(0), targetPlayerId(0) {}
    CardId playedCardId; ///
    CardId targetCardId; ///
    CardId discardCardId; ///
    PlayerId targetPlayerId; ///
};


/**
 * @author: MacJariel
 */
struct ActionStartGameData: public ActionData {
    ActionStartGameData(): ActionData(StartGameType) {}
};


/**
 * @author: MacJariel
 */
struct ActionUseAbilityData: public ActionData {
    ActionUseAbilityData(): ActionData(UseAbilityType),
         targetPlayerId(0) {}
    PlayerId targetPlayerId; ///
    CardIdListData targetCardsId; ///
};

//[[[end]]]

#endif // ACTIONS_H