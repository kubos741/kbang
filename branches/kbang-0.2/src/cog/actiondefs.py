# -*- coding: utf-8 -*-

from kbangcommon import *

Actions = []

a = Action("ChatMessage", "chat-message")
a["simpleMembers"].append(Member("QString", "message", "message", ""))
Actions.append(a)

a = Action("CreateGame", "create-game")
a["complexMembers"].append(Member("CreateGameData", "createGameData", "game-data", ""))
a["complexMembers"].append(Member("CreatePlayerData", "createPlayerData", "player-data", ""))
Actions.append(a)

a = Action("Discard", "discard")
a["simpleMembers"].append(Member("CardId", "cardId", "card-id", "Discarded card.", "0"))
Actions.append(a)

a = Action("DrawCard", "draw-card")
Actions.append(a)

a = Action("EndTurn", "end-turn")
Actions.append(a)

a = Action("JoinGame", "join-game")
a["simpleMembers"].append(Member("GameId", "gameId", "game-id", "", "0"))
a["simpleMembers"].append(Member("PlayerId", "playerId", "player-id", "", "0"))
a["simpleMembers"].append(Member("QString", "gamePassword", "game-password", "", "0"))
a["simpleMembers"].append(Member("GameParticipantType", "gameParticipantType", "game-participant-type", "", "GAMEPARTICIPANT_INVALID"))
a["complexMembers"].append(Member("CreatePlayerData", "createPlayerData", "player-data", ""))
Actions.append(a)

a = Action("LeaveGame", "leave-game")
Actions.append(a)

a = Action("Pass", "pass")
Actions.append(a)

a = Action("PlayCard", "play-card")
a["simpleMembers"].append(Member("CardId", "playedCardId", "played-card-id", "", "0"))
a["simpleMembers"].append(Member("CardId", "targetCardId", "target-card-id", "", "0"))
a["simpleMembers"].append(Member("CardId", "discardCardId", "discard-card-id", "", "0"))
a["simpleMembers"].append(Member("PlayerId", "targetPlayerId", "target-player-id", "", "0"))
Actions.append(a)

a = Action("StartGame", "start-game")
Actions.append(a)

a = Action("UseAbility", "use-ability")
a["simpleMembers"].append(Member("PlayerId", "targetPlayerId", "target-player-id", "", "0"))
a["complexMembers"].append(Member("CardIdListData", "targetCardsId", "target-cards", ""))
Actions.append(a)