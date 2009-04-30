#include "gameeventbroadcaster.h"
#include "gameeventhandler.h"
#include "player.h"

QPair<GameEventHandler*, Player*> handler;

QList<const PlayingCard*> voidCardList(int s) {
    QList<const PlayingCard*> l;
    for(int i = 0; i < s; ++i)
        l.append(0);
    return l;
}

GameEventBroadcaster::GameEventBroadcaster()
{
}


void GameEventBroadcaster::registerHandler(GameEventHandler* handler, Player* player)
{
    m_handlers.append(qMakePair(handler, player));
}

void GameEventBroadcaster::unregisterHandler(GameEventHandler* handler, Player* player)
{
    m_handlers.removeAll(qMakePair(handler, player));
}

void GameEventBroadcaster::onChatMessage(Player* p, const QString& message)
{    
    foreach(handler, m_handlers) {
        handler.first->onChatMessage(p->publicView(), message);
    }
}

void GameEventBroadcaster::onGameSync()
{
    foreach(handler, m_handlers) {
        handler.first->onGameSync();
    }
}

void GameEventBroadcaster::onPlayerJoinedGame(Player* p)
{
    foreach(handler, m_handlers) {
        handler.first->onPlayerJoinedGame(p->publicView());
    }
}

void GameEventBroadcaster::onPlayerLeavedGame(Player* p)
{
    foreach(handler, m_handlers) {
        handler.first->onPlayerLeavedGame(p->publicView());
    }
}

void GameEventBroadcaster::onPlayerDied(Player* p, Player* causedBy)
{
    foreach(handler, m_handlers) {
        handler.first->onPlayerDied(p->publicView(), causedBy ? &causedBy->publicView() : 0);
    }
}

void GameEventBroadcaster::onGameStarted()
{
    foreach(handler, m_handlers) {
        handler.first->onGameStarted();
    }
}


void GameEventBroadcaster::onPlayerDrawFromDeck(Player* p, QList<const PlayingCard*> cards, bool revealCards)
{
    foreach(handler, m_handlers) {
        if (handler.second == p || revealCards)
            handler.first->onPlayerDrawFromDeck(p->publicView(), cards, revealCards);
        else
            handler.first->onPlayerDrawFromDeck(p->publicView(), voidCardList(cards.size()), revealCards);
    }
}

void GameEventBroadcaster::onPlayerDiscardCard(Player* p, PlayingCard* card, PocketType pocketFrom)
{
    foreach(handler, m_handlers) {
        handler.first->onPlayerDiscardCard(p->publicView(), card, pocketFrom);
    }
}

void GameEventBroadcaster::onPlayerPlayCard(Player* p, PlayingCard* card)
{
    foreach(handler, m_handlers) {
        handler.first->onPlayerPlayCard(p->publicView(), card);
    }
}

void GameEventBroadcaster::onPlayerPlayCard(Player* p, PlayingCard* card, Player* targetPlayer)
{
    foreach(handler, m_handlers) {
        handler.first->onPlayerPlayCard(p->publicView(), card, targetPlayer->publicView());
    }
}

void GameEventBroadcaster::onPlayerPlayCard(Player* p, PlayingCard* card, PlayingCard* targetCard)
{
    foreach(handler, m_handlers) {
        handler.first->onPlayerPlayCard(p->publicView(), card, targetCard);
    }
}

void GameEventBroadcaster::onPlayerPlayCardOnTable(Player* p, PlayingCard* card, Player* targetPlayer)
{
    foreach(handler, m_handlers) {
        handler.first->onPlayerPlayCardOnTable(p->publicView(), card, targetPlayer->publicView());
    }
}

void GameEventBroadcaster::onPassTableCard(Player* p, PlayingCard* card, Player* targetPlayer)
{
    foreach(handler, m_handlers) {
        handler.first->onPassTableCard(p->publicView(), card, targetPlayer->publicView());
    }
}

void GameEventBroadcaster::onPlayerPass(Player* p)
{
    foreach(handler, m_handlers) {
        handler.first->onPlayerPass(p->publicView());
    }
}

void GameEventBroadcaster::onDrawIntoSelection(Player* selectionOwner, QList<const PlayingCard*> cards)
{
    foreach(handler, m_handlers) {
        if (selectionOwner == 0 || handler.second == selectionOwner)
            handler.first->onDrawIntoSelection(cards);
        else
            handler.first->onDrawIntoSelection(voidCardList(cards.size()));
    }
}

void GameEventBroadcaster::onPlayerPickFromSelection(Player* p, PlayingCard* card, bool revealCard)
{
    foreach(handler, m_handlers) {
        if (handler.second == p || revealCard)
            handler.first->onPlayerPickFromSelection(p->publicView(), card);
        else
            handler.first->onPlayerPickFromSelection(p->publicView(), 0);
    }
}

void GameEventBroadcaster::onPlayerCheckDeck(Player* p, PlayingCard* checkedCard, PlayingCard* causedBy, bool checkResult)
{
    foreach(handler, m_handlers) {
        handler.first->onPlayerCheckDeck(p->publicView(), checkedCard, causedBy, checkResult);
    }
}

void GameEventBroadcaster::onPlayerStealCard(Player* p, Player* targetPlayer, PocketType pocketFrom, PlayingCard* card)
{
    foreach(handler, m_handlers) {
        if (pocketFrom != POCKET_HAND || handler.second == p || handler.second == targetPlayer)
            handler.first->onPlayerStealCard(p->publicView(), targetPlayer->publicView(), pocketFrom, card);
        else
            handler.first->onPlayerStealCard(p->publicView(), targetPlayer->publicView(), pocketFrom, 0);
    }
}

void GameEventBroadcaster::onCancelCard(Player* targetPlayer, PocketType pocketFrom, PlayingCard* card, Player* p)
{
    foreach(handler, m_handlers) {
        handler.first->onPlayerCancelCard(targetPlayer->publicView(), pocketFrom, card, p ? &p->publicView() : 0);
    }
}

void GameEventBroadcaster::onGameContextChange(const GameContextData& gameContextData)
{
    foreach(handler, m_handlers) {
        handler.first->onGameContextChange(gameContextData);
    }
}

void GameEventBroadcaster::onLifePointsChange(Player* p, int lifePoints, Player* causedBy)
{
    foreach(handler, m_handlers) {
        handler.first->onLifePointsChange(p->publicView(), lifePoints, causedBy ? &causedBy->publicView() : 0);
    }
}

void GameEventBroadcaster::onDeckRegenerate()
{
    foreach(handler, m_handlers) {
        handler.first->onDeckRegenerate();
    }
}
