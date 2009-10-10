# -*- coding: utf-8 -*-

from kbangcommon import *

GameStructs = []

s = GameStruct("ServerInfo", "server-info")
s["doxyString"] = ("The %(structName)s struct holds the information about the "
                  " server. It is used when querying for server information.") % s
s["simpleMembers"].append(Member("QString", "name", "name", "Name of the server."))
s["simpleMembers"].append(Member("QString", "desc", "desc", "Short description of the server."))
s["simpleMembers"].append(Member("QString", "adminName", "admin-name", "Server administrator's name."))
s["simpleMembers"].append(Member("QString", "adminEmail", "admin-email", "Server administrator's email."))
s["simpleMembers"].append(Member("quint16", "gamesCnt", "games-cnt", "Count of games on server.", "0"))
s["simpleMembers"].append(Member("quint16", "playersCnt", "players-cnt", "Count of players on server.", "0"))
s["simpleMembers"].append(Member("quint16", "clientsCnt", "clients-cnt", "Count of clients on server.", "0"))
s["simpleMembers"].append(Member("QDateTime", "startTime", "start-time", "Time of the start of the server in ISO 8601 UTC."))
s["simpleMembers"].append(Member("QString", "motd", "motd", "Message of the day."))
GameStructs.append(s)

playerInfo = GameStruct("PlayerInfo", "player-info")
playerInfo["doxyString"] = ("The %(structName)s structure describes basic information about a player. "
                            "It is used to list players in join game dialog." % s)
playerInfo["simpleMembers"].append(Member("PlayerId", "id", "id", "Player id.", "0"))
playerInfo["simpleMembers"].append(Member("QString", "name", "name", "Player name."))
playerInfo["simpleMembers"].append(Member("bool", "hasPassword", "has-password", "Whether player has password.", "0"))
playerInfo["simpleMembers"].append(Member("bool", "hasController", "has-controller", "Whether player has an attached controller.", "0"))
playerInfo["simpleMembers"].append(Member("bool", "isAI", "is-ai", "Whether is controlled by AI.", "0"))
playerInfo["simpleMembers"].append(Member("bool", "isAlive", "is-alive", "Whether is alive.", "0"))
GameStructs.append(playerInfo)

s = GameStruct("PlayerInfoList", "player-info-list")
s.setImplicitList(playerInfo["structName"])
GameStructs.append(s)

s = GameStruct("GameInfo", "game-info")
s["doxyString"] = ("The %(structName)s structure describes basic information about a game. "
                   "It is used to list games in join game dialog.") % s

s["simpleMembers"].append(Member("GameId", "id", "id", "Game id.", "0"))
s["simpleMembers"].append(Member("QString", "name", "name", "Game name."))
s["simpleMembers"].append(Member("QString", "desc", "desc", "Game description."))
s["simpleMembers"].append(Member("quint8", "playersMin", "players-min", "Minimal count of players.", "0"))
s["simpleMembers"].append(Member("quint8", "playersMax", "players-max", "Maximal count of players.", "0"))
s["simpleMembers"].append(Member("quint8", "playersCnt", "players-cnt", "Count of all players.", "0"))
s["simpleMembers"].append(Member("quint8", "alivePlayersCnt", "alive-players-cnt", "Count of alive players.", "0"))
s["simpleMembers"].append(Member("quint8", "aiPlayersCnt", "ai-players-cnt", "Count of AI players.", "0"))
s["simpleMembers"].append(Member("qint16", "spectatorsMax", "spectators-max", "Maximal number of spectators.", "-1"))
s["simpleMembers"].append(Member("quint16", "spectatorsCnt", "spectators-cnt", "Count of spectators.", "0"))
s["simpleMembers"].append(Member("bool", "hasPlayerPassword", "has-player-password", "Whether has player password.", "0"))
s["simpleMembers"].append(Member("bool", "hasSpectatorPassword", "has-spectator-password", "Whether has spectator password.", "0"))
s["simpleMembers"].append(Member("GameState", "gameState", "game-state", "State of the game.", "GAMESTATE_INVALID"))
s["complexMembers"].append(Member("PlayerInfoListData", "players", "players", "List of players."))
GameStructs.append(s)

sl = GameStruct("GameInfoList", "game-info-list")
sl.setImplicitList(s["structName"])
GameStructs.append(sl)

s = GameStruct("UrlList", "url-list")
s.setImplicitList("QString", False, "url")
GameStructs.append(s)

s = GameStruct("CardSetInfo", "card-set-info")
s["doxyString"] = ("The %(structName)s structure describes cardset information that is "
                   "advertised by server to clients.") % s
s["simpleMembers"].append(Member("QString", "id", "id", "Unique id of cardset.", "0"))
s["simpleMembers"].append(Member("QString", "name", "name", "English name of cardset."))
s["simpleMembers"].append(Member("QList<QLocale>", "locales", "locales", "Locales of the cardset."))
s["simpleMembers"].append(Member("QString", "slotId", "slot-id", "Id of the slot."))
s["simpleMembers"].append(Member("quint16", "formatVersion", "format-version", "Version of used cardset format.", "0"))
s["simpleMembers"].append(Member("quint16", "revision", "revision", "Revision of the cardset.", "0"))
s["complexMembers"].append(Member("UrlListData", "downloadLinks", "download-links", "List of download links."))
GameStructs.append(s)

sl = GameStruct("CardSetInfoList", "card-set-info-list")
sl.setImplicitList(s["structName"])
GameStructs.append(sl)

s = GameStruct("CreatePlayer", "create-player")
s["doxyString"] = ("The %(structName)s structure holds information needed to create a player. "
                   "This is used when creating and/or joining games.") % s
s["simpleMembers"].append(Member("QString", "name", "name", "Player's name."))
s["simpleMembers"].append(Member("QString", "password", "password", "Player's password. Empty string disables password."))
s["complexMembers"].append(Member("QByteArray", "avatar", "avatar", "Player's avatar."))
GameStructs.append(s)


s = GameStruct("CreateGame", "create-game")
s["doxyString"] = """
    This structure holds all information that is necessary to create a game. This is used when creating a game.
    @todo add items to determine game type and parameters
"""
s["simpleMembers"].append(Member("QString", "name", "name", "Game name."))
s["simpleMembers"].append(Member("QString", "desc", "desc", "Game description."))
s["simpleMembers"].append(Member("quint8", "playersMin", "players-min", "Minimal count of players.", "0"))
s["simpleMembers"].append(Member("quint8", "playersMax", "players-max", "Maximal count of players.", "0"))
s["simpleMembers"].append(Member("qint16", "spectatorsMax", "spectators-max", "Maximal number of spectators.", "0"))
s["simpleMembers"].append(Member("quint8", "aiPlayersCnt", "ai-players-cnt", "Count of AI players.", "0"))
s["simpleMembers"].append(Member("QString", "playerPassword", "player-password", "Player password, empty string = no pass."))
s["simpleMembers"].append(Member("QString", "spectatorPassword", "spectator-password", "Spectator password, empty string = no pass."))
s["complexMembers"].append(Member("QMap<QString, QVariant>", "options", "options", ""))
GameStructs.append(s)

s = GameStruct("Card", "card")
s["doxyString"] = """
    This structure holds information about a card.
"""
s["simpleMembers"].append(Member("CardId", "id", "id", "Card id. @see CardId.", "0"))
s["simpleMembers"].append(Member("CardName", "name", "name", "Card name. @see CardName."))
s["simpleMembers"].append(Member("CardType", "type", "type", "Card type. @see CardType.", "CARDTYPE_UNKNOWN"))
s["simpleMembers"].append(Member("CardSuit", "suit", "suit", "Card suit. @see CardSuit.", "SUIT_INVALID"))
s["simpleMembers"].append(Member("CardRank", "rank", "rank", "Card rank. @see CardRank.", "RANK_INVALID"))
s["simpleMembers"].append(Member("bool", "isReady", "is-ready", "Whether card is ready - this is related to green-bordered cards", "1"))
GameStructs.append(s)

sl = GameStruct("CardList", "card-list")
sl.setImplicitList(s["structName"])
GameStructs.append(sl)

s = GameStruct("PublicPlayer", "public-player")
s["doxyString"] = """This structure holds all public information about a player."""
s["simpleMembers"].append(Member("PlayerId", "id", "id", "Player id.", "0"))
s["simpleMembers"].append(Member("QString", "name", "name", "Player name."))
s["simpleMembers"].append(Member("bool", "hasPassword", "has-password", "Whether player has password.", "0"))
s["simpleMembers"].append(Member("bool", "hasController", "has-controller", "Whether player has an attached controller.", "0"))
s["simpleMembers"].append(Member("bool", "isAI", "is-ai", "Whether is controlled by AI.", "0"))
s["simpleMembers"].append(Member("bool", "isAlive", "is-alive", "Whether is alive.", "0"))
s["simpleMembers"].append(Member("bool", "isWinner", "is-winner", "Whether is a winner.", "0"))
s["simpleMembers"].append(Member("bool", "isSheriff", "is-sheriff", "Whether is sheriff.", "0"))
s["complexMembers"].append(Member("QByteArray", "avatar", "avatar", "Player's avatar."))
s["simpleMembers"].append(Member("QString", "character", "character", "Player's character."))
s["simpleMembers"].append(Member("QString", "takenCharacter", "takenCharacter", "Used for Vera Custer."))
s["simpleMembers"].append(Member("qint8", "lifePoints", "life-points", "Player's life points.", "0"))
s["simpleMembers"].append(Member("quint8", "handSize", "hand-size", "Number of cards in player's hand.", "0"))
s["complexMembers"].append(Member("CardListData", "table", "table", "List of cards on table."))
s["simpleMembers"].append(Member("PlayerRole", "role", "role", "Player's role (if is known)", "ROLE_INVALID"))
GameStructs.append(s)

sl = GameStruct("PublicPlayerList", "public-player-list")
sl.setImplicitList(s["structName"])
GameStructs.append(sl)

s = GameStruct("PrivatePlayer", "private-player-list")
s["doxyString"] = """This structure holds player id and all private information about a player."""
s["simpleMembers"].append(Member("PlayerId", "id", "id", "Player id.", "0"))
s["simpleMembers"].append(Member("PlayerRole", "role", "role", "Player's role.", "ROLE_INVALID"))
s["complexMembers"].append(Member("CardListData", "hand", "hand", "List of cards in player's hand."))
GameStructs.append(s)

s = GameStruct("GameContext", "game-context")
s["doxyString"] = """This structure holds information about game context."""
s["simpleMembers"].append(Member("PlayerId", "currentPlayerId", "current-player-id", "Id of current player (Player on turn).", "0"))
s["simpleMembers"].append(Member("PlayerId", "requestedPlayerId", "requested-player-id", "Id of requested player.", "0"))
s["simpleMembers"].append(Member("quint32", "turnNumber", "turn-number", "Turn number.", "0"))
s["simpleMembers"].append(Member("GamePlayState", "gamePlayState", "game-play-state", "GamePlay state.", "GAMEPLAYSTATE_INVALID"))
s["simpleMembers"].append(Member("ReactionType", "reactionType", "reaction-type", "Reaction type.", "REACTION_NONE"))
s["simpleMembers"].append(Member("PlayerId", "causedBy", "caused-by", "Id of player that caused reaction.", "0"))
GameStructs.append(s)


s = GameStruct("GameSync", "game-sync")
s["doxyString"] = (
    "This structure is used to synchronize client with server. It contains all"
    "information about a game that a client needs to reconstuct it from scratch."
    "Note, that this structure is created on demand for concrete player (client)."
)
s["simpleMembers"].append(Member("GameId", "id", "id", "Game id.", "0"))
s["simpleMembers"].append(Member("QString", "name", "name", "Game name."))
s["simpleMembers"].append(Member("bool", "isCreator", "is-creator", "Whether the client is creator.", "0"))
s["complexMembers"].append(Member("PublicPlayerListData", "players", "players", "List of PublicPlayerData."))
s["complexMembers"].append(Member("PrivatePlayerData", "localPlayer", "local-player", "Local player information (if not spectator)."))
s["complexMembers"].append(Member("GameContextData", "gameContext", "game-context", "The context of the game."))
s["simpleMembers"].append(Member("GameState", "gameState", "game-state", "The GameState.", "GAMESTATE_INVALID"));
s["complexMembers"].append(Member("CardData", "graveyard", "graveyard", "The top card in graveyard."))
s["complexMembers"].append(Member("CardListData", "selection", "selection", "The content of selection pocket."))
GameStructs.append(s)

s = GameStruct("CardIdList", "card-id-list")
s.setImplicitList("CardId", False, "card-id")
GameStructs.append(s)
