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
 * to construct whole Stanza instance at once. Instead a "void" stanza
 * is constructed and then it is fed with xml tokens. When the stanza is complete,
 * it is executed.
 * Generally when a root element of a stanza is recieved, it is send to the factory
 * method that constructs a void Stanza instance depending on the type of the stanza.
 * The processToken method is then called for every xml token inside that stanza.
 * After all the tokens from stanza are send to the instance, the stanza
 * is complete and the execute method is called. Because every recieved stanza should
 * respond somehow, the reference to XmlStreamWriter is passed when calling the execute method.
 * This class is subclassed for concrete stanza types. The factory method creates
 * the instance of these subclases according to the stanza type. If the type is unknown,
 * instance of this class is created. Such instance does nothing.
 *
 * @note This class handles only stanzas recieved from client. The outgoing stanzas are
 * typically generated in execute method.
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Stanza {
protected:
    enum State { STATE_VOID, STATE_OK, STATE_NOT_EXIST,
                 STATE_INVALID_TYPE, STATE_MISSING_ID,
                 STATE_BAD_QUERY, STATE_BAD_ACTION };

    /**
     * Constructs the void stanza instance. This is used for unknown
     * stanzas, otherwise a constructor of a subclass is used.
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

    /**
     * This method constructs the stanzas according to their types. This
     * is the only way that should be used for creating stanzas.
     */
    static Stanza* construct(const QXmlStreamReader& xmlIn);

protected:
    /**
     * This method will read the state of the stanza and
     * writes error element according its state. This method
     * should be used in subclasses, since the list of possible
     * error elements is defined in this class. Nevertheless
     * this method is virtual and could be overwrittten in subclasses.
     * @param xmlOut xml stream for output
     */
    virtual void writeErrorElement(QXmlStreamWriter& xmlOut);

protected:
    State                m_state;
    QString              m_id;
    int                  m_xmlDepth;
    bool                 m_complete;
};

#endif
