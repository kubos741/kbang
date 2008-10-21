#include <QtTest/QtTest>

class Parser;
class MockSocket;


class TestParser: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();




private:
    MockSocket* mp_clientSocket;
    MockSocket* mp_serverSocket;

    Parser* mp_clientParser;
    Parser* mp_serverParser;
};
