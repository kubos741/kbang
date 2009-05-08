#include "playerevent.h"
#include "game.h"

using namespace client;

PlayerEvent::PlayerEvent(Game* game):
        GameEvent(game)
{
}

PlayerEvent* PlayerEvent::playerJoined(const PublicPlayerData& publicPlayerData)
{
    m_type = PlayerJoined;
    m_publicPlayerData = publicPlayerData;
    return this;
}

PlayerEvent* PlayerEvent::playerLeaved(int playerId)
{
    m_type = PlayerLeaved;
    m_playerId = playerId;
    return this;
}

PlayerEvent* PlayerEvent::playerControllerChanged(int playerId, bool hasController)
{
    m_type = PlayerControllerChanged;
    m_playerId = playerId;
    m_hasController = hasController;
    return this;
}


PlayerEvent::~PlayerEvent()
{
}

void PlayerEvent::run()
{
    switch(m_type) {
    case PlayerJoined:
        mp_game->playerJoinedGame(m_publicPlayerData);
        break;
    case PlayerLeaved:
        mp_game->playerLeavedGame(m_playerId);
        break;
    case PlayerControllerChanged:
        ///@todo
        break;
    }
}

