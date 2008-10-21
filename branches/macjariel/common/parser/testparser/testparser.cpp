#include "testparser.h"
#include "mocksocket.h"
#include "../parser.h"


void TestParser::initTestCase()
{
    mp_clientSocket = new MockSocket(this);
    mp_serverSocket = new MockSocket(this);

    connect(mp_clientSocket, SIGNAL(networkOut(QByteArray)),
            mp_serverSocket, SLOT(networkIn(QByteArray)));
    connect(mp_serverSocket, SIGNAL(networkOut(QByteArray)),
            mp_clientSocket, SLOT(networkIn(QByteArray)));

    mp_clientParser = new Parser(this, mp_clientSocket);
    mp_serverParser = new Parser(this, mp_serverSocket);

    mp_clientParser->initializeStream();


}

void TestParser::cleanupTestCase()
{
}

QTEST_MAIN(TestParser)
