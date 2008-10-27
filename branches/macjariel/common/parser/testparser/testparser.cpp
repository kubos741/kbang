#include "testparser.h"
#include "mocksocket.h"
#include "../parser.h"


void TestParser::initTestCase()
{
    mp_clientSocket = new MockSocket(this);
    mp_serverSocket = new MockSocket(this);

    connect(mp_clientSocket, SIGNAL(networkOut(QByteArray)),
            mp_serverSocket, SLOT(networkIn(QByteArray)), Qt::QueuedConnection);
    connect(mp_serverSocket, SIGNAL(networkOut(QByteArray)),
            mp_clientSocket, SLOT(networkIn(QByteArray)), Qt::QueuedConnection);

    mp_clientParser = new Parser(this, mp_clientSocket);
    mp_serverParser = new Parser(this, mp_serverSocket);

    m_clientStreamInitialized = m_serverStreamInitialized = 0;
    connect(mp_clientParser, SIGNAL(streamInitialized()),
            this, SLOT(clientStreamInitialized()));
    connect(mp_serverParser, SIGNAL(streamInitialized()),
            this, SLOT(serverStreamInitialized()));
    mp_clientParser->initializeStream();
    QCoreApplication::processEvents();
    QCOMPARE(m_clientStreamInitialized, 1);
    QCOMPARE(m_serverStreamInitialized, 1);
}

void TestParser::serverinfoRequestRecieved()
{
    StructServerInfo x;
    x.name = m_serverName;
    x.description = m_serverDescription;
    mp_parser->resultServerInfo(x);
}



void TestParser::cleanupTestCase()
{
}

void TestParser::initializationTest()
{
    
    

}

QTEST_MAIN(TestParser)
