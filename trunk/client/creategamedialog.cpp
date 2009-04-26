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

const int minPlayers = 3, maxPlayers = 7;

CreateGameDialog::CreateGameDialog(QWidget *parent)
 : QDialog(parent), Ui::CreateGameDialog()
{
    setupUi(this);

    lineEditPlayerPassword->setEnabled(0);
    pushButtonCreate->setEnabled(0);


    spinBoxMinPlayers->setRange(minPlayers, maxPlayers);
    spinBoxMaxPlayers->setRange(minPlayers, maxPlayers);
    spinBoxMinPlayers->setValue(minPlayers);
    spinBoxMaxPlayers->setValue(maxPlayers);

    lineEditPlayerPassword->setEnabled(0);

    connect(spinBoxMinPlayers, SIGNAL(valueChanged(int)),
            this, SLOT(playerRangeChanged()));

    connect(checkBoxEnablePlayerPassword, SIGNAL(toggled(bool)),
            lineEditPlayerPassword, SLOT(setEnabled(bool)));

    connect(lineEditGameName, SIGNAL(textChanged(const QString&)),
            this, SLOT(validateInput()));
    connect(lineEditPlayerName, SIGNAL(textChanged(const QString&)),
            this, SLOT(validateInput()));

    connect(checkBoxEnablePlayerPassword, SIGNAL(clicked(bool)),
            lineEditPlayerPassword, SLOT(setEnabled(bool)));


}


CreateGameDialog::~CreateGameDialog()
{
}

void CreateGameDialog::playerRangeChanged()
{
    spinBoxMinPlayers->setMaximum(spinBoxMaxPlayers->value());
    spinBoxMaxPlayers->setMinimum(spinBoxMinPlayers->value());
}

void CreateGameDialog::validateInput()
{
    if(lineEditGameName->text().isEmpty() ||
       lineEditPlayerName->text().isEmpty()) pushButtonCreate->setEnabled(0);
    else pushButtonCreate->setEnabled(1);
}

void CreateGameDialog::on_pushButtonCreate_clicked()
{
    StructGame game;
    game.name = lineEditGameName->text();
    game.description = lineEditGameDescription->text();
    game.minPlayers = spinBoxMinPlayers->value();
    game.maxPlayers = spinBoxMaxPlayers->value();
    game.hasPlayerPassword = checkBoxEnablePlayerPassword->isChecked();
    if (game.hasPlayerPassword)
        game.playerPassword = lineEditPlayerPassword->text();
    game.flagShufflePlayers = checkBoxShufflePlayers->isChecked();

    StructPlayer player;
    player.name = lineEditPlayerName->text();
    emit createGame(game, player);
    close();
}


