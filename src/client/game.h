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
#ifndef GAME_H
#define GAME_H

#include <QPushButton>
#include <QList>
#include <QMap>

#include "gamestructs.h"

namespace client {
// Widgets:
class PlayerWidget;
class LocalPlayerWidget;
class DeckWidget;
class GraveyardWidget;
class CardListWidget;

class GameEventHandler;
class GameEventQueue;
class GameActionManager;

/**
 *
 * @author MacJariel <MacJariel@gmail.com>
 */
class Game: public QObject {
Q_OBJECT;
public:
    static void enterGameMode(GameId, QString gameName, ClientType);

    void leaveGameMode();

    /**
     * Returns the pointer to the current game or 0 if client
     * is not in game.
     */
    inline static Game* currentGame() {
        return smp_currentGame;
    }

    /**
     * Returns whether client is in a game.
     */
    inline static bool isInGame() {
        return (smp_currentGame != 0);
    }

    /**
     * Returns the ClientType of the game.
     */
    inline ClientType clientType() const {
        return m_clientType;
    }

    /**
     * Returns the PlayerWidget of the player with given <i>id</i>
     * or 0, if such PlayerWidget is not found.
     */
    inline PlayerWidget* playerWidget(PlayerId id) const {
        return m_playerWidgets.value(id, 0);
    }

    /**
     * Returns the widget of local player, or 0 if game is in spectator mode.
     */
    inline LocalPlayerWidget* localPlayerWidget() const {
        return mp_localPlayerWidget;
    }

    /**
     * Returns the DeckWidget, or 0 if it was not created yet.
     */
    inline DeckWidget* deck() const {
        return mp_deck;
    }

    /**
     * Returns the GraveyardWidget. or 0 if it was not created yet.
     */
    inline GraveyardWidget* graveyard() const {
        return mp_graveyard;
    }

    /**
     * Returns the CardListWidget for selection pocket, or 0 if it was not
     * created yet.
     */
    inline CardListWidget* selection() const {
        return mp_selection;
    }

    /**
     * Returns the id of current player.
     */
    inline PlayerId currentPlayerId() const {
        return m_gameContextData.currentPlayerId;
    }

    /**
     * Returns the id of requested player.
     */
    inline PlayerId requestedPlayerId() const {
        return m_gameContextData.requestedPlayerId;
    }

    /**
     * Returns the current GamePlayState.
     */
    inline GamePlayState gamePlayState() const {
        return m_gameContextData.gamePlayState;
    }

    /**
     * Returns, whether local player is requested.
     */
    inline bool isRequested() const {
        return (localPlayerId() == requestedPlayerId());
    }

    /**
     * Returns the id of the local player, or 0 in spectator mode.
     */
    inline PlayerId localPlayerId() const {
        return m_localPlayerId;
    }

    /**
     * Returns the character of local player, or empty string in spectator mode.
     */
    QString localCharacter() const;

    inline bool isCreator() const {
        return m_isCreator;
    }

    /**
     * Returns whether the game already finished.
     */
    inline bool isFinished() const {
        return (m_gameState == GAMESTATE_FINISHED);
    }

    inline GameEventHandler* eventHandler() const {
        return mp_gameEventHandler;
    }

    inline GameEventQueue* eventQueue() const {
        return mp_gameEventQueue;
    }

    inline GameActionManager* actionManager() const {
        return mp_gameActionManager;
    }

    void setIsCreator(bool isCreator) {
        m_isCreator = isCreator;
    }

    /**
     * Sets the widget of the local player according to PublicPlayerData.
     * Does nothing in spectator mode.
     * First use setLocalPlayer(PublicPlayerData), then
     * setLocalPlayer(PrivatePlayerData).
     */
    void setLocalPlayer(const PublicPlayerData&);

    /**
     * Sets the widget of the local player according to PrivatePlayerData.
     * Does nothing in spectator mode.
     * First use setLocalPlayer(PublicPlayerData), then
     * setLocalPlayer(PrivatePlayerData).
     */
    void setLocalPlayer(const PrivatePlayerData&);

    /**
     * Sets the state of the game.
     */
    void setGameState(const GameState&);

    /**
     * Sets game context
     */
    void setGameContext(const GameContextData&);

    /**
     * Sets the selection.
     */
    void setSelection(QList<CardData>);

    /**
     * Sets the graveyard top card.
     */
    void setGraveyard(const CardData&);

    /**
     * Changes the game interface, if necessary.
     */
    void updateInterface();

    /**
     * Cleans the UI after leaving the game mode.
     */
    void cleanUp();

    /**
     * Sets the text-info string.
     */
    void setTextInfo(const QString&);

    /**
     * Unsets the text-info string.
     */
    void unsetTextInfo();

    /**
     * Adds new opponent according to PublicPlayerData. The opponent is
     * added to first unused opponentWidget. This method should be used only
     * before game is started, because the resulting player order may differ
     * from the correct one.
     */
    void appendOpponent(const PublicPlayerData&);

    /**
     * Inserts new opponent according to PublicPlayerData. The opponent is
     * added to the OpponentWidget with given <i>index</i>. Index with positive
     * value counts from the local player clock-wise, and with negative value
     * counts counter-clock-wise.
     */
    void insertOpponent(int index, const PublicPlayerData&);

    /**
     * Removes the opponent with given <i>id</i>.
     */
    void removeOpponent(PlayerId id);

    /**
     * Updates the opponent according to PublicPlayerData. First the right
     * OpponentWidget is found and then this widget is updated with PublicPlayerData.
     */
    void updateOpponent(const PublicPlayerData&);

    /**
     * Clears opponent widget specified with index.
     */
    void clearOpponentWidget(int index);

    /**
     * Pauses the dequeuing of incoming game events.
     */
    void pauseGameEvents();

    /**
     * Resumes the dequeuing of incoming game events.
     */
    void resumeGameEvents();

public slots:
    void setGameStartability(bool);

private:
    Game(GameId, QString gameName, ClientType);
    virtual ~Game();

    void loadCreatorInterface();
    void unloadCreatorInterface();
    void loadGameInterface();
    void unloadGameInterface();
    void unloadInterface();

    enum InterfaceType {
        NoInterface = 0,
        CreatorInterface,
        GameInterface
    };

    GameId          m_gameId;
    QString         m_gameName;
    ClientType      m_clientType;
    PlayerId        m_localPlayerId;
    GameState       m_gameState;
    GameContextData m_gameContextData;
    InterfaceType   m_interfaceType;
    bool            m_isCreator;

    QMap<PlayerId, PlayerWidget*>   m_playerWidgets;
    QList<PlayerWidget*>            m_playerWidgetsList;

    QPushButton*        mp_startButton;
    DeckWidget*         mp_deck;
    GraveyardWidget*    mp_graveyard;
    CardListWidget*     mp_selection;
    LocalPlayerWidget*  mp_localPlayerWidget;

    GameEventHandler*   mp_gameEventHandler;
    GameEventQueue*     mp_gameEventQueue;
    GameActionManager*  mp_gameActionManager;

    static Game*        smp_currentGame;
};
}
#endif
