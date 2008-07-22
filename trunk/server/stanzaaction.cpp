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

#include "stanzaaction.h"
#include "client.h"
#include "common.h"
#include "game.h"
#include "gameserver.h"



#define ASSERT_AVAILABLE(cond) if (!(cond)) { m_state = STATE_NOT_AVAILABLE; \
                                           writeErrorElement(xmlOut);     \
                                           return; }




QHash<QString, StanzaAction::ExecuteMethod> StanzaAction::sm_methods;
bool StanzaAction::sm_initialized = 0;

StanzaAction::StanzaAction(const QXmlStreamReader& xmlIn):
 Stanza(xmlIn)
{
    if (!sm_initialized) StanzaAction::initializeMethods();
}

void StanzaAction::processToken(const QXmlStreamReader& xmlIn)
{
    Stanza::processToken(xmlIn);
    if (m_state != STATE_OK && m_state != STATE_VOID) return;

    if (xmlIn.isEndElement()) return;
    if ((m_xmlDepth == 1) && xmlIn.isStartElement())
    {
        if (!m_elementName.isNull() || !sm_methods.contains(xmlIn.name().toString()))
        {
            m_state = STATE_BAD_QUERY;
            return;
        }
        m_elementName = xmlIn.name().toString();
        m_attributes  = xmlIn.attributes();
        m_state       = STATE_OK;
    }
    else if (m_xmlDepth == 2  && xmlIn.isStartElement())
    {
        m_optElements[xmlIn.name().toString()] = xmlIn.attributes();
    }
    else
    {
        m_state = STATE_BAD_QUERY;
        return;
    }

}

void StanzaAction::execute(QXmlStreamWriter& xmlOut)
{
    Stanza::execute(xmlOut);
    if (m_state == STATE_VOID) m_state = STATE_BAD_QUERY;
    if (m_state != STATE_OK)
    {
        writeErrorElement(xmlOut);
    }
    else
    {
        Q_ASSERT(sm_methods.contains(m_elementName));
        qDebug() << m_elementName << "triggered by" << client()->id();
        CALL_MEMBER_FN(*this,sm_methods[m_elementName])(xmlOut);
    }
}

void StanzaAction::writeErrorElement(QXmlStreamWriter & xmlOut)
{
    xmlOut.writeStartElement("action");
    xmlOut.writeAttribute("type", "error");
    if (!m_id.isEmpty()) xmlOut.writeAttribute("id", m_id);
    Stanza::writeErrorElement(xmlOut);
    xmlOut.writeEndElement();
}

void StanzaAction::initializeMethods()
{
    sm_methods["create-game"]   = &StanzaAction::createGame;
    sm_methods["join-game"]     = &StanzaAction::joinGame;
    sm_methods["leave-game"]    = &StanzaAction::leaveGame;
    sm_initialized = 1;
}

void StanzaAction::createGame(QXmlStreamWriter& xmlOut)
{
    if (client()->isInGame())
    {
        m_state = STATE_NOT_AVAILABLE;
        writeErrorElement(xmlOut);
        return;
    }

    if (!m_optElements.contains("player"))
    {
        m_state = STATE_NOT_COMPLETE;
        writeErrorElement(xmlOut);
        return;
    }

    QString name             = m_attributes.value("name").toString();
    QString description      = m_attributes.value("desc").toString();
    int     minPlayers       = m_attributes.value("minplayers").toString().toInt();
    int     maxPlayers       = m_attributes.value("maxplayers").toString().toInt();
    int     maxObservers     = m_attributes.value("maxobservers").toString().toInt();
    QString playerPassword   = m_attributes.value("playerpassword").toString();
    QString observerPassword = m_attributes.value("observerpassword").toString();
    bool    shufflePlayers   = m_attributes.value("shuffleplayers").toString().toInt() == 1;

    Game* newGame = GameServer::instance().createGame(name, description, client()->id(), minPlayers, maxPlayers, maxObservers, playerPassword, observerPassword, shufflePlayers);
    Q_ASSERT(newGame);

    QString playerName  = m_optElements["player"].value("name").toString();
    QString playerPass  = m_optElements["player"].value("password").toString();

    Player* newPlayer = newGame->createNewPlayer(playerName, playerPass);
    newPlayer->attachPlayerController(client()->playerController());
    xmlOut.writeStartElement("event");
    xmlOut.writeStartElement("join-game");
    xmlOut.writeAttribute("id", QString::number(newGame->gameId()));
    xmlOut.writeAttribute("type", "player");
    xmlOut.writeEndElement();
    xmlOut.writeEndElement();

    /*
    writeStanzaStartElement(xmlOut);
    xmlOut.writeStartElement("gamelist");
    foreach(Game* game, GameServer::instance().gameList())
    {
        game->writeXml(xmlOut);
    }
    xmlOut.writeEndElement();
    writeStanzaEndElement(xmlOut);
    */
}

void StanzaAction::joinGame(QXmlStreamWriter& xmlOut)
{
    /// TODO: copy&pasted from createGame - to be refactored
    qDebug() << "join-game triggered by" << client()->id();


    ASSERT_AVAILABLE(!client()->isInGame());

    enum type_t { NONE = 0, PLAYER, OBSERVER };
    type_t type = NONE;
    if (m_optElements.contains("player"))
    {
        type = PLAYER;
    }
    else if (m_optElements.contains("observer"))
    {
        type = OBSERVER;
    }

    if (!type)
    {
        m_state = STATE_NOT_COMPLETE;
        writeErrorElement(xmlOut);
        return;
    }

    int gameId             = m_attributes.value("id").toString().toInt();
    QString accessPassword = m_attributes.value("password").toString();

    Game* game = GameServer::instance().game(gameId);
    if (!game)
    {
        m_state = STATE_NOT_EXIST;
        writeErrorElement(xmlOut);
        return;
    }
    bool access = (type == PLAYER) ? game->comparePlayerPassword(accessPassword)
                                   : game->compareObserverPassword(accessPassword);
    if (!access)
    {
        m_state = STATE_ACCESS_DENIED;
        writeErrorElement(xmlOut);
        return;
    }

    Q_ASSERT(type == PLAYER); // TODO: implement joining observers

    QString playerName  = m_optElements["player"].value("name").toString();
    QString playerPass  = m_optElements["player"].value("password").toString();

    Player* newPlayer = game->createNewPlayer(playerName, playerPass);
    newPlayer->attachPlayerController(client()->playerController());
    xmlOut.writeStartElement("event");
    xmlOut.writeStartElement("join-game");
    xmlOut.writeAttribute("id", QString::number(game->gameId()));
    xmlOut.writeAttribute("type", "player");
    xmlOut.writeEndElement();
    xmlOut.writeEndElement();

}

void StanzaAction::leaveGame(QXmlStreamWriter& xmlOut)
{
    ASSERT_AVAILABLE(client()->isInGame());
    client()->player()->detachPlayerController();
}




StanzaAction::~StanzaAction()
{
}

