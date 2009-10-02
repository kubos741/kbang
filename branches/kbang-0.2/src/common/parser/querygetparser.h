#ifndef QUERYGETPARSER_H
#define QUERYGETPARSER_H

#include "queries.h"
#include <QXmlStreamWriter>
#include "parser/xmlnode.h"

class QueryGetParser
{
public:
    static QString elementName(Query::Type);

    static void write(QXmlStreamWriter*, const QueryGetPtr&);
    static QueryGetPtr read(XmlNode*);

    static void writeServerInfo(QXmlStreamWriter*, const QueryServerInfoGetPtr&);
    static QueryServerInfoGetPtr readServerInfo(XmlNode*);

    static void writeGameInfo(QXmlStreamWriter*, const QueryGameInfoGetPtr&);
    static QueryGameInfoGetPtr readGameInfo(XmlNode*);

    static void writeGameInfoList(QXmlStreamWriter*, const QueryGameInfoListGetPtr&);
    static QueryGameInfoListGetPtr readGameInfoList(XmlNode*);

    static void writeCardsetInfo(QXmlStreamWriter*, const QueryCardsetInfoGetPtr&);
    static QueryCardsetInfoGetPtr readCardsetInfo(XmlNode*);
};

#endif // QUERYGETPARSER_H
