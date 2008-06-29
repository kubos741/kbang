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
#ifndef COMMAND_H
#define COMMAND_H

#include <QXmlStreamAttributes>
#include <QTextStream>

class QXmlStreamWriter;

/**
 * The Command class represent a single action that was encountered by either
 * client or server and typically has reactions (other Commands). It's the
 * use of the command design pattern.
 * Command has three important roles.
 * First it has to be built by parts. Commands can be created from stanzas
 * (xml subtrees) and therefore it needs to have the capability of building
 * itself from a sequence of xml elements.
 * The second role is to execute the action. As soon as the command is built
 * the action can be triggered. The command is responsible for processing
 * the specified task it was built for.
 * The third important role is generating another commands, typically the response
 * for the sender.
 *
 * The Command class is abstract, its subclasses are concrete commands with building
 * mechanism and execution logic hardwired inside.
 * The Command class supply a factory method to build a specific commands according the
 * stanza element name.
 *
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Command {
protected:
    Command(const QXmlStreamReader& xml):
        m_xmlId(xml.attributes().value("id").toString()),
        m_invalid(0),
        m_xmlDepth(0) {}
private:
    Command(const Command&) {}
public:
    virtual void processToken(const QXmlStreamReader& xml) = 0;
    //virtual QString execute() = 0;
    virtual void execute(QXmlStreamWriter& xmlOut) = 0;
    virtual ~Command() {};

protected:
    virtual void setInvalid();


public:
    /**
     * The static factory method for creating instances of Command subclasses. Given a
     * stanzaName, a new instance of corresponding Command subclass is returned.
     */
    static Command* create(const QXmlStreamReader& xml);
protected:
    QString m_xmlId;    // the id of the stanza
    int     m_invalid;
    int     m_xmlDepth;
};

#endif
