#include "gameeventbroadcaster.h"
#include "gameeventhandler.h"
#include "player.h"
#include "playingcard.h"
#include "game.h"

QList<const PlayingCard*> voidCardList(int s) {
    QList<const PlayingCard*> l;
    for(int i = 0; i < s; ++i)
        l.append(0);
    return l;
}

GameEventBroadcaster::GameEventBroadcaster(Game* game):
        mp_game(game)
{
}


void GameEventBroadcaster::registerHandler(GameEventHandler* handler, Player* player)
{
    m_handlers.append(new Handler(handler, player));
    handler->onHandlerRegistered(&mp_game->publicGameView(),
                                             (player ? player->playerCtrl() : 0));
}

void GameEventBroadcaster::registerSupervisor(GameEventHandler* handler)
{
    m_handlers.append(new Handler(handler, 0, 1));
    handler->onHandlerRegistered(&mp_game->publicGameView(), 0);
}

void GameEventBroadcaster::unregisterHandler(GameEventHandler* handler)
{
    foreach(Handler* h, m_handlers) {
        if (h->handler == handler) {
            m_handlers.removeAll(h);
            delete h;
        }
    }
    handler->onHandlerUnregistered();
}

void GameEventBroadcaster::onChatMessage(Player* p, const QString& message)
{    
    foreach(Handler* h, m_handlers) {
        h->handler->onChatMessage(p->publicView(), message);
    }
}

void GameEventBroadcaster::onGameSync()
{
    foreach(Handler* h, m_handlers) {
        h->handler->onGameSync();
    }
}

void GameEventBroadcaster::onPlayerJoinedGame(Player* p)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerJoinedGame(p->publicView());
    }
}

void GameEventBroadcaster::onPlayerLeavedGame(Player* p)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerLeavedGame(p->publicView());
    }
}

void GameEventBroadcaster::onPlayerUpdated(Player* p)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerUpdated(p->publicView());
    }
}

void GameEventBroadcaster::onPlayerDied(Player* p, Player* causedBy)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerDied(p->publicView(), causedBy ? &causedBy->publicView() : 0);
    }
}

void GameEventBroadcaster::onGameStarted()
{
    foreach(Handler* h, m_handlers) {
        h->handler->onGameStarted();
    }
}


void GameEventBroadcaster::onPlayerDrawFromDeck(Player* p, QList<const PlayingCard*> cards, bool revealCards)
{
    foreach(Handler* h, m_handlers) {
        if (h->player == p || revealCards || h->isSupervisor)
            h->handler->onPlayerDrawFromDeck(p->publicView(), cards, revealCards);
        else
            h->handler->onPlayerDrawFromDeck(p->publicView(), voidCardList(cards.size()), revealCards);
    }
}

void GameEventBroadcaster::onPlayerDrawFromGraveyard(Player* p, const PlayingCard* card, const PlayingCard* nextCard)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerDrawFromGraveyard(p->publicView(), card, nextCard);
    }
}

void GameEventBroadcaster::onPlayerDiscardCard(Player* p, PlayingCard* card, PocketType pocketFrom)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerDiscardCard(p->publicView(), card, pocketFrom);
    }
}

void GameEventBroadcaster::onPlayerPlayCard(Player* p, PlayingCard* card)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerPlayCard(p->publicView(), card);
    }
}

void GameEventBroadcaster::onPlayerPlayCard(Player* p, PlayingCard* card, Player* targetPlayer)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerPlayCard(p->publicView(), card, targetPlayer->publicView());
    }
}

void GameEventBroadcaster::onPlayerPlayCard(Player* p, PlayingCard* card, PlayingCard* targetCard)
{
    PublicPlayerView* owner = targetCard->owner() ? &targetCard->owner()->publicView() : 0;
    foreach(Handler* h, m_handlers) {
        if (targetCard->pocket() == POCKET_HAND && targetCard->owner() == h->player || h->isSupervisor) {
            h->handler->onPlayerPlayCard(p->publicView(), card, targetCard, owner);
        } else {
            h->handler->onPlayerPlayCard(p->publicView(), card, 0, owner);
        }
    }
}

void GameEventBroadcaster::onPlayerPlayCardOnTable(Player* p, PlayingCard* card, Player* targetPlayer)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerPlayCardOnTable(p->publicView(), card, targetPlayer->publicView());
    }
}

void GameEventBroadcaster::onPassTableCard(Player* p, PlayingCard* card, Player* targetPlayer)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPassTableCard(p->publicView(), card, targetPlayer->publicView());
    }
}

void GameEventBroadcaster::onPlayerRespondWithCard(Player* p, PlayingCard* card)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerRespondWithCard(p->publicView(), card);
    }
}

void GameEventBroadcaster::onPlayerPass(Player* p)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerPass(p->publicView());
    }
}

void GameEventBroadcaster::onDrawIntoSelection(Player* selectionOwner, QList<const PlayingCard*> cards)
{
    foreach(Handler* h, m_handlers) {
        if (selectionOwner == 0 || h->player == selectionOwner || h->isSupervisor)
            h->handler->onDrawIntoSelection(cards);
        else
            h->handler->onDrawIntoSelection(voidCardList(cards.size()));
    }
}

void GameEventBroadcaster::onPlayerPickFromSelection(Player* p, PlayingCard* card, bool revealCard)
{
    foreach(Handler* h, m_handlers) {
        if (h->player == p || revealCard || h->isSupervisor)
            h->handler->onPlayerPickFromSelection(p->publicView(), card);
        else
            h->handler->onPlayerPickFromSelection(p->publicView(), 0);
    }
}

void GameEventBroadcaster::onUndrawFromSelection(PlayingCard* card, Player* selectionOwner)
{
    foreach(Handler* h, m_handlers) {
        if (h->player == selectionOwner || h->isSupervisor)
            h->handler->onUndrawFromSelection(card);
        else
            h->handler->onUndrawFromSelection(0);
    }
}

void GameEventBroadcaster::onPlayerCheckDeck(Player* p, PlayingCard* checkedCard, PlayingCard* causedBy, bool checkResult)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerCheckDeck(p->publicView(), checkedCard, causedBy, checkResult);
    }
}

void GameEventBroadcaster::onPlayerStealCard(Player* p, Player* targetPlayer, PocketType pocketFrom, PlayingCard* card)
{
    foreach(Handler* h, m_handlers) {
        if (pocketFrom != POCKET_HAND || h->player == p || h->player == targetPlayer || h->isSupervisor)
            h->handler->onPlayerStealCard(p->publicView(), targetPlayer->publicView(), pocketFrom, card);
        else
            h->handler->onPlayerStealCard(p->publicView(), targetPlayer->publicView(), pocketFrom, 0);
    }
}

void GameEventBroadcaster::onCancelCard(Player* targetPlayer, PocketType pocketFrom, PlayingCard* card, Player* causedBy)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onCancelCard(pocketFrom, card,
                                    targetPlayer ? &targetPlayer->publicView() : 0,
                                    causedBy ? &causedBy->publicView() : 0);
    }
}

void GameEventBroadcaster::onGameContextChange(const GameContextData& gameContextData)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onGameContextChange(gameContextData);
    }
}

void GameEventBroadcaster::onLifePointsChange(Player* p, int lifePoints, Player* causedBy)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onLifePointsChange(p->publicView(), lifePoints, causedBy ? &causedBy->publicView() : 0);
    }
}

void GameEventBroadcaster::onDeckRegenerate()
{
    foreach(Handler* h, m_handlers) {
        h->handler->onDeckRegenerate();
    }
}

void GameEventBroadcaster::onPlayerUseAbility(Player* player)
{
    foreach(Handler* h, m_handlers) {
        h->handler->onPlayerUseAbility(player->publicView());
    }
}
