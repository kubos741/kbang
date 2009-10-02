#include "queries.h"
#include "parser/parser.h"

QueryResultHandler::QueryResultHandler():
        mp_parser(0)
{
}

/* virtual */
QueryResultHandler::~QueryResultHandler()
{
    cancel();
}

void QueryResultHandler::cancel()
{
    if (mp_parser) {
        mp_parser->cancelQueryGet(this);
    }
    mp_parser = 0;
}
