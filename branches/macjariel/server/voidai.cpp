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
        qDebug() << QString("VoidAI (%1): REQUEST_DRAW");
            // Drawing two cards
            try {
                mp_playerCtrl->drawCard(2);
            } catch (BadPredrawException& e) {
                e.debug();
                QList<PlayingCard*> table = mp_playerCtrl->privatePlayerView().table();
                foreach(PlayingCard* c, table) {
                    try {
                        qDebug() << "Trying to play some card to bypass predraw exception";
                        mp_playerCtrl->playCard(c);
                        return;
                    } catch (GameException& e) {
                        qDebug() << "Predraw exception test exception:";
                        e.debug();
                    }
                }
            }
            break;
        case REQUEST_PLAY: {
            qDebug() << QString("VoidAI (%1): REQUEST_PLAY");
            // Try to use blue cards:
            foreach (PlayingCard* card, hand) {
                try {
                    switch(card->type()) {
                        case CARD_APPALOSSA:
                        case CARD_MUSTANG:
                        case CARD_VOLCANIC:
                        case CARD_SCHOFIELD:
                        case CARD_REMINGTON:
                        case CARD_CARABINE:
                        case CARD_WINCHESTER:
                        case CARD_DILIGENZA:
                        case CARD_WELLSFARGO:
                        case CARD_INDIANS:
                        case CARD_GATLING:
                        case CARD_GENERALSTORE:
                        case CARD_DYNAMITE:
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
                } catch (GameException& e)  {
                    qDebug() << "VoidAI: (checkpoint #1)";
                    e.debug();
                }
            }
            foreach (PlayingCard* card, hand) {
                try {
                    switch(card->type()) {
                        case CARD_BANG:
                        case CARD_DUEL:
                        {
                            QList<const PublicPlayerView*> players = mp_playerCtrl->publicGameView().publicPlayerList();
                            shuffleList(players);
                            foreach(const PublicPlayerView* p, players) {
                                try {
                                    mp_playerCtrl->playCard(card, p);
                                    return;
                                } catch (BadTargetPlayerException e) {
                                    qDebug() << "VoidAI: BadTargetPlayerException!";
                                } catch (OneBangPerTurnException e) {
                                    qDebug() << "VoidAI: One bang per turn!";
                                }
                            }
                        }
                    }
                } catch (GameException& e) {
                    qDebug() << "VoidAI: (checkpoint #2)";
                    e.debug();
                }
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
            if (mp_playerCtrl->publicGameView().selection().size() > 0) {
                QList<PlayingCard*> cards = mp_playerCtrl->publicGameView().selection();
                int index = rand() % cards.size();
                mp_playerCtrl->playCard(cards[index]);
                return;
            }
            qDebug() << QString("VoidAI (%1): REQUEST_RESPOND");
            QList<PlayingCard*> cards = mp_playerCtrl->privatePlayerView().hand();
            foreach (PlayingCard* c, cards) {
                try {
                    qDebug() << "Trying to play: " << PlayingCardTypeToString(c->type());
                    mp_playerCtrl->playCard(c);
                    return;
                } catch (BadCardException e) {
                    qDebug() << QString("VoidAI (%1): Respond: BadCardException").arg(m_id);
                } catch (BadPlayerException e) {
                    qDebug() << QString("VoidAI (%1): Respond: BadPlayerException").arg(m_id);
                } catch (GameException& e) {
                    qDebug("VoidAI");
                    e.debug();
                }
            }
            qDebug() << QString("VoidAI (%1): Trying to pass").arg(m_id);
            try {
                mp_playerCtrl->pass();
            } catch (GameException& e) {
                qDebug("Pass exception:");
                e.debug();
            }


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
