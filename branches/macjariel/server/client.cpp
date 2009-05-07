/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
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

#include <QTcpSocket>
#include "client.h"
#include "publicgameview.h"
#include "privateplayerview.h"
#include "playingcard.h"
#include "parser/parserstructs.h"

#include "voidai.h"

Client::Client(QObject* parent, int id, QTcpSocket* socket):
        QObject(parent),
        m_id(id),
        mp_playerCtrl(0)
{
    Q_ASSERT(m_id != 0);
    qDebug("%s:%d: Client #%d connected.", __FILE__, __LINE__, m_id);

    mp_parser = new Parser(this, socket);
    connect(mp_parser,  SIGNAL(terminated()),
            this,       SLOT(deleteLater()));
    connect(mp_parser,  SIGNAL(sigQueryServerInfo(QueryResult)),
            this,       SLOT(onQueryServerInfo(QueryResult)));
    connect(mp_parser,  SIGNAL(sigQueryGame(int, QueryResult)),
            this,       SLOT(onQueryGame(int, QueryResult)));
    connect(mp_parser,  SIGNAL(sigQueryGameList(QueryResult)),
            this,       SLOT(onQueryGameList(QueryResult)));
    connect(mp_parser,  SIGNAL(sigActionCreateGame(StructGame, StructPlayer)),
            this,       SLOT(onActionCreateGame(StructGame, StructPlayer)));
    connect(mp_parser,  SIGNAL(sigActionJoinGame(int, StructPlayer)),
            this,       SLOT(onActionJoinGame(int, StructPlayer)));
    connect(mp_parser,  SIGNAL(sigActionLeaveGame()),
            this,       SLOT(onActionLeaveGame()));
    connect(mp_parser,  SIGNAL(sigActionStartGame()),
            this,       SLOT(onActionStartGame()));
    connect(mp_parser,  SIGNAL(sigActionDrawCard(int,bool)),
            this,       SLOT(onActionDrawCard(int,bool)));
    connect(mp_parser,  SIGNAL(sigActionPlayCard(const ActionPlayCardData&)),
            this,       SLOT(onActionPlayCard(const ActionPlayCardData&)));
    connect(mp_parser,  SIGNAL(sigActionUseAbility(const ActionUseAbilityData&)),
            this,       SLOT(onActionUseAbility(const ActionUseAbilityData&)));
    connect(mp_parser,  SIGNAL(sigActionEndTurn()),
            this,       SLOT(onActionEndTurn()));
    connect(mp_parser,  SIGNAL(sigActionPass()),
            this,       SLOT(onActionPass()));
    connect(mp_parser,  SIGNAL(sigActionDiscard(int)),
            this,       SLOT(onActionDiscard(int)));

}

Client::~Client()
{
    emit disconnected(m_id);
    qDebug("%s:%d: Client #%d disconnected.", __FILE__, __LINE__, m_id);
}

int Client::id() const
{
    return m_id;
}

void Client::onActionCreateGame(const StructGame& structGame, const StructPlayer& structPlayer)
{
    if (isInGame()) {
        // TODO: respond with error
        return;
    }
    PlayerCtrl::createGame(structGame, structPlayer, this);
}


void Client::onActionJoinGame(int gameId, const StructPlayer& structPlayer)
{
    if (isInGame()) {
        // TODO: respond with error
        return;
    }
    PlayerCtrl::joinGame(gameId, structPlayer, this);
}



/*
void Client::joinGame(Game* game, const StructPlayer& player)
{
    qDebug(qPrintable(QString("Player %1 is joining the game with id %2").arg(player.name).arg(game->id())));
    mp_player = game->createNewPlayer(player);
    Q_ASSERT(mp_player != 0);
    connectPlayer();
    bool creator = 1;// todo game->creatorId() == id();
    if (creator)
    {
        connect(mp_player->game(), SIGNAL(startableChanged(int, bool)),
                mp_parser, SLOT(eventGameStartable(int, bool)));
    }
    mp_parser->eventJoinGame(game->id(), mp_player->structPlayer(), 0, creator);
}
*/


void Client::onActionLeaveGame()
{
    if (!isInGame()) {
        // TODO: error
        return;
    }
    mp_playerCtrl->disconnect();
}

void Client::onActionStartGame()
{
    if (!isInGame()) {
        // TODO: error
        return;
    }
    mp_playerCtrl->startGame();
}

void Client::onActionDrawCard(int numCards, bool revealCard)
{
    try {
        mp_playerCtrl->draw();
    } catch (GameException& e) {
        qDebug() << "Client::onActionDrawCard - exception:";
        e.debug();
    }
}




void Client::onActionPlayCard(const ActionPlayCardData& actionPlayCardData)
{
    qDebug("[CLIENT]   onActionPlayCard");
    PlayingCard* playedCard = mp_playerCtrl->privatePlayerView().card(actionPlayCardData.playedCardId);
    if (playedCard == 0) {
        qDebug(qPrintable(QString("[CLIENT]   Card '%1' not found!").arg(actionPlayCardData.playedCardId)));
        // @todo feedback
        return;
    }
    try {
        switch (actionPlayCardData.type) {
        case ActionPlayCardData::PLAYCARD_SIMPLE:
            mp_playerCtrl->playCard(playedCard);
            break;
        case ActionPlayCardData::PLAYCARD_PLAYER:
        case ActionPlayCardData::PLAYCARD_HAND:{
                int targetPlayerId = (actionPlayCardData.type == ActionPlayCardData::PLAYCARD_PLAYER) ?
                                     actionPlayCardData.targetPlayerId :
                                     actionPlayCardData.targetHandId;

                const PublicPlayerView* targetPlayer =
                        mp_playerCtrl->publicGameView().publicPlayerView(targetPlayerId);

                if (targetPlayer == 0) {
                    qDebug(qPrintable(QString("[CLIENT]   Target player '%1' not exist!").arg(actionPlayCardData.targetPlayerId)));
                    // @todo feedback
                    return;
                }
                mp_playerCtrl->playCard(playedCard, targetPlayer);
            } break;
        case ActionPlayCardData::PLAYCARD_CARD:
            int targetCardId = actionPlayCardData.targetCardId;
            PlayingCard* card = mp_playerCtrl->card(targetCardId);
            if (card == 0) {
                qDebug(qPrintable(QString("[CLIENT]   Target card '%1' not exist!").arg(targetCardId)));
                // @todo feedback
                return;
            }
            mp_playerCtrl->playCard(playedCard, card);
            break;
        }
    } catch (GameException& e) {
        qDebug("[CLIENT]: onActionPlayCard - exception:");
        e.debug();
    }
}

void Client::onActionUseAbility(const ActionUseAbilityData& actionUseAbilityData)
{
    try {
        switch(actionUseAbilityData.type) {
            case ActionUseAbilityData::TypeSimple: {
                mp_playerCtrl->useAbility();
                break;
            }
            case ActionUseAbilityData::TypePlayer: {
                PublicPlayerView* targetPlayer = getPlayer(actionUseAbilityData.targetPlayerId);
                if (targetPlayer == 0)
                    return;
                mp_playerCtrl->useAbility(targetPlayer);
                break;
            }
            case ActionUseAbilityData::TypeCards: {
                QList<PlayingCard*> cards = getCards(actionUseAbilityData.targetCardsId);
                mp_playerCtrl->useAbility(cards);
                break;
            }
        }
    } catch (GameException& e) {
        qDebug("[CLIENT]: onActionUseAbility - exception:");
        e.debug();
    }
}

void Client::onActionEndTurn()
{
    try {
        mp_playerCtrl->finishTurn();
    } catch (GameException& e) {
        qDebug("[CLIENT]: onActionEndTurn - exception:");
        e.debug();
    }
}

void Client::onActionPass()
{
    try {
        mp_playerCtrl->pass();
    } catch (GameException& e) {
        qDebug("[CLIENT]: onActionPass - exception:");
        e.debug();
    }
}

void Client::onActionDiscard(int cardId)
{
    try {
        PlayingCard* card = mp_playerCtrl->privatePlayerView().card(cardId);
        if (card == 0) {
            qDebug("Cannot discard unknown card.");
            return;
        }
        mp_playerCtrl->discardCard(card);
    } catch (GameException& e) {
        qDebug("[CLIENT]: onActionDiscard - exception:");
        e.debug();
    }
}


void Client::onQueryServerInfo(QueryResult result)
{
    result.sendData(PlayerCtrl::structServerInfo());
}

void Client::onQueryGame(int gameId, QueryResult result)
{
    try {
        const PublicGameView& publicGameView = PlayerCtrl::publicGameView(gameId);
        StructGame structGame = publicGameView.structGame();
        StructPlayerList structPlayerList;
        foreach (const PublicPlayerView* publicPlayerView, publicGameView.publicPlayerList()) {
            structPlayerList.append(publicPlayerView->structPlayer());
        }
        result.sendData(structGame, structPlayerList);
    } catch (BadGameException e) {
        // TODO
        //result.sendData(e);
    }
}

void Client::onQueryGameList(QueryResult result)
{
    StructGameList structGameList;
    foreach (const PublicGameView* publicGameView, PlayerCtrl::publicGameList()) {
        structGameList.append(publicGameView->structGame());
    }
    result.sendData(structGameList);
}



void Client::startAI() {
    int id = mp_playerCtrl->publicGameView().id();
    new VoidAI(id);
    new VoidAI(id);
    new VoidAI(id);
    new VoidAI(id);

}


////////////////////////////////////////////
// The AbstractPlayerController interface //
////////////////////////////////////////////


void Client::onHandlerRegistered(PlayerCtrl* playerCtrl)
{
    mp_playerCtrl = playerCtrl;
}

void Client::onHandlerUnregistered()
{
    mp_playerCtrl = 0;
}

void Client::onGameStartabilityChanged(bool isStartable)
{
    mp_parser->eventGameStartable(mp_playerCtrl->publicGameView().id(), isStartable);
}

void Client::onChatMessage(PublicPlayerView& publicPlayerView, const QString& message)
{
    mp_parser->eventMessage(publicPlayerView.id(),
                            publicPlayerView.name(),
                            message);
}

void Client::onGameSync()
{
    GameSyncData gameSyncData;
    foreach (const PublicPlayerView* p, mp_playerCtrl->publicGameView().publicPlayerList())
        gameSyncData.players.append(p->publicPlayerData());
    gameSyncData.localPlayer = mp_playerCtrl->privatePlayerView().privatePlayerData();
    gameSyncData.gameContext = mp_playerCtrl->publicGameView().gameContextData();
    mp_parser->eventGameSync(gameSyncData);
}


void Client::onPlayerJoinedGame(PublicPlayerView& publicPlayerView)
{
    int gameId = mp_playerCtrl->publicGameView().id();
    int playerId = publicPlayerView.id();
    StructPlayer structPlayer;
    bool isOther;
    if (playerId == mp_playerCtrl->privatePlayerView().id()) {
        structPlayer = mp_playerCtrl->privatePlayerView().structPlayer();
        isOther = 0;
        if (mp_playerCtrl->privatePlayerView().isCreator())  {
            QTimer::singleShot(500, this, SLOT(startAI()));
        }
    } else {
        structPlayer = mp_playerCtrl->publicPlayerView(playerId).structPlayer();
        isOther = 1;
    }
    bool isCreator = mp_playerCtrl->privatePlayerView().isCreator();
    mp_parser->eventJoinGame(gameId, structPlayer, isOther, isCreator);

}

void Client::onPlayerLeavedGame(PublicPlayerView& leavingPlayer)
{
    Q_ASSERT(isInGame());
    int gameId = mp_playerCtrl->publicGameView().id();
    int playerId = mp_playerCtrl->publicPlayerView().id();
    if (leavingPlayer.id() != playerId) {
        mp_parser->eventLeaveGame(gameId, leavingPlayer.structPlayer(), 1);
    }
}

void Client::onPlayerDied(PublicPlayerView& player, PublicPlayerView* causedBy)
{
    int         playerId = player.id();
    PlayerRole  role     = player.role();
    Q_ASSERT(role != ROLE_UNKNOWN);
    mp_parser->eventPlayerDied(playerId, role);
}


void Client::onGameStarted()
{
    StructGame structGame = mp_playerCtrl->publicGameView().structGame();
    StructPlayerList structPlayerList;
    const PrivatePlayerView* privatePlayer = &mp_playerCtrl->privatePlayerView();
    foreach(const PublicPlayerView* player, mp_playerCtrl->publicGameView().publicPlayerList()) {
        if (player->id() == privatePlayer->id())
            player = privatePlayer;
        structPlayerList.append(player->structPlayer());
    }
    mp_parser->eventStartGame(structGame, structPlayerList);
}

void Client::onPlayerDrawFromDeck(PublicPlayerView& player, QList<const PlayingCard*> cards, bool revealCards)
{
    foreach (const PlayingCard* card, cards) {
        CardMovementData x;
        x.pocketTypeFrom = POCKET_DECK;
        x.pocketTypeTo   = POCKET_HAND;
        x.playerTo       = player.id();
        if (card != 0)
            x.card = card->cardData();
        mp_parser->eventCardMovement(x);
    }
}

void Client::onPlayerDrawFromGraveyard(PublicPlayerView& player, const PlayingCard* card, const PlayingCard* nextCard)
{
    CardMovementData x;
    x.pocketTypeFrom = POCKET_GRAVEYARD;
    x.pocketTypeTo   = POCKET_HAND;
    x.playerTo       = player.id();
    x.card           = card->cardData();
    mp_parser->eventCardMovement(x);
    ///@todo: send info about nextCard (the card under the drawn card from graveyard)
}

void Client::onPlayerDiscardCard(PublicPlayerView& player, const PlayingCard* card, PocketType pocketFrom)
{
    CardMovementData x;
    x.pocketTypeFrom = pocketFrom;
    x.pocketTypeTo   = POCKET_GRAVEYARD;
    x.playerFrom     = player.id();
    x.card           = card->cardData();
    mp_parser->eventCardMovement(x);
}

void Client::onPlayerPlayCard(PublicPlayerView& player, const PlayingCard* card)
{
    CardMovementData x;
    x.pocketTypeFrom = POCKET_HAND;
    x.pocketTypeTo   = POCKET_GRAVEYARD;
    x.playerFrom     = player.id();
    x.card           = card->cardData();
    mp_parser->eventCardMovement(x);
}

void Client::onPlayerPlayCard(PublicPlayerView& player, const PlayingCard* card, PublicPlayerView& target)
{
    CardMovementData x;
    x.pocketTypeFrom = POCKET_HAND;
    x.pocketTypeTo   = POCKET_GRAVEYARD;
    x.playerFrom     = player.id();
    x.card           = card->cardData();
    mp_parser->eventCardMovement(x);
}

void Client::onPlayerPlayCard(PublicPlayerView& player, const PlayingCard* card, const PlayingCard* target)
{
    CardMovementData x;
    x.pocketTypeFrom = POCKET_HAND;
    x.pocketTypeTo   = POCKET_GRAVEYARD;
    x.playerFrom     = player.id();
    x.card           = card->cardData();
    mp_parser->eventCardMovement(x);
}

void Client::onPlayerPlayCardOnTable(PublicPlayerView& player, const PlayingCard* card, PublicPlayerView& targetPlayer)
{
    CardMovementData x;
    x.pocketTypeFrom = POCKET_HAND;
    x.pocketTypeTo   = POCKET_TABLE;
    x.playerFrom     = player.id();
    x.playerTo       = targetPlayer.id();
    x.card           = card->cardData();
    mp_parser->eventCardMovement(x);
}

void Client::onPassTableCard(PublicPlayerView& player, const PlayingCard* card, PublicPlayerView& targetPlayer)
{
    CardMovementData x;
    x.pocketTypeFrom = POCKET_TABLE;
    x.pocketTypeTo   = POCKET_TABLE;
    x.playerFrom     = player.id();
    x.playerTo       = targetPlayer.id();
    x.card           = card->cardData();
    mp_parser->eventCardMovement(x);
}

void Client::onPlayerPass(PublicPlayerView& player)
{
}

void Client::onDrawIntoSelection(QList<const PlayingCard*> cards)
{
    foreach (const PlayingCard* card, cards) {
        CardMovementData x;
        x.pocketTypeFrom = POCKET_DECK;
        x.pocketTypeTo   = POCKET_SELECTION;
        x.playerTo       = 0;
        if (card != 0)
            x.card = card->cardData();
        mp_parser->eventCardMovement(x);
    }
}

void Client::onPlayerPickFromSelection(PublicPlayerView& player, const PlayingCard* card)
{
    CardMovementData x;
    x.pocketTypeFrom = POCKET_SELECTION;
    x.pocketTypeTo   = POCKET_HAND;
    x.playerFrom     = 0;
    x.playerTo       = player.id();
    x.card           = card->cardData();
    mp_parser->eventCardMovement(x);
}

void Client::onUndrawFromSelection(const PlayingCard* card)
{
    CardMovementData x;
    x.pocketTypeFrom = POCKET_SELECTION;
    x.pocketTypeTo   = POCKET_DECK;
    x.playerFrom     = 0;
    x.playerTo       = 0;
    if (card != 0)
        x.card = card->cardData();
    mp_parser->eventCardMovement(x);
}

void Client::onPlayerCheckDeck(PublicPlayerView& player, const PlayingCard* checkedCard, const PlayingCard* causedBy, bool checkResult)
{
    /// caused by can be NULL
    CardMovementData x;
    x.pocketTypeFrom = POCKET_DECK;
    x.pocketTypeTo   = POCKET_GRAVEYARD;
    x.playerFrom     = 0;
    x.playerTo       = 0;
    x.card           = checkedCard->cardData();
    mp_parser->eventCardMovement(x);

}

void Client::onPlayerStealCard(PublicPlayerView& player, PublicPlayerView& targetPlayer, PocketType pocketFrom, const PlayingCard* card)
{
    CardMovementData x;
    x.pocketTypeFrom = pocketFrom;
    x.pocketTypeTo   = POCKET_HAND;
    x.playerFrom     = targetPlayer.id();
    x.playerTo       = player.id();
    if (card != 0)
        x.card       = card->cardData();
    mp_parser->eventCardMovement(x);
}

void Client::onPlayerCancelCard(PublicPlayerView& targetPlayer, PocketType pocketFrom, const PlayingCard* card, PublicPlayerView* p)
{
    CardMovementData x;
    x.pocketTypeFrom = pocketFrom;
    x.pocketTypeTo   = POCKET_GRAVEYARD;
    x.playerFrom     = targetPlayer.id();
    x.playerTo       = 0;
    x.card           = card->cardData();
    mp_parser->eventCardMovement(x);
}

void Client::onGameContextChange(const GameContextData& gameContextData)
{
    mp_parser->eventGameContextChange(gameContextData);
}

void Client::onLifePointsChange(PublicPlayerView& player, int lifePoints, PublicPlayerView* causedBy)
{
    mp_parser->eventLifePointsChange(player.id(), lifePoints);
}

void Client::onDeckRegenerate()
{

}

void Client::onActionRequest(ActionRequestType requestType)
{
    qDebug() << QString("Client (%1): onActionRequest(%2)").arg(m_id).arg(requestType);
}


PublicPlayerView* Client::getPlayer(int playerId)
{
    PublicPlayerView* res = mp_playerCtrl->publicGameView().publicPlayerView(playerId);
    if (res == 0)
        qDebug(qPrintable(QString("[CLIENT]   Target player '%1' not exist!").arg(playerId)));
    return res;
}

PlayingCard* Client::getCard(int cardId)
{
    PlayingCard* card = mp_playerCtrl->card(cardId);
    if (card == 0) {
        qDebug(qPrintable(QString("[CLIENT]   Target card '%1' not exist!").arg(cardId)));
    }
    return card;
}

QList<PlayingCard*> Client::getCards(QList<int> cardIds)
{
    QList<PlayingCard*> res;
    foreach(int cardId, cardIds) {
        PlayingCard* card = getCard(cardId);
        if (card != 0)
            res.append(card);
    }
    return res;
}



bool Client::isInGame() const
{
    return (mp_playerCtrl != 0);
}

