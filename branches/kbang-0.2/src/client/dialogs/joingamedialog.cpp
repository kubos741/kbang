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

#include <QInputDialog>
#include <QHeaderView>

#include "joingamedialog.h"
#include "serverconnection.h"

#include "common.h"

#include "ui_joingamedialog.h"

using namespace client;

class QueryHandler: public QueryResultHandler
{
public:
    QueryHandler(JoinGameDialog* s): mp_s(s) {}
    virtual void resultReceived(const GameStructPtr& data) {
        if (data->t() == GameStruct::GameInfoListType) {
            mp_s->setGameList(*data.staticCast<GameInfoListData>());
        }
    }
    JoinGameDialog* mp_s;
};

JoinGameDialog::JoinGameDialog(QWidget *parent):
        QDialog(parent),
        m_currentGameId(0),
        m_currentPlayerId(0),
        mp_handler(new QueryHandler(this)),
        mp_ui(new Ui::JoinGameDialog())
{
    mp_ui->setupUi(this);
    connect(mp_ui->pushButtonRefresh, SIGNAL(clicked()),
            this, SLOT(doRefresh()));
    connect(mp_ui->pushButtonPlay, SIGNAL(clicked()),
            this, SLOT(doPlay()));
    connect(mp_ui->pushButtonSpectate, SIGNAL(clicked()),
            this, SLOT(doSpectate()));
    connect(mp_ui->lineEditPlayerName, SIGNAL(textChanged(QString)),
            this, SLOT(updateButtons()));
    connect(mp_ui->gameListView, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(doClickGameListItem(QTreeWidgetItem*,int)));
    connect(mp_ui->playerListView, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(doClickPlayerListItem(QTreeWidgetItem*,int)));

    mp_ui->gameListView->header()->setResizeMode(QHeaderView::ResizeToContents);
    mp_ui->gameListView->setHeaderLabels(QStringList() << tr("Game") <<
                                         tr("State") << tr("Players") << "");

    mp_ui->playerListView->header()->setResizeMode(QHeaderView::ResizeToContents);
    mp_ui->playerListView->setHeaderLabels(QStringList() << tr("Player") <<
                                           "" << "" << "");

    updateGameListView();
    updateGameView();
    loadConfigValues();
}

/* virtual */
JoinGameDialog::~JoinGameDialog()
{
    delete mp_handler;
}

void JoinGameDialog::show()
{
    doRefresh();
    QDialog::show();
}

void JoinGameDialog::setGameList(const GameInfoListData& gameList)
{
    m_gameList = gameList;
    updateGameListView();
    updateGameView();
    updateButtons();
}

void JoinGameDialog::doClickGameListItem(QTreeWidgetItem* item, int column)
{
    Q_UNUSED(column);
    m_currentGameId = item->data(0, Qt::UserRole).toUInt();
    updateGameView();
    updateButtons();
}

void JoinGameDialog::doClickPlayerListItem(QTreeWidgetItem* item, int column)
{
    Q_UNUSED(column);
    m_currentPlayerId = item->data(0, Qt::UserRole).toUInt();
    updateButtons();
}

void JoinGameDialog::doRefresh()
{
    QueryGameInfoListGetPtr query(new QueryGameInfoListGet());
    ServerConnection::instance()->sendQueryGet(query, mp_handler);
}

void JoinGameDialog::doPlay()
{
    doJoinGame(0);
}

void JoinGameDialog::doSpectate()
{
    doJoinGame(1);
}

void JoinGameDialog::updateButtons()
{
    bool enableSpectate = (m_currentGameId != 0);
    bool enablePlay = enableSpectate && (m_currentPlayerId != 0) &&
                        !mp_ui->lineEditPlayerName->text().isEmpty();
    mp_ui->pushButtonSpectate->setEnabled(enableSpectate);
    mp_ui->pushButtonPlay->setEnabled(enablePlay);
}

/* static */
QString JoinGameDialog::gameStateDisplayString(GameState gameState)
{
    switch(gameState) {
    case GAMESTATE_WAITINGFORPLAYERS:   return tr("waiting");
    case GAMESTATE_PLAYING:             return tr("playing");
    case GAMESTATE_FINISHED:            return tr("finished");
    default: break;
    }
    return "";
}

void JoinGameDialog::updateGameListView()
{
    bool isCurrentGameInList = 0;
    mp_ui->gameListView->clear();
    foreach (const GameInfoData& game, m_gameList) {
        QTreeWidgetItem* gameItem = new QTreeWidgetItem(mp_ui->gameListView);
        gameItem->setData(0, Qt::UserRole, game.id);
        gameItem->setText(0, game.name);
        gameItem->setText(1, gameStateDisplayString(game.gameState));
        switch(game.gameState) {
        case GAMESTATE_WAITINGFORPLAYERS:
            gameItem->setText(2, QString("%1 / %2").arg(game.playersCnt).
                              arg(game.playersMax));
            break;
        case GAMESTATE_PLAYING:
            gameItem->setText(2, QString("%1 / %2").arg(game.alivePlayersCnt).
                              arg(game.playersCnt));
            break;
        case GAMESTATE_FINISHED:
            gameItem->setText(2, QString("%1 / %2").arg(game.alivePlayersCnt).
                              arg(game.playersCnt));
            break;
        default:
            NOT_REACHED();
        }
        if (game.id == m_currentGameId) {
            mp_ui->gameListView->setCurrentItem(gameItem);
            isCurrentGameInList = 1;
        }
    }
    if (!isCurrentGameInList) {
        m_currentGameId = 0;
    }
}

void JoinGameDialog::updateGameView()
{
    GameInfoData game;
    foreach (const GameInfoData& g, m_gameList) {
        if (g.id == m_currentGameId) {
            game = g;
            break;
        }
    }

    mp_ui->labelName->setText(game.name);
    mp_ui->labelDesc->setText(game.desc);
    mp_ui->labelState->setText(gameStateDisplayString(game.gameState));

    mp_ui->playerListView->clear();

    foreach (const PlayerInfoData& player, game.players) {
        QTreeWidgetItem * playerItem = new QTreeWidgetItem();
        playerItem->setData(0, Qt::UserRole, player.id);
        playerItem->setText(0, player.name);
        if (player.hasController) {
            playerItem->setIcon(1, QIcon(":/icons/connect.png"));
            playerItem->setData(1, Qt::ToolTipRole, tr("Connected"));
        } else {
            playerItem->setIcon(1, QIcon(":/icons/disconnect.png"));
            playerItem->setData(1, Qt::ToolTipRole, tr("Disconnected"));
        }
        if (player.isAI) {
            playerItem->setIcon(2, QIcon(":/icons/ai.png"));
            playerItem->setData(2, Qt::ToolTipRole, tr("Artifical Intelligence"));
        } else {
            playerItem->setIcon(2, QIcon(":/icons/human.png"));
            playerItem->setData(2, Qt::ToolTipRole, tr("Human Player"));
        }

        if (player.isAlive) {
            playerItem->setIcon(3, QIcon(":/icons/alive.png"));
            playerItem->setData(3, Qt::ToolTipRole, tr("Player is Alive"));
        } else {
            playerItem->setIcon(3, QIcon(":/icons/dead.png"));
            playerItem->setData(3, Qt::ToolTipRole, tr("Player is Dead"));
        }
#if 0
        if (player.hasController && !player.isAI) {
            item->setDisabled(1);
        } else {
            item->setDisabled(0);
        }
#endif
        mp_ui->playerListView->addTopLevelItem(playerItem);

        if (player.id == m_currentPlayerId) {
            mp_ui->playerListView->setCurrentItem(playerItem);
        }
    }

    if (game.gameState == GAMESTATE_WAITINGFORPLAYERS &&
        game.playersCnt < game.playersMax) {
        QTreeWidgetItem* playerItem = new QTreeWidgetItem();
        playerItem->setData(0, Qt::UserRole, -1);
        playerItem->setText(0, QObject::tr("Create new player"));
        QFont font;
        font.setItalic(1);
        playerItem->setData(0, Qt::FontRole, font);
        mp_ui->playerListView->addTopLevelItem(playerItem);
        if (m_currentPlayerId == -1) {
            mp_ui->playerListView->setCurrentItem(playerItem);
        }
    }
}

void JoinGameDialog::doJoinGame(bool spectate)
{
    if (m_currentGameId == 0) {
        qWarning("JoinGameDialog: trying to join without game selected.");
        return;
    }

    const GameInfoData* game = 0;
    foreach (const GameInfoData& g, m_gameList) {
        if (g.id == m_currentGameId) {
            game = &g;
            break;
        }
    }
    if (game == 0) {
        qWarning("JoinGameDialog: trying to join unexisting game.");
        return;
    }

    QString password;
    if (!spectate && game->hasPlayerPassword || game->hasSpectatorPassword) {
        bool ok;
        password = QInputDialog::getText(this, tr("Enter password"),
                                         tr("The game is protected by password. Please enter the password:"),
                                          QLineEdit::Password, "", &ok);
         if (!ok || password.isEmpty())
             return;
    }


    ActionJoinGameDataPtr actionJoinGame(new ActionJoinGameData());
    actionJoinGame->gameId   = m_currentGameId;
    actionJoinGame->playerId = m_currentPlayerId;
    actionJoinGame->gamePassword = password;

    actionJoinGame->createPlayerData.name = mp_ui->lineEditPlayerName->text();
    actionJoinGame->createPlayerData.password =
            mp_ui->lineEditPlayerPassword->text();
    actionJoinGame->createPlayerData.avatar =
            mp_ui->selectAvatarWidget->avatarData();

    emit joinGame(actionJoinGame);
    saveConfigValues();
    close();
}

void JoinGameDialog::loadConfigValues()
{
    Config& cfg = Config::instance();
    cfg.refresh();
    mp_ui->lineEditPlayerName->setText(cfg.readString("player", "name"));
    mp_ui->lineEditPlayerPassword->setText(cfg.readString("player", "password"));
    mp_ui->selectAvatarWidget->loadAvatar(cfg.readString("player", "avatar"));
    updateButtons();
}

void JoinGameDialog::saveConfigValues()
{
    Config& cfg = Config::instance();
    cfg.writeString("player", "name", mp_ui->lineEditPlayerName->text());
    cfg.writeString("player", "password", mp_ui->lineEditPlayerPassword->text());
    cfg.writeString("player", "avatar", mp_ui->selectAvatarWidget->avatarFilePath());
    cfg.store();
}


