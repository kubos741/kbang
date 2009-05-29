#include "voidai.h"
#include "playerctrl.h"
#include "publicgameview.h"
#include "privateplayerview.h"
#include "cards.h"
#include "util.h"

#include <QDebug>
#include <QTimer>
#include <QApplication>
#include <cstdlib>

int VoidAI::sm_playerCounter = 0;

int minActionDelay = 200;
int maxActionDelay = 1500;


VoidAI::VoidAI(QObject* parent):
        QObject(parent),
        m_id(++sm_playerCounter)
{
    //moveToThread(QApplication::instance()->thread());
}

CreatePlayerData VoidAI::createPlayerData() const
{
    CreatePlayerData res;
    res.name = QString("VoidAI #%1").arg(m_id);
    res.password = "void";
    return res;
}

void VoidAI::onHandlerRegistered(const PublicGameView* publicGameView, PlayerCtrl* playerCtrl)
{
    mp_playerCtrl = playerCtrl;
}

void VoidAI::onGameStarted()
{
    foreach(PublicPlayerView* player, mp_playerCtrl->publicGameView().publicPlayerList()) {
        m_score[player] = 0;
        if (player->isSheriff()) {
            m_score[player] = 5;
        }
    }
}
void VoidAI::onPlayerPlayCard(PublicPlayerView& player, const PlayingCard* card, PublicPlayerView& targetPlayer)
{
    qreal coef = 0;
    switch(card->type()) {
        case CARD_BANG:
        case CARD_DUEL:
        case CARD_PANIC:
            coef = 0.8;
            break;
        case CARD_CATBALOU:
        case CARD_DUEL:
            coef = 1;
            break;
        default:
            break;
    }
    if (coef == 0) return;
    m_score[&player] -= (int)(m_score[&targetPlayer] * coef);
}

void VoidAI::onPlayerPlayCard(PublicPlayerView& player, const PlayingCard* card, const PlayingCard* targetCard, PublicPlayerView* targetPlayer)
{
    qreal coef = 0;
    switch(card->type()) {
        case CARD_PANIC:
            coef = 0.8;
            break;
        case CARD_CATBALOU:
            coef = 1;
            break;
        default:
            break;
    }
    if (coef == 0) return;
    if (targetCard && targetCard->pocket() == POCKET_TABLE && targetCard->type() == CARD_JAIL) {
        m_score[&player] += (int)(m_score[&targetPlayer] * coef);
    } else {
        m_score[&player] -= (int)(m_score[&targetPlayer] * coef);
    }
}

void VoidAI::onPlayerPlayCardOnTable(PublicPlayerView& player, const PlayingCard* card, PublicPlayerView& targetPlayer)
{
    if (card->type() == CARD_JAIL) {
        m_score[&player] -= (int)(m_score[&targetPlayer] * 0.8);
    }
}

void VoidAI::onActionRequest(ActionRequestType requestType)
{
    m_requestType = requestType;
    QTimer::singleShot(200, this, SLOT(requestWithAction()));
}

void VoidAI::requestWithAction()
{
    if (mp_playerCtrl->publicGameView().gameContextData().requestedPlayerId != mp_playerCtrl->privatePlayerView().id()) {
        qDebug() << QString("VoidAI (%1): Not requested!").arg(m_id);
        return;
    }

    switch(m_requestType) {
        case REQUEST_DRAW:
            onRequestDraw();
            break;
        case REQUEST_PLAY:
            onRequestPlay();
            break;
        case REQUEST_RESPOND:
            onRequestResponse();
            break;
        case REQUEST_DISCARD:
            onRequestDiscard();
            break;
    }
}


void VoidAI::onRequestDraw()
{
    ///@todo AI does not use character abilities

    try {
        mp_playerCtrl->draw();
    } catch (BadPredrawException& e) {
        PlayingCard* jail = mp_playerCtrl->privatePlayerView().cardFromTable(CARD_JAIL);
        PlayingCard* dynamite = mp_playerCtrl->privatePlayerView().cardFromTable(CARD_JAIL);
        try {
            if (dynamite) {
                mp_playerCtrl->playCard(dynamite);
                return;
            }
        } catch (GameException& e) {
        }

        try {
            if (jail) {
                mp_playerCtrl->playCard(jail);
                return;
            }
        } catch (GameException& e) {
        }
        qWarning() << QString("VoidAI (%1): Unknown predraw.").arg(m_id);
    }
}

void VoidAI::onRequestPlay()
{
    bool keepMissed = 0;
    bool keepBang = 0;

    if (playCardTakers()) return;

    if (playAggresiveCards()) return;

    if (playAlwaysPlayables()) return;

    try {
        mp_playerCtrl->finishTurn();
        return;
    } catch (TooManyCardsInHandException e) {
        onRequestDiscard();
    }
}

void VoidAI::onRequestResponse()
{
    if (mp_playerCtrl->publicGameView().selection().size() > 0) {
        ///@todo AI selects cards from selection randomly
        QList<PlayingCard*> cards = mp_playerCtrl->publicGameView().selection();
        int index = qrand() % cards.size();
        try {
            mp_playerCtrl->playCard(cards[index]);
            return;
        } catch(GameException& e) {
            qDebug() << QString("VoidAI (%1): Respond - selection: GameException").arg(m_id);
            e.debug();
        }
    }

    if (randomBool(0.9)) {
        PlayingCard* barrel = mp_playerCtrl->privatePlayerView().cardFromTable(CARD_BARREL);
        if (barrel) {
            try {
                mp_playerCtrl->playCard(barrel);
                return;
            } catch (GameException&) {
            }
        }
    }

    foreach (PlayingCard* card, mp_playerCtrl->privatePlayerView().hand()) {
        try {
            mp_playerCtrl->playCard(c);
            return;
        } catch (GameException& e) {
        }
    }

    try {
        mp_playerCtrl->pass();
    } catch (GameException& e) {
        qDebug() << QString("VoidAI (%1): onRequestResponse:").arg(m_id);
        e.debug();
    }
}

void VoidAI::onRequestDiscard()
{
    try {
        int discard_level = 0;
        foreach (PlayingCard* card, mp_playerCtrl->privatePlayerView().hand()) {
            switch (card->type()) {
            case CARD_BANG:
            case CARD_MISSED:
                if (discard_level < 2) continue;
                mp_playerCtrl->discardCard(card);
                return;
            default:
                mp_playerCtrl->discardCard(card);
                return;
            }
            discard_level++;
        }
    } catch (GameException& e) {
        qDebug() << QString("VoidAI (%1): onRequestDiscard:").arg(m_id);
        e.debug();
    }
}

bool VoidAI::playCardTakers()
{
    if (randomBool(0.05)) return 0;
    foreach (PlayingCard* card, hand) {
        try {
            QList<PublicPlayerView*> target_players;
            switch(card->type()) {
            case CARD_PANIC:
                target_players = mp_playerCtrl->publicGameView().neighbors(mp_playerCtrl->privatePlayerView(), 1);
                break;
            case CARD_CATBALOU:
                target_players = mp_playerCtrl->publicGameView().publicPlayerList();
                break;
            default:
                break;
            }
            if (targetPlayers.size() > 0) {
                QList<PublicPlayerView*> friend_players = friendPlayer(target_players);
                QList<PublicPlayerView*> takers_targets = takersTargets(target_players);

                if (friend_players.size() > 0) {
                    foreach (PublicPlayerView* friend_player, friend_players) {
                        PlayingCard jail = friend_player.cardFromTable(CARD_JAIL);
                        if (jail) {
                            mp_playerCtrl->playCard(card, jail);
                            return 1;
                        }
                    }
                }

                if (takers_targets.size() > 0) {
                    foreach (PublicPlayerView* takers_target, takers_targets) {
                        if (takers_target->handSize() > 0 || randomBool(0.5)) {
                            mp_playerCtrl->playCard(card, takers_target);
                            return 1;
                        } else if (takers_target->tableSize() > 0) {
                            mp_playerCtrl->playCard(card, takers_target->cardFromTable());
                            return 1;
                        }
                    }
                }
            }
        } catch (GameException& e)  {
            //e.debug();
        }
    }
    return 0;
}

bool VoidAI::playAlwaysPlayables()
{
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
            case CARD_BARREL:
                mp_playerCtrl->playCard(card);
                return 1;

            case CARD_BEER:
                if (mp_playerCtrl->privatePlayerView().lifePoints() !=
                        mp_playerCtrl->privatePlayerView().maxLifePoints()) {
                    mp_playerCtrl->playCard(card);
                    return 1;
                }
                break;

            case CARD_DYNAMITE:
                {
                    bool playDynamite = isGoodGuy() ^ randomBool(0.9);
                    if (playDynamite) {
                        mp_playerCtrl->playCard(card);
                        return 1;
                    }
                }
                break;

            case CARD_GENERALSTORE:
                if (randomBool(0.9)) {
                    mp_playerCtrl->playCard(card);
                    return 1;
                }
                break;

            default:
                break;

            }
        } catch (GameException& e)  {
            //e.debug();
        }
    }
    return 0;
}

bool VoidAI::playAggresiveCards()
{
    int bangs_in_hand = mp_playerCtrl->privatePlayerView().handSize(CARD_BANG);
    int life_points = mp_playerCtrl->privatePlayerView().lifePoints();
    foreach (PlayingCard* card, hand) {
        try {
            QList<PublicPlayerView*> enemy_players = enemyPlayers();
            switch(card->type()) {
            case CARD_BANG:
                {
                    if ((mp_playerCtrl->privatePlayerView().handSize(CARD_BANG) < 2 &&
                        mp_playerCtrl->privatePlayerView().lifePoints() < 2) ^ randomBool(0.1)) {
                        break;
                    }

                    foreach (PublicPlayerView* bang_target, enemy_players) {
                        try {
                            mp_playerCtrl->playCard(card, bang_target);
                            return 1;
                        } catch (PlayerOutOfRangeException&) {
                        }
                    }
                }
                break;
            case CARD_DUEL:
                {
                    bool only_secure_duel = 0;

                    if (bangs_in_hand == 0 && randomBool(0.8) || life_points == 1) {
                        only_secure_duel = 1;
                    }

                    foreach (PublicPlayerView* duel_target, enemy_players) {
                        if (onlySecureDuel && duel_target->handSize() > bangs_in_hand)
                            continue;
                        mp_playerCtrl->playCard(card, duel_target);
                        return 1;
                    }
                }
                break;
            case CARD_JAIL:
                {
                    foreach (PublicPlayerView* jail_target, enemy_players) {
                        try {
                            mp_playerCtrl->playCard(card, jail_target);
                            return 1;
                        } catch (GameException&) {
                        }
                    }
                }
                break;
            case CARD_INDIANS:
            case CARD_GATLING:
                if (randomBool(0.9)) {
                    mp_playerCtrl->playCard(card);
                    return 1;
                }
                break;
            default:
                break;
            }
        } catch (GameException& e)  {
            //e.debug();
        }
    }
    return 0;
}

bool VoidAI::isRenegade() const
{
    return mp_playerCtrl->privatePlayerView().role() == ROLE_RENEGADE;
}

bool VoidAI::isOutlaw() const
{
    return mp_playerCtrl->privatePlayerView().role() == ROLE_OUTLAW;
}

bool VoidAI::isGoodGuy() const
{
    return ( mp_playerCtrl->privatePlayerView().role() == ROLE_SHERIFF ||
             mp_playerCtrl->privatePlayerView().role() == ROLE_DEPUTY );
}

QList<PublicPlayerView*> VoidAI::enemyPlayers() const
{
    QList<PublicPlayerView*> result;
    switch(mp_playerCtrl->privatePlayerView().role()) {
    case ROLE_SHERIFF:


    }

}


    PublicPlayerView* takersTarget(QList<PublicPlayerView*>) const;
    QList<PublicPlayerView*> friendPlayers(QList<PublicPlayerView*>) const;



QList<PublicPlayerView*> VoidAI::playersToTreshold(int treshold, bool isAscending)
{
    QMap<int, PublicPlayerView*> map;
    foreach (PublicPlayerView* player, mp_playerCtrl->publicGameView().publicPlayerList()) {
        if (!player->isAlive()) continue;
        //if (isAscending && m_score[player]
        //map.insert(m_score[player], player);
        // CONTINUE HERE
    }
    return map.values();
}
