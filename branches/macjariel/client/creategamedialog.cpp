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

using namespace client;

const int minPlayers = 4, maxPlayers = 7;

CreateGameDialog::CreateGameDialog(QWidget *parent)
 : QDialog(parent), Ui::CreateGameDialog()
{
    setupUi(this);

    lineEditPlayerPassword->setEnabled(0);
    pushButtonCreate->setEnabled(0);


    spinBoxMinPlayers->setRange(minPlayers, maxPlayers);
    spinBoxMaxPlayers->setRange(minPlayers, maxPlayers);
    spinBoxAIPlayers->setRange(0, maxPlayers - 1);

    ///@todo: load last values from config file
    spinBoxMinPlayers->setValue(minPlayers);
    spinBoxMaxPlayers->setValue(maxPlayers);
    spinBoxAIPlayers->setValue(0);

    connect(spinBoxMinPlayers, SIGNAL(valueChanged(int)),
            this, SLOT(playerCountsChanged()));
    connect(spinBoxMaxPlayers, SIGNAL(valueChanged(int)),
            this, SLOT(playerCountsChanged()));

    connect(lineEditGameName,   SIGNAL(textChanged(const QString&)),
            this, SLOT(validateInput()));
    connect(lineEditPlayerName, SIGNAL(textChanged(const QString&)),
            this, SLOT(validateInput()));
}


CreateGameDialog::~CreateGameDialog()
{
}

void CreateGameDialog::playerCountsChanged()
{
    spinBoxMinPlayers->setMaximum(spinBoxMaxPlayers->value());
    spinBoxMaxPlayers->setMinimum(spinBoxMinPlayers->value());
    spinBoxAIPlayers->setMaximum(spinBoxMaxPlayers->value() - 1);
}

void CreateGameDialog::validateInput()
{
    pushButtonCreate->setEnabled(!lineEditGameName->text().isEmpty() &&
                                 !lineEditPlayerName->text().isEmpty());
}

void CreateGameDialog::on_pushButtonCreate_clicked()
{
    CreateGameData createGameData;
    createGameData.name                 = lineEditGameName->text();
    createGameData.description          = lineEditGameDescription->text();
    createGameData.minPlayers           = spinBoxMinPlayers->value();
    createGameData.maxPlayers           = spinBoxMaxPlayers->value();
    createGameData.maxSpectators        = spinBoxMaxSpectators->value();
    createGameData.AIPlayers            = spinBoxAIPlayers->value();
    createGameData.playerPassword       = lineEditGamePasswordPlayers->text();
    createGameData.spectatorPassword    = lineEditGamePasswordSpectators->text();
    createGameData.flagShufflePlayers   = radioButtonOrderRandom->isChecked();

    CreatePlayerData createPlayerData;
    createPlayerData.name               = lineEditPlayerName->text();
    createPlayerData.password           = lineEditPlayerPassword->text();
    ///@todo send avatar

    emit createGame(createGameData, createPlayerData);
    close();
}


