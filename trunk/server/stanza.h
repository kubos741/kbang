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
#ifndef STANZA_H
#define STANZA_H

#include <QXmlStreamAttributes>
#include <QTextStream>

class QXmlStreamWriter;

/**
 * The Stanza class represents a recieved stanza from a client. Since
 * xml stanzas are recieved as a sequence of xml tokens, it's not possible
 * to construct whole Stanza instance at once. Instead a &quot;void&quot; stanza
 * is constructed and then it is fed with xml tokens. When the stanza is complete,
 * it is executed.
 * Generally when a root element of a stanza is recieved, it is send to the factory
 * method that constructs an incomplete Stanza instance depending on the type
 * of the stanza. The processToken method is then called for every xml token inside of
 * that stanza. After all the tokens from stanza are send to the instance, the stanza
 * is complete and the execute method is called. Because every recieved stanza should
 * respond somehow, the reference to XmlStreamWriter is passed in the execute method call.
 *
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Stanza {
public:
    enum State { STATE_OK, STATE_NOT_EXIST,
                 STATE_INVALID_TYPE, STATE_MISSING_ID,
                 STATE_BAD_QUERY, STATE_BAD_ACTION };

protected:
    /**
     * Constructs the (incomplete) stanza instance according to the root xml element
     * of the stanza. The constructor should not be used
     * @param xmlIn The root xml element of the stanza is gotten from the QXmlStreamReader object.
     */
    Stanza(const QXmlStreamReader& xmlIn);

private:
    Stanza(const Stanza&) {}

public:
    /**
     * This method processes an xml token of the stanza.
     * @param xmlIn the QXmlStreamReader pointing to current (processed) token
     * @see class Stanza
     */
    virtual void processToken(const QXmlStreamReader& xmlIn);

    /**
     * This method executes the stanza. The stanza must be complete,
     * which means that the last token passed to processToken must be
     * the end root element of the stanza.
     * @param xmlOut The execution of stanza may (and almost always will)
     *               produce output to the client - through the QXmlStreamWriter
     */
    virtual void execute(QXmlStreamWriter& xmlOut);
    virtual ~Stanza() {}
    static Stanza* construct(const QXmlStreamReader& xmlIn);

protected:
    virtual void writeErrorElement(QXmlStreamWriter& xmlOut);

protected:
    State                m_state;
    QString              m_id;
    int                  m_xmlDepth;
    bool                 m_complete;

};

#endif
