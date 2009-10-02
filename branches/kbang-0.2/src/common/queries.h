/***************************************************************************
 *   Copyright (C) 2008-2009 by MacJariel                                  *
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
#ifndef QUERIES_H
#define QUERIES_H

#include "gamestructs.h"
#include <QSharedPointer>

namespace Query {
    typedef QString Id;

    enum Type {
        InvalidType = 0,
        ServerInfoType,
        GameInfoType,
        GameInfoListType,
        CardsetInfoType
    };
}

class Parser;

class QueryGet
{
public:
    QueryGet(Query::Type type): m_type(type) {}

    inline Query::Id id() const {
        return m_id;
    }

    inline void setId(Query::Id id) {
        m_id = id;
    }

    inline Query::Type t() const {
        return m_type;
    }

private:
    Query::Id   m_id;
    Query::Type m_type;
};


class QueryServerInfoGet: public QueryGet
{
public:
    QueryServerInfoGet(): QueryGet(Query::ServerInfoType) {}
};

class QueryGameInfoGet: public QueryGet
{
public:
    QueryGameInfoGet(): QueryGet(Query::GameInfoType) {}
    GameId gameId;
};

class QueryGameInfoListGet: public QueryGet
{
public:
    QueryGameInfoListGet(): QueryGet(Query::GameInfoListType) {}
};

class QueryCardsetInfoGet: public QueryGet
{
public:
    QueryCardsetInfoGet(): QueryGet(Query::CardsetInfoType) {}
};

class QueryResultHandler
{
    friend class Parser;
public:
    QueryResultHandler();
    virtual ~QueryResultHandler();

    inline bool isActive() const {
        return (mp_parser != 0);
    }

    void cancel();

    virtual void resultReceived(const GameStructPtr&) = 0;
private:
    Parser* mp_parser;
};


#endif // QUERIES_H
