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

class Card;
typedef Card* CardPointer;


/**
 * @author MacJariel <echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil">
 */
class Card
{
public:

    typedef enum {
        CT_CHARACTER,
        CT_ROLE,
        CT_PLAYING
    } Type;

private:
    Card(const QString& id, const QString& name, Type type, const QString& imageSmall, const QString& image);
    Card(const Card&);
    const Card& operator=(const Card& other);

public:
    QString id() { return m_id; }
    QString name() { return m_name; }
    Type type() { return m_type; }

    QPixmap imageSmall();
    QPixmap image();

public: /* static */
    static void loadDefaultRuleset();
    static const CardPointer findCard(const QString& id);

private:
    QString m_id;
    QString m_name;
    Type    m_type;
    QPixmap m_imageSmall;
    QPixmap m_image;
    QString m_imageSmallFile;
    QString m_imageFile;

    static QMap<QString, CardPointer> sm_cards;

};

#endif
