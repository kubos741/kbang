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
#ifndef CARD_H
#define CARD_H

#include <QMap>
#include <QString>
#include <QPixmap>

namespace client
{
class Card;
typedef Card* CardPointer;

/**
 * This class is a type of a card in Bang! game. The whole set of Card instances
 * is created during the start of the client. This class manages lifetime of its
 * objects by itself. It's only sufficient to create an instance with \b{new}
 * operator and you should never free any instances with \b{delete} operator by
 * yourself.
 *
 * Cards can be then looked up by their id string. The identification of common cards
 * is specified in KBang specification, so you can use card identification that you
 * got from server (more specifically the parser class) to get the card object.
 *
 * The Card class is almost exclusively used in the CardWidget class.
 * @see client::CardWidget
 *
 * \note In future it may be possible to use different card sets. This will be
 *       implemented by adding a kind of card-set-manager class that will manage
 *       creating the Card objects.
 *
 * \todo The class will use only one pixmap of the largest size. CardWidget can resize
 *       this pixmap on fly.
 *
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Card
{
public:

    typedef enum {
        CT_CHARACTER, /**< Character card (Susy Lafayete, etc.) */
        CT_ROLE,      /**< Role card (Sheriff, etc.) */
        CT_PLAYING,   /**< Playing card (Bang!, etc.) */
        CT_BACK       /**< Back of a card (back of a playing card, back of a character card (bullets), etc.) */
    } Type;

private:
    /**
     * Constructs a new Card according to given parameters.
     * @param id The unique card identificator.
     * @param name The localized card name (should be used with QObject::tr).
     * @param image The filename of the image, as used in QPixmap constructor.
     */
    Card(const QString& id, const QString& name, Type type, const QString& imageFileName);
    Card(const Card&);                    ///< Copy constructor is private.
    const Card& operator=(const Card&);   ///< Assignment operator is private.

public:
    inline QString id()    { return m_id;    } ///< Returns unique indentifier.
    inline QString name()  { return m_name;  } ///< Returns card name.
    inline Type    type()  { return m_type;  } ///< Returns card type. @see Card::Type
    inline QPixmap image() { return m_image; } ///< Returns image pixmap.

public: /* static */
    static void loadDefaultRuleset();  ///< Loads default ruleset. To be replaced with ruleset manager.
    static const CardPointer findCard(const QString& id); ///< Looks up a card by its identifier.

private:
    QString m_id;
    QString m_name;
    Type    m_type;
    QPixmap m_image;
    QString m_imageFileName;
    static QMap<QString, CardPointer> sm_cards;
};
}
#endif
