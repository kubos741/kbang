/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
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

#include "game.h"
#include "mainwindow.h"
#include "util.h"
#include "gameeventhandler.h"
#include "gameeventqueue.h"
#include "gameactionmanager.h"
#include "serverconnection.h"

#include "localplayerwidget.h"
#include "graveyardwidget.h"
#include "deckwidget.h"
#include "cardlistwidget.h"


using namespace client;

Game* Game::smp_currentGame(0);

Game::Game(GameId gameId, QString gameName, ClientType clientType):
        QObject(MainWindow::instance()),
        m_gameId(gameId),
        m_gameName(gameName),
        m_clientType(clientType),
        m_localPlayerId(0),
        m_gameState(GAMESTATE_INVALID),
        m_interfaceType(NoInterface),
        m_isCreator(0),
        mp_startButton(0),
        mp_deck(0),
        mp_graveyard(0),
        mp_selection(0),
        mp_localPlayerWidget(MainWindow::instance()->localPlayerWidget()),
        mp_gameEventHandler(new GameEventHandler(this)),
        mp_gameEventQueue(new GameEventQueue(this)),
        mp_gameActionManager(new GameActionManager(this))
{
    Q_ASSERT(smp_currentGame == 0);
    smp_currentGame = this;


    m_playerWidgetsList = MainWindow::instance()->opponentWidgets();
    switch(m_clientType) {
        case CLIENTTYPE_PLAYER:
            m_playerWidgetsList[0]->hide();
            localPlayerWidget()->show();
            m_playerWidgetsList[0] = localPlayerWidget();
            break;
        case CLIENTTYPE_SPECTATOR:
            m_playerWidgetsList[0]->show();
            localPlayerWidget()->hide();
            break;
    }

#if 0
    mp_localPlayerWidget->enterGameMode(this);
    foreach(OpponentWidget* opponentWidget, m_opponentWidgets) {
        opponentWidget->enterGameMode(this);
    }
    mp_gameEventHandler = new GameEventHandler(this);
    mp_gameEventHandler->connectSlots(mp_serverConnection->parser());
#endif
}

Game::~Game()
{
    smp_currentGame = 0;
}

/* static */ void
Game::enterGameMode(GameId gameId, QString gameName, ClientType clientType)
{
    if (smp_currentGame != 0) {
        qFatal("Trying to create new Game instance, but another already exists.");
    }
    new Game(gameId, gameName, clientType);
}

void
Game::leaveGameMode()
{
    delete smp_currentGame;
}

QString
Game::localCharacter() const
{
    if (localPlayerId() == 0) {
        return "";
    } else {
        return mp_localPlayerWidget->characterWidget()->character();
    }
}

void
Game::setLocalPlayer(const PublicPlayerData& publicPlayerData)
{
    if (m_clientType != CLIENTTYPE_PLAYER) {
        return;
    }
    localPlayerWidget()->setFromPublicData(publicPlayerData);
    m_localPlayerId = publicPlayerData.id;
}

void
Game::setLocalPlayer(const PrivatePlayerData& privatePlayerData)
{
    if (m_clientType != CLIENTTYPE_PLAYER) {
        return;
    }
    Q_ASSERT(m_localPlayerId == privatePlayerData.id);
    localPlayerWidget()->setFromPrivateData(privatePlayerData);
}

void
Game::setGameState(const GameState& gameState)
{
    m_gameState = gameState;
}

void
Game::setGameContext(const GameContextData& gameContextData)
{
    if (m_gameState != GAMESTATE_PLAYING &&
        m_gameState != GAMESTATE_FINISHED) {
        return;
    }

    PlayerWidget* currentPlayer = playerWidget(currentPlayerId());
    PlayerWidget* requestedPlayer = playerWidget(requestedPlayerId());

    if (currentPlayer) {
        currentPlayer->setCurrent(0);
        currentPlayer->update();
    }

    if (requestedPlayer) {
        requestedPlayer->setRequested(0);
        requestedPlayer->update();
    }

    m_gameContextData = gameContextData;

    currentPlayer = playerWidget(currentPlayerId());
    requestedPlayer = playerWidget(requestedPlayerId());

    if (currentPlayer) {
        currentPlayer->setCurrent(1);
        currentPlayer->update();
    } else {
        qCritical("Cannot set active player widget.");
    }

    if (requestedPlayer) {
        requestedPlayer->setRequested(1);
        requestedPlayer->update();
    } else {
        qCritical("Cannot set requested player widget.");
    }

    localPlayerWidget()->setFromContext(gameContextData);

#if 0
    if (gamePlayState() == GAMEPLAYSTATE_DRAW) {
        emit emitLogMessage("<br />");
    }
#endif

    if (!requestedPlayer || !requestedPlayer->isLocalPlayer()) {
        unsetTextInfo();
        return;
    }

    if (gamePlayState() == GAMEPLAYSTATE_RESPONSE) {
        PlayerWidget* causedBy = gameContextData.causedBy ? playerWidget(gameContextData.causedBy) : 0;
        QString causedByName = causedBy ? causedBy->name() : "";
        QString message;
        switch(gameContextData.reactionType) {
        case REACTION_BANG:
            message = tr("<i>%1</i> played Bang! on you!").arg(causedByName);
            break;
        case REACTION_DUEL:
            message = tr("You are in duel with <i>%1</i>.").arg(causedByName);
            break;
        case REACTION_GATLING:
            message = tr("<i>%1</i> played Gatling.").arg(causedByName);
            break;
        case REACTION_GENERALSTORE:
            message = tr("Shopping time. Please pick a card.").arg(causedByName);
            break;
        case REACTION_INDIANS:
            message = tr("The Indians lead by <i>%1</i> are in town.").arg(causedByName);
            break;
        case REACTION_LASTSAVE:
            message = tr("You've just got the fatal shot. Ya have beer?");
            break;
        case REACTION_KITCARLSON:
            message = tr("Pick two cards from selection.");
            break;
        case REACTION_LUCKYDUKE:
            message = tr("Feelin' lucky? Pick a card to respond with.");
            break;
        case REACTION_NONE:
            NOT_REACHED();
        }
        setTextInfo(message);
    } else if (gamePlayState() == GAMEPLAYSTATE_DRAW) {
        setTextInfo(tr("It's your turn. Good luck!"));
    } else if (gamePlayState() == GAMEPLAYSTATE_DISCARD) {
        setTextInfo(tr("You need to discard some cards!"));
    } else{
        unsetTextInfo();
    }
}

void
Game::setSelection(QList<CardData> cards)
{
    if (m_gameState != GAMESTATE_PLAYING &&
        m_gameState != GAMESTATE_FINISHED) {
        return;
    }

    mp_selection->clear();
    foreach(const CardData& card, cards) {
        CardWidget* cardWidget = new CardWidget(0);
        cardWidget->setCardData(card);
        mp_selection->push(cardWidget);
    }
}

void
Game::setGraveyard(const CardData& data)
{
    if (m_interfaceType != GameInterface) {
        return;
    }
    mp_graveyard->setFirstCard(data);
}

void
Game::updateInterface()
{
    switch(m_gameState) {
    case GAMESTATE_INVALID:
    case GAMESTATE_WAITINGFORPLAYERS:
        if (m_isCreator) {
            if (m_interfaceType== CreatorInterface) return;
            unloadInterface();
            loadCreatorInterface();
        } else {
            unloadInterface();
        }
        break;
    case GAMESTATE_PLAYING:
    case GAMESTATE_FINISHED:
        unloadInterface();
        loadGameInterface();
        break;
    }
}

void
Game::cleanUp()
{
#if 0
    unloadInterface();
    mp_localPlayerWidget->leaveGameMode();
    foreach(OpponentWidget* opponentWidget, m_opponentWidgets)
        opponentWidget->leaveGameMode();
    unsetTextInfo();
    mp_gameEventHandler->clear();
    smp_currentGame = 0;
#endif
}

void
Game::setTextInfo(const QString& text)
{
//    mp_statusLabel->setText(text);
}

void
Game::unsetTextInfo()
{
//    mp_statusLabel->setText("");
}

void
Game::appendOpponent(const PublicPlayerData& publicPlayerData)
{
    foreach (PlayerWidget* widget, m_playerWidgets) {
        if (widget->isVoid()) {
            widget->setFromPublicData(publicPlayerData);
            m_playerWidgets[publicPlayerData.id] = widget;
            return;
        }
    }
    qCritical("Too many players connected to the game.");
}

void
Game::insertOpponent(int index, const PublicPlayerData& publicPlayerData)
{
    if (index < 0) {
        index += m_playerWidgetsList.size();
    }
    Q_ASSERT(0 <= index && index < m_playerWidgetsList.size());
    m_playerWidgetsList[index]->setFromPublicData(publicPlayerData);
    m_playerWidgets[publicPlayerData.id] = m_playerWidgetsList[index];
}

void
Game::removeOpponent(PlayerId playerId)
{
    if (m_playerWidgets.contains(playerId))
    {
        m_playerWidgets[playerId]->clear();
        m_playerWidgets.remove(playerId);
    }
}

void
Game::updateOpponent(const PublicPlayerData& publicPlayerData)
{
    PlayerWidget* opponent = playerWidget(publicPlayerData.id);
    if (opponent) {
        opponent->setFromPublicData(publicPlayerData);
    }
}

void
Game::clearOpponentWidget(int index)
{
    if (index < 0) {
        index += m_playerWidgetsList.size();
    }
    Q_ASSERT(0 <= index && index < m_playerWidgetsList.size());
    PlayerWidget* opponent = m_playerWidgetsList[index];
    if (m_playerWidgets[opponent->id()] == opponent) {
        m_playerWidgets.remove(opponent->id());
    }
    opponent->clear();
}

void
Game::clearOpponentWidgetRange(int indexFrom, int indexTo)
{
    if (indexFrom < 0) {
        indexFrom += m_playerWidgetsList.size();
    }
    if (indexTo < 0) {
        indexTo += m_playerWidgetsList.size();
    }
    for (int index = indexFrom; index <= indexTo; ++index) {
        clearOpponentWidget(index);
    }
}

void
Game::pauseGameEvents()
{
    mp_gameEventQueue->pause();
}

void
Game::resumeGameEvents()
{
    mp_gameEventQueue->resume();
}

void
Game::setGameStartability(bool gameStartability)
{
    mp_startButton->setEnabled(gameStartability);
}


void Game::loadCreatorInterface()
{
    QWidget* middleWidget = MainWindow::instance()->middleWidget();
    Q_ASSERT(mp_startButton == 0);
    Q_ASSERT(middleWidget->layout() == 0);
    mp_startButton = new QPushButton(middleWidget);
    QBoxLayout* l = new QBoxLayout(QBoxLayout::LeftToRight);
    mp_startButton->setText(tr("Start game"));
    mp_startButton->setEnabled(0);
    connect(mp_startButton, SIGNAL(clicked()),
            this, SLOT(startButtonClicked()));
    connect(ServerConnection::instance(), SIGNAL(gameCanBeStarted(bool)),
            this, SLOT(gameCanBeStarted(bool)));
    l->addStretch(1);
    l->addWidget(mp_startButton);
    l->addStretch(1);
    middleWidget->setLayout(l);
    m_interfaceType= CreatorInterface;
}

void Game::unloadCreatorInterface()
{
    QWidget* middleWidget = MainWindow::instance()->middleWidget();
    Q_ASSERT(mp_startButton != 0);
    Q_ASSERT(middleWidget->layout() != 0);
    mp_startButton->deleteLater();
    mp_startButton = 0;
    delete middleWidget->layout();
    m_interfaceType= NoInterface;
}

void Game::loadGameInterface()
{
    QWidget* middleWidget = MainWindow::instance()->middleWidget();
    Q_ASSERT(mp_deck == 0);
    Q_ASSERT(mp_graveyard == 0);
    Q_ASSERT(mp_selection == 0);
    Q_ASSERT(middleWidget->layout() == 0);
    qDebug("---- loading game interface ----");
    mp_deck = new DeckWidget(0);
    //mp_deck->init();
    mp_graveyard = new GraveyardWidget(0);
    //mp_graveyard->init();
    mp_selection = new CardListWidget(0);
    mp_selection->setPocketType(POCKET_SELECTION);
    mp_selection->setCardSizeRole(CARD_SIZE_NORMAL);
    mp_selection->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mp_selection->setHasBox(0);

    QBoxLayout* l = new QBoxLayout(QBoxLayout::LeftToRight);
    l->addStretch(3);
    l->addWidget(mp_graveyard);
    l->addStretch(1);
    l->addWidget(mp_deck);
    l->addStretch(3);

    QBoxLayout* l2 = new QBoxLayout(QBoxLayout::LeftToRight);
    l2->addStretch(3);
    l2->addWidget(mp_selection);
    l2->addStretch(3);

    QBoxLayout* l3 = new QVBoxLayout();
    l3->addLayout(l);
    l3->addStretch(1);
    l3->addLayout(l2);
    middleWidget->setLayout(l3);
    m_interfaceType= GameInterface;
}

void Game::unloadGameInterface()
{
    QWidget* middleWidget = MainWindow::instance()->middleWidget();
    Q_ASSERT(mp_deck != 0);
    Q_ASSERT(mp_graveyard != 0);
    Q_ASSERT(mp_selection != 0);
    Q_ASSERT(middleWidget->layout() != 0);
    qDebug("---- unloading game interface ----");
    mp_deck->deleteLater();
    mp_graveyard->deleteLater();
    mp_selection->deleteLater();
    delete middleWidget->layout();
    m_interfaceType= NoInterface;
    mp_deck = 0;
    mp_graveyard = 0;
    mp_selection = 0;
}

void Game::unloadInterface()
{
    switch(m_interfaceType) {
    case NoInterface:
        return;
    case CreatorInterface:
        unloadCreatorInterface();
        return;
    case GameInterface:
        unloadGameInterface();
        return;
    }
}



//void Game::gameStarted(const StructGame&, const StructPlayerList&)
//{
//    /*
//    int pI;
//    for(pI = 0; pI < playerList.count(); pI++)
//    {
//        if (playerList[pI].id == m_playerId) break;
//    }
//    qDebug() << "player: " << pI;
//    //mp_localPlayerWidget->setPlayer(playerList[pI]);
//    foreach(OpponentWidget* w, m_opponentWidgets)
//    {
//        w->clear();
//    }
//    for (int i = pI + 1; i < playerList.count(); ++i)
//    {
//        int pos = i - (pI + 1);
//        m_players[playerList[i].id] = m_opponentWidgets[pos];
//        m_opponentWidgets[pos]->setPlayer(playerList[i]);
//    }
//    for (int i = pI - 1; i >= 0; --i)
//    {
//        int pos = i - pI + 6;
//        m_players[playerList[i].id] = m_opponentWidgets[pos];
//        m_opponentWidgets[pos]->setPlayer(playerList[i]);
//    }*/
//    if (mp_startButton)
//    {
//        mp_startButton->hide();
//        mp_startButton->deleteLater();
//    }
//
//    mp_deck = new DeckWidget(0);
//    mp_deck->init(&m_cardWidgetFactory);
//    mp_graveyard = new CardPileWidget(0);
//    mp_graveyard->setPocketType(POCKET_GRAVEYARD);
//    mp_selection = new CardListWidget(0);
//    mp_selection->setPocketType(POCKET_SELECTION);
//    mp_selection->setCardSize(CardWidget::SIZE_NORMAL);
//    mp_selection->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//
//
//    if (middleWidget->layout() != 0) {
//        delete middleWidget->layout();
//    }
//
//    QBoxLayout* l = new QBoxLayout(QBoxLayout::LeftToRight);
//    l->addStretch(3);
//    l->addWidget(mp_graveyard);
//    l->addStretch(1);
//    l->addWidget(mp_deck);
//    l->addStretch(3);
//
//    QBoxLayout* l2 = new QBoxLayout(QBoxLayout::LeftToRight);
//    l2->addStretch(3);
//    l2->addWidget(mp_selection);
//    l2->addStretch(3);
//
//    QBoxLayout* l3 = new QVBoxLayout();
//    l3->addLayout(l);
//    l3->addStretch(1);
//    l3->addLayout(l2);
//    middleWidget->setLayout(l3);
//}

