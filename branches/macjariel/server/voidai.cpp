#include "voidai.h"
#include "playerctrl.h"
#include "publicgameview.h"
#include "privateplayerview.h"
#include "cards.h"
#include "util.h"

#include <QDebug>
#include <QTimer>
#include <QApplication>

int VoidAI::sm_playerCounter = 0;

VoidAI::VoidAI(int gameId):
        m_id(++sm_playerCounter)
{
    moveToThread(QApplication::instance()->thread());
    StructPlayer structPlayer;
    structPlayer.name = QString("VoidAI #%1").arg(m_id);
    PlayerCtrl::joinGame(gameId, structPlayer, this);

}

void VoidAI::onPlayerInit(PlayerCtrl* playerCtrl)
{
    mp_playerCtrl = playerCtrl;
}

void VoidAI::onActionRequest(ActionRequestType requestType)
{
    m_requestType = requestType;
    QTimer::singleShot(1, this, SLOT(requestWithAction()));
}

void VoidAI::requestWithAction()
{
    qDebug() << QString("VoidAI (%1): onActionRequest(%2)").arg(m_id).arg(m_requestType);
    if (mp_playerCtrl->publicGameView().gameContextData().requestedPlayerId != mp_playerCtrl->privatePlayerView().id()) {
        QString("VoidAI (%1): Not requested!");
        return;
    }
    QList<PlayingCard*> hand = mp_playerCtrl->privatePlayerView().hand();
    switch(m_requestType) {
        case REQUEST_DRAW:
            // Drawing two cards
            mp_playerCtrl->drawCard(2);
            break;
        case REQUEST_PLAY: {

            // Try to use blue cards:
            foreach (PlayingCard* card, hand) {
                try {
                    switch(card->type()) {
                        case CARD_APPALOSSA:
                        //case CARD_MUSTANG:
                        case CARD_VOLCANIC:
                        case CARD_SCHOFIELD:
                        case CARD_REMINGTON:
                        case CARD_CARABINE:
                        case CARD_WINCHESTER:
                            mp_playerCtrl->playCard(card);
                            return;
                        case CARD_BEER:
                            if (mp_playerCtrl->privatePlayerView().lifePoints() !=
                                    mp_playerCtrl->privatePlayerView().maxLifePoints()) {
                                mp_playerCtrl->playCard(card);
                                return;
                            }
                        default:
                            break;
                    }
                } catch (BadGameStateException e)  {
                }
            }

            // If have bang, tries to play it
            try {

                foreach (PlayingCard* c, hand) {
                    CardBang* bang = qobject_cast<CardBang*>(c);
                    if (bang == 0) continue;

                    QList<const PublicPlayerView*> players = mp_playerCtrl->publicGameView().neighbors(
                                &mp_playerCtrl->privatePlayerView(), 1);
                    int size = players.size();
                    qDebug() << "Selecting from " << size << " targets!";
                    if (size > 0) {
                        int targetId = rand() % size;
                        const PublicPlayerView* p = players[targetId];
                        mp_playerCtrl->playCard(bang, p);
                        return;
                    }
                }
            } catch (OneBangPerTurnException e) {
                qDebug() << "VoidAI: One bang per turn!";
            } catch (BadPlayerException e) {
                qDebug() << "VoidAI: Bad player exception!";
            }

            // Finish turn or discard random card
            try {
                mp_playerCtrl->finishTurn();
                return;
            } catch (TooManyCardsInHandException e) {
                qDebug() << QString("VoidAI (%1): discarding card").arg(m_id);
                PlayingCard* card = mp_playerCtrl->privatePlayerView().hand().first();
                mp_playerCtrl->discardCard(card);
                return;
            }
            break;
        }
        case REQUEST_RESPOND: {
            QList<PlayingCard*> cards = mp_playerCtrl->privatePlayerView().hand();
            foreach (PlayingCard* c, cards) {
                try {
                    CardMissed* missed = qobject_cast<CardMissed*>(c);
                    if (missed == 0) continue;
                    qDebug() << QString("VoidAI (%1): Trying to play Missed").arg(m_id);
                    mp_playerCtrl->playCard(missed);
                    return;
                } catch (BadCardException e) {
                    qDebug() << QString("VoidAI (%1): BadCardException (missed)").arg(m_id);
                }
            }
            qDebug() << QString("VoidAI (%1): Trying to pass").arg(m_id);
            mp_playerCtrl->pass();


            return;
        }
        case REQUEST_DISCARD:
            try {
                qDebug() << QString("VoidAI (%1): discarding card").arg(m_id);
                PlayingCard* card = mp_playerCtrl->privatePlayerView().hand().first();
                qDebug() << QString("VoidAI (%1): cards in hand: %2").arg(m_id).arg(
                        mp_playerCtrl->privatePlayerView().hand().size());
                mp_playerCtrl->discardCard(card);
            } catch (BadGameStateException e) {
                qDebug() << QString("VoidAI (%1): BadGameStateException").arg(m_id);
            }
            break;
    }
}
