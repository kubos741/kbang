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

#include <QRegExpValidator>
#include <QRegExp>

#include "creategamedialog.h"
#include "config.h"
#include "gamestructs.h"

#include "ui_creategamedialog.h"


using namespace client;

const int minPlayers = 4, maxPlayers = 7;

CreateGameDialog::CreateGameDialog(QWidget* parent):
        QDialog(parent),
        mp_ui(new Ui::CreateGameDialog())
{
    mp_ui->setupUi(this);

    mp_ui->pushButtonCreate->setEnabled(0);

    mp_ui->spinBoxMinPlayers->setRange(minPlayers, maxPlayers);
    mp_ui->spinBoxMaxPlayers->setRange(minPlayers, maxPlayers);
    mp_ui->spinBoxAIPlayers->setRange(0, maxPlayers - 1);

    if (Config::instance().hasGroup("create-game-dialog")) {
        loadConfigValues();
    } else {
        mp_ui->spinBoxMinPlayers->setValue(minPlayers);
        mp_ui->spinBoxMaxPlayers->setValue(maxPlayers);
        mp_ui->spinBoxAIPlayers->setValue(0);
        mp_ui->spinBoxMaxSpectators->setValue(-1);
    }

    connect(mp_ui->spinBoxMinPlayers, SIGNAL(valueChanged(int)),
            this, SLOT(playerCountsChanged()));
    connect(mp_ui->spinBoxMaxPlayers, SIGNAL(valueChanged(int)),
            this, SLOT(playerCountsChanged()));

    connect(mp_ui->lineEditGameName,   SIGNAL(textChanged(const QString&)),
            this, SLOT(validateInput()));
    connect(mp_ui->lineEditPlayerName, SIGNAL(textChanged(const QString&)),
            this, SLOT(validateInput()));

    connect(mp_ui->pushButtonCreate, SIGNAL(clicked()),
            this, SLOT(onCreateGameClicked()));
}


CreateGameDialog::~CreateGameDialog()
{
    delete mp_ui;
}

void CreateGameDialog::playerCountsChanged()
{
    mp_ui->spinBoxMinPlayers->setMaximum(mp_ui->spinBoxMaxPlayers->value());
    mp_ui->spinBoxMaxPlayers->setMinimum(mp_ui->spinBoxMinPlayers->value());
    mp_ui->spinBoxAIPlayers->setMaximum(mp_ui->spinBoxMaxPlayers->value() - 1);
}

void CreateGameDialog::validateInput()
{
    mp_ui->pushButtonCreate->setEnabled(!mp_ui->lineEditGameName->text().isEmpty() &&
                                        !mp_ui->lineEditPlayerName->text().isEmpty());
}

void CreateGameDialog::onCreateGameClicked()
{
    CreateGameData createGameData;
    createGameData.name                 = mp_ui->lineEditGameName->text();
    createGameData.desc                 = mp_ui->lineEditGameDescription->text();
    createGameData.playersMin           = mp_ui->spinBoxMinPlayers->value();
    createGameData.playersMax           = mp_ui->spinBoxMaxPlayers->value();
    createGameData.spectatorsMax        = mp_ui->spinBoxMaxSpectators->value();
    createGameData.aiPlayersCnt         = mp_ui->spinBoxAIPlayers->value();
    createGameData.playerPassword       = mp_ui->lineEditGamePasswordPlayers->text();
    createGameData.spectatorPassword    = mp_ui->lineEditGamePasswordSpectators->text();
    createGameData.options["shufflePlayers"] = mp_ui->radioButtonOrderRandom->isChecked();

    CreatePlayerData createPlayerData;
    createPlayerData.name               = mp_ui->lineEditPlayerName->text();
    createPlayerData.password           = mp_ui->lineEditPlayerPassword->text();
    QBuffer buffer(&createPlayerData.avatar);
    buffer.open(QIODevice::WriteOnly);
    mp_ui->selectAvatarWidget->avatar().save(&buffer, "PNG");

    saveConfigValues(createGameData);

    emit createGame(createGameData, createPlayerData);
    close();
}


void CreateGameDialog::loadConfigValues()
{
    Config& cfg = Config::instance();
    cfg.refresh();
    QString grp("create-game-dialog");
    mp_ui->lineEditGameName->setText(cfg.readString(grp, "name"));
    mp_ui->lineEditGameDescription->setText(cfg.readString(grp, "description"));
    mp_ui->spinBoxMinPlayers->setValue(cfg.readInt(grp, "min-players"));
    mp_ui->spinBoxMaxPlayers->setValue(cfg.readInt(grp, "max-players"));
    mp_ui->spinBoxMaxSpectators->setValue(cfg.readInt(grp, "max-spectators"));
    mp_ui->spinBoxAIPlayers->setValue(cfg.readInt(grp, "ai-players"));
    int shufflePlayers = cfg.readInt(grp, "flag-shuffle-players");
    if (shufflePlayers) {
        mp_ui->radioButtonOrderRandom->setChecked(1);
    } else {
        mp_ui->radioButtonOrderChronological->setChecked(1);
    }
    mp_ui->lineEditPlayerName->setText(cfg.readString("player", "name"));
    mp_ui->lineEditPlayerPassword->setText(cfg.readString("player", "password"));
    mp_ui->selectAvatarWidget->loadAvatar(cfg.readString("player", "image"));
    validateInput();
}

void CreateGameDialog::saveConfigValues(const CreateGameData& game)
{
    ///@todo change config var names
    Config& cfg = Config::instance();
    QString grp("create-game-dialog");
    cfg.writeString(grp, "name", game.name);
    cfg.writeString(grp, "description", game.desc);
    cfg.writeInt(grp, "min-players", game.playersMin);
    cfg.writeInt(grp, "max-players", game.playersMax);
    cfg.writeInt(grp, "max-spectators", game.spectatorsMax);
    cfg.writeInt(grp, "ai-players", game.aiPlayersCnt);

    ///cfg.writeInt(grp, "flag-shuffle-players", game.flagShufflePlayers);

    cfg.writeString("player", "name", mp_ui->lineEditPlayerName->text());
    cfg.writeString("player", "password", mp_ui->lineEditPlayerPassword->text());
    cfg.writeString("player", "image", mp_ui->selectAvatarWidget->avatarFilePath());

    cfg.store();
}

