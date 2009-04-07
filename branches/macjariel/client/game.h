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
#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QHash>
#include <QList>
#include <QQueue>
#include <QPushButton>
#include "parser/parserstructs.h"
#include "common.h"
#include "deckwidget.h"
#include "playerwidget.h"

namespace client {

class ServerConnection;
class GameEventHandler;

/**
 * @author MacJariel <MacJariel@gmail.com>
 */
class Game: public QObject {
Q_OBJECT;
public:
    Game(QObject* parent, int gameId, const StructPlayer&, ServerConnection*, const GameWidgets&, QWidget*);

    /* for MainWindow */
    void init();
    virtual ~Game();

    void setCreator(bool creator) { m_creator = creator; }

    void setCurrentPlayerId(int currentPlayerId);
    void setRequestedPlayerId(int requestedPlayerId);



    inline DeckWidget*     deck() const               { return mp_deck; }
    inline CardPileWidget* graveyard() const          { return mp_graveyard; }
    inline PlayerWidget*   playerWidget(int id) const { return m_players.contains(id) ? m_players[id] : 0; }
    inline QWidget*        mainWidget() const         { return mp_mainWidget; }

    inline int             currentPlayerId() const    { return m_currentPlayerId; }
    inline int             requestedPlayerId() const  { return m_requestedPlayerId; }

private:



private:
    const int m_playerId;
    const QString m_playerName;
    const int m_gameId;
    ServerConnection* mp_serverConnection;

    int m_currentPlayerId;
    int m_requestedPlayerId;



/*  Visual elements - provided by MainWindow */
    QGridLayout*              mp_layout;
    QList<OpponentWidget*>    m_opponentWidgets;
    QHash<int, PlayerWidget*> m_players;
    LocalPlayerWidget*        mp_localPlayerWidget;
    QPushButton*              mp_startButton;
    DeckWidget*               mp_deck;
    CardPileWidget*           mp_graveyard;
    bool                      m_creator;
    QQueue<StructCardMovement> m_cardMovementQueue;
    QWidget*                  mp_mainWidget;
    GameEventHandler*         mp_gameEventHandler;




public slots:
    void opponentJoinedGame(const StructPlayer& player);
    void opponentLeavedGame(const StructPlayer& player);
    void startableChanged(int gameId, bool startable);
    void startButtonClicked();
    void gameStarted(const StructGame&, const StructPlayerList&);

    void initialGameStateRecieved(const StructGame&, const StructPlayerList& playerList);



    void test();
};
}
#endif
