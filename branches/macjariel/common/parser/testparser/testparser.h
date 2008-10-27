#include <QtTest/QtTest>

class Parser;
class MockSocket;


class TestParser: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();


    void initializationTest();


private:
    MockSocket* mp_clientSocket;
    MockSocket* mp_serverSocket;

    Parser* mp_clientParser;
    Parser* mp_serverParser;

public slots:
    void clientStreamInitialized()
    {
        m_clientStreamInitialized++;
    }
    void serverStreamInitialized()
    {
        m_serverStreamInitialized++;
    }
    void serverinfoRequestRecieved();

private:
    int m_clientStreamInitialized, m_serverStreamInitialized;
    QString m_serverName, m_serverDescription;
};
