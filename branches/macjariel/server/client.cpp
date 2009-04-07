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
#include "cardabstract.h"

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

void Client::onIncomingMessage(const PublicPlayerView& publicPlayerView, const QString& message)
{
    mp_parser->eventMessage(publicPlayerView.id(),
                            publicPlayerView.name(),
                            message);
}

void Client::onPlayerInit(PlayerCtrl* playerCtrl)
{
    mp_playerCtrl = playerCtrl;
    /* SOME CACHING POSSIBLE HERE */


}

void Client::onPlayerExit()
{
    mp_playerCtrl = 0;
    /* IF CACHING, UNCACHE ASAP */
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


void Client::onPlayerJoinedGame(const PublicPlayerView& publicPlayerView)
{
    int gameId = mp_playerCtrl->publicGameView().id();
    int playerId = publicPlayerView.id();
    StructPlayer structPlayer;
    bool isOther;
    if (playerId == mp_playerCtrl->privatePlayerView().id()) {
        structPlayer = mp_playerCtrl->privatePlayerView().structPlayer();
        isOther = 0;
        QTimer::singleShot(500, this, SLOT(startAI()));
    } else {
        structPlayer = mp_playerCtrl->publicPlayerView(playerId).structPlayer();
        isOther = 1;
    }
    bool isCreator = mp_playerCtrl->privatePlayerView().isCreator();
    mp_parser->eventJoinGame(gameId, structPlayer, isOther, isCreator);

}

void Client::onPlayerLeavedGame(const PublicPlayerView& leavingPlayer)
{
    Q_ASSERT(isInGame());
    int gameId = mp_playerCtrl->publicGameView().id();
    int playerId = mp_playerCtrl->publicPlayerView().id();
    if (leavingPlayer.id() == playerId)
    {
        // TODO
        /*
        mp_parser->eventLeaveGame(gameId, player, 0);
        disconnectPlayer();
        mp_player = 0;
        */
    }
    else
    {
        mp_parser->eventLeaveGame(gameId, leavingPlayer.structPlayer(), 1);
    }
}

void Client::onGameStartabilityChanged(bool isStartable)
{
    mp_parser->eventGameStartable(mp_playerCtrl->publicGameView().id(), isStartable);
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

void Client::onPlayerDrawedCard(int playerId, const CardAbstract* card)
{
    StructCardMovement x;
    x.pocketTypeFrom = POCKET_DECK;
    x.pocketTypeTo   = POCKET_HAND;
    x.playerTo       = playerId;
    if (card != 0)
    {
        x.cardDetails = card->cardDetails();
    }
    mp_parser->eventCardMovement(x);
}

void Client::onPlayerDiscardedCard(int playerId, const CardAbstract* card)
{
    StructCardMovement x;
    x.pocketTypeFrom = POCKET_HAND;
    x.pocketTypeTo   = POCKET_GRAVEYARD;
    x.playerFrom     = playerId;
    x.cardDetails    = card->cardDetails();
    mp_parser->eventCardMovement(x);
}

void Client::onPlayerPlayedCard(int playerId, const CardAbstract* card)
{
    StructCardMovement x;
    x.pocketTypeFrom = POCKET_HAND;
    x.pocketTypeTo   = POCKET_PLAYED;
    x.playerFrom     = playerId;
    x.cardDetails    = card->cardDetails();
    mp_parser->eventCardMovement(x);
}

void Client::onPlayedCardsCleared()
{
}

void Client::onLifePointsChange(const PublicPlayerView& player, int oldLifePoints, int newLifePoints)
{
    qDebug() << "TRYING TO SEND LIFEPOINTS";
    mp_parser->eventLifePointsChange(player.id(), newLifePoints);
    qDebug() << "DONE TRYING TO SEND LIFEPOINTS";
}

void Client::onGameFocusChange(int currentPlayerId, int requestedPlayerId)
{
    mp_parser->eventGameFocusChange(currentPlayerId, requestedPlayerId);
}

void Client::onActionRequest(ActionRequestType requestType)
{
    qDebug() << QString("Client (%1): onActionRequest(%2)").arg(m_id).arg(requestType);
}


bool Client::isInGame() const
{
    return (mp_playerCtrl != 0);
}

