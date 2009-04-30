#include "gamelogger.h"
#include "publicplayerview.h"

using namespace std;

GameLogger::GameLogger()
{
}

void GameLogger::onHandlerRegistered(PlayerCtrl* playerCtrl)
{
    mp_playerCtrl = playerCtrl;
}

void GameLogger::onHandlerUnregistered()
{
    mp_playerCtrl = 0;
}

void GameLogger::onGameStarted()
{
    qDebug() << "Creating log file.";
    Q_ASSERT(m_logFile.is_open() == 0);
    m_logFile.open("game.log", std::ios::out | std::ios::trunc);
}


void GameLogger::onPlayerDied(PublicPlayerView& p, PublicPlayerView* causedBy)
{
    m_logFile << "onPlayerDied (player=" << p.id() << ", causedBy=" << causedBy->id() << ")" << endl;
}

void GameLogger::onPlayerDrawFromDeck(PublicPlayerView& p, QList<const PlayingCard*>, bool)
{
    m_logFile << "onPlayerDrawFromDeck (player=" << p.id() << ", cards=todo)" << endl;
}

void GameLogger::onPlayerDiscardCard(PublicPlayerView& p, const PlayingCard*, PocketType)
{
    m_logFile << "onPlayerDiscardCard (player=" << p.id() << ")" << endl;
}

void GameLogger::onPlayerPlayCard(PublicPlayerView& p, const PlayingCard*)
{
    m_logFile << "onPlayerPlayCard (player=" << p.id() << ")" << endl;
}

void GameLogger::onPlayerPlayCard(PublicPlayerView& p, const PlayingCard*, PublicPlayerView&)
{
    m_logFile << "onPlayerPlayCard (player=" << p.id() << ")" << endl;
}

void GameLogger::onPlayerPlayCard(PublicPlayerView& p, const PlayingCard*, const PlayingCard*)
{
    m_logFile << "onPlayerPlayCard (player=" << p.id() << ")" << endl;
}

void GameLogger::onPlayerPlayCardOnTable(PublicPlayerView& p, const PlayingCard*, PublicPlayerView&)
{
    m_logFile << "onPlayerPlayCard (player=" << p.id() << ")" << endl;
}

void GameLogger::onPassTableCard(PublicPlayerView& p, const PlayingCard*, PublicPlayerView&)
{
    m_logFile << "onPlayerPlayCardOnTable (player=" << p.id() << ")" << endl;
}

void GameLogger::onPlayerPass(PublicPlayerView& p)
{
    m_logFile << "onPlayerPass (player=" << p.id() << ")" << endl;
}

void GameLogger::onDrawIntoSelection(QList<const PlayingCard*>)
{
    m_logFile << "onDrawIntoSelection ()" << endl;
}

void GameLogger::onPlayerPickFromSelection(PublicPlayerView& p, const PlayingCard*)
{
    m_logFile << "onPlayerPickFromSelection (player=" << p.id() << ")" << endl;
}

void GameLogger::onPlayerCheckDeck(PublicPlayerView& p, const PlayingCard*, const PlayingCard*, bool)
{
    m_logFile << "onPlayerCheckDeck (player=" << p.id() << ")" << endl;
}

void GameLogger::onPlayerStealCard(PublicPlayerView& p, PublicPlayerView&, PocketType, const PlayingCard*)
{
    m_logFile << "onPlayerStealCard(player=" << p.id() << ")" << endl;
}

void GameLogger::onPlayerCancelCard(PublicPlayerView& p, PocketType, const PlayingCard*, PublicPlayerView*)
{
    m_logFile << "onPlayerCancelCard (player=" << p.id() << ")" << endl;
}

void GameLogger::onGameContextChange(const GameContextData&)
{
    m_logFile << "onGameContextChange ()" << endl;
}

void GameLogger::onLifePointsChange(PublicPlayerView& p, int lifePoints, PublicPlayerView*)
{
    m_logFile << "onLifePointsChange (player=" << p.id() << ", lifePoints=" << lifePoints << ")" << endl;
}

void GameLogger::onDeckRegenerate()
{
    m_logFile << "onDeckRegenerate()" << endl;
}
