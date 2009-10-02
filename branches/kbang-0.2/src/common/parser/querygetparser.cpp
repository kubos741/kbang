#include "querygetparser.h"
#include "util.h"

/* static */
QString QueryGetParser::elementName(Query::Type type)
{
    switch(type) {
    case Query::ServerInfoType:     return "server-info";
        break;
    case Query::GameInfoType:       return "game-info";
        break;
    case Query::GameInfoListType:   return "game-info-list";
        break;
    case Query::CardsetInfoType:    return "cardset-info";
        break;
    }
    return "";
}


/* static */
void QueryGetParser::write(QXmlStreamWriter* w, const QueryGetPtr& d)
{
    w->writeStartElement("query");
    w->writeAttribute("type", "get");
    w->writeAttribute("id", d->id());

    switch (d->t()) {
    case Query::ServerInfoType: writeServerInfo(w, d.staticCast<QueryServerInfoGet>());
        break;
    case Query::GameInfoType: writeGameInfo(w, d.staticCast<QueryGameInfoGet>());
        break;
    case Query::GameInfoListType: writeGameInfoList(w, d.staticCast<QueryGameInfoListGet>());
        break;
    case Query::CardsetInfoType: writeCardsetInfo(w, d.staticCast<QueryCardsetInfoGet>());
        break;
    default:
        NOT_REACHED();
    }
    w->writeEndElement();
}

/* static */
QueryGetPtr QueryGetParser::read(XmlNode* n)
{
    QueryGetPtr res;
    if (n == 0 || n->name() != "query" || n->attribute("type") != "get") {
        return res;
    }
    XmlNode* ch = n->getFirstChild();
    if (!ch) {
        return res;
    }

    if (ch->name() == elementName(Query::ServerInfoType)) {
        res = readServerInfo(ch);
    } else if (ch->name() == elementName(Query::GameInfoType)) {
        res = readGameInfo(ch);
    } else if (ch->name() == elementName(Query::GameInfoListType)) {
        res = readGameInfoList(ch);
    } else if (ch->name() == elementName(Query::CardsetInfoType)) {
        res = readCardsetInfo(ch);
    }
    if (!res.isNull()) {
        res->setId(n->attribute("id"));
    }
    return res;
}


/* static */
void  QueryGetParser::writeServerInfo(QXmlStreamWriter* w,
                                      const QueryServerInfoGetPtr& d)
{
    w->writeEmptyElement(elementName(d->t()));
}

/* static */
QueryServerInfoGetPtr QueryGetParser::readServerInfo(XmlNode* node)
{
    Q_UNUSED(node);
    return QueryServerInfoGetPtr(new QueryServerInfoGet());
}


/* static */
void  QueryGetParser::writeGameInfo(QXmlStreamWriter* w,
                                    const QueryGameInfoGetPtr& d)
{
    w->writeStartElement(elementName(d->t()));
    w->writeAttribute("game-id", intToString(d->gameId));
    w->writeEndElement();
}

/* static */
QueryGameInfoGetPtr QueryGetParser::readGameInfo(XmlNode* node)
{
    QueryGameInfoGet* res = new QueryGameInfoGet();
    res->gameId = stringToInt(node->attribute("game-id"));
    return QueryGameInfoGetPtr(res);
}

/* static */
void  QueryGetParser::writeGameInfoList(QXmlStreamWriter* w,
                                        const QueryGameInfoListGetPtr& d)
{
    w->writeEmptyElement(elementName(d->t()));
}

/* static */
QueryGameInfoListGetPtr QueryGetParser::readGameInfoList(XmlNode* node)
{
    Q_UNUSED(node);
    return QueryGameInfoListGetPtr(new QueryGameInfoListGet());
}

/* static */
void QueryGetParser::writeCardsetInfo(QXmlStreamWriter* w,
                                      const QueryCardsetInfoGetPtr& d)
{
    w->writeEmptyElement(elementName(d->t()));
}

/* static */
QueryCardsetInfoGetPtr QueryGetParser::readCardsetInfo(XmlNode* node)
{
    Q_UNUSED(node);
    return QueryCardsetInfoGetPtr(new QueryCardsetInfoGet());
}

