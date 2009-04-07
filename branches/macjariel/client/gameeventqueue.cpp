#include <QTimer>
#include "gameeventqueue.h"
#include "gameevent.h"


using namespace client;

GameEventQueue::GameEventQueue(QObject* parent):
        QObject(parent)
{
}

void GameEventQueue::add(GameEvent* gameEvent)
{
    if (m_queue.isEmpty()) {
        m_queue.enqueue(gameEvent);
        runGameEvent();
    } else {
        m_queue.enqueue(gameEvent);
    }
}

void GameEventQueue::runGameEvent()
{
    GameEvent* gameEvent = m_queue.head();
    Q_ASSERT(!gameEvent->isRunning());
    if (gameEvent->isReadyRun()) {
        connect(gameEvent, SIGNAL(finished(GameEvent*)),
                this,      SLOT(onGameEventFinished(GameEvent*)));
        gameEvent->run();
    } else {
        QTimer::singleShot(10, this, SLOT(runGameEvent()));
    }
}

void GameEventQueue::onGameEventFinished(GameEvent* gameEvent)
{
    Q_ASSERT(gameEvent == m_queue.head());
    m_queue.dequeue()->deleteLater();
    if (!m_queue.isEmpty())
        runGameEvent();
    else
        qDebug("Event queue is empty!");
}
