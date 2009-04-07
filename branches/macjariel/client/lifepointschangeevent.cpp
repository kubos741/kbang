#include "lifepointschangeevent.h"
#include "game.h"
#include "playercharacterwidget.h"

using namespace client;

LifePointsChangeEvent::LifePointsChangeEvent(Game* game, int playerId, int lifePoints):
        GameEvent(game),
        m_playerId(playerId),
        m_lifePoints(lifePoints)

{
}

LifePointsChangeEvent::~LifePointsChangeEvent()
{
}

void LifePointsChangeEvent::run()
{
    qDebug() << "LifePointsChangeEvent::run()";
    if (m_lifePoints < 0 || m_lifePoints > 5 ||
        mp_game->playerWidget(m_playerId)->playerCharacterWidget()->lifePoints() == m_lifePoints) {
        qDebug() << "invalid lifepoint change";
        QTimer::singleShot(10, this, SLOT(finish()));
        return;
    }
    connect(mp_game->playerWidget(m_playerId)->playerCharacterWidget(), SIGNAL(animationFinished()),
            this,                                                       SLOT(finish()));
    mp_game->playerWidget(m_playerId)->playerCharacterWidget()->setLifePoints(m_lifePoints);
}
