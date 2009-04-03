#include "gameserver.h"
#include "game.h"
#include "gamecycle.h"
#include "player.h"
#include "playerctrl.h"
#include "gameeventhandler.h"




PlayerCtrl::PlayerCtrl(Player* player):
        QObject(player),
        mp_player(player)
{
}

void PlayerCtrl::disconnect()
{
    mp_player->game()->removePlayer(mp_player);
}

void PlayerCtrl::startGame()
{
    mp_player->game()->startGame(mp_player);
}

void PlayerCtrl::drawCard(int numCards, bool revealCard)
{
    mp_player->game()->gameCycle().drawCard(mp_player, numCards, revealCard);
}

void PlayerCtrl::finishTurn()
{
    mp_player->game()->gameCycle().finishTurn(mp_player);
}

void PlayerCtrl::discardCard(CardAbstract* card)
{
    mp_player->game()->gameCycle().discardCard(mp_player, card);
}

void PlayerCtrl::playCard(CardPlayable* card)
{
    mp_player->game()->gameCycle().playCard(mp_player, card);
}

void PlayerCtrl::playCard(CardPlayable* card, const PublicPlayerView* targetPlayer)
{
    mp_player->game()->gameCycle().playCard(mp_player,
                                            card,
                                            Player::player(targetPlayer));
}


void PlayerCtrl::pass()
{
    mp_player->game()->gameCycle().pass(mp_player);
}





const PublicGameView& PlayerCtrl::publicGameView() const
{
    return mp_player->game()->publicGameView();
}

const PublicPlayerView& PlayerCtrl::publicPlayerView(int playerId) const
{
    if (playerId == 0)
        return mp_player->publicView();
    Player* player = mp_player->game()->getPlayer(playerId);
    if (player != 0) return player->publicView();
    throw BadPlayerException(playerId);
}

const PrivatePlayerView& PlayerCtrl::privatePlayerView() const
{
    return mp_player->privateView();
}








void PlayerCtrl::createGame(const StructGame& structGame,
                                   const StructPlayer& structPlayer,
                                   GameEventHandler* gameEventHandler)
{
    Game* newGame = GameServer::instance().createGame(structGame);
    Q_ASSERT(newGame != 0);
    Player* newPlayer = newGame->createNewPlayer(structPlayer, gameEventHandler);
    Q_ASSERT(newPlayer != 0);
}

void PlayerCtrl::joinGame(int gameId,
                                 const StructPlayer& structPlayer,
                                 GameEventHandler* gameEventHandler)
{
    Game* game = GameServer::instance().game(gameId);
    if (game == 0)
        throw BadGameException();
    Player* newPlayer = game->createNewPlayer(structPlayer, gameEventHandler);
    Q_ASSERT(newPlayer != 0);
}

StructServerInfo PlayerCtrl::structServerInfo()
{
    return GameServer::instance().structServerInfo();
}

QList<const PublicGameView*> PlayerCtrl::publicGameList()
{
    QList<const PublicGameView*> result;
    foreach(Game* game,GameServer::instance().gameList()) {
        result.append(&game->publicGameView());
    }
    return result;
}

const PublicGameView& PlayerCtrl::publicGameView(int gameId)
{
    Game* game = GameServer::instance().game(gameId);
    if (game == 0)
        throw BadGameException();
    return game->publicGameView();
}
