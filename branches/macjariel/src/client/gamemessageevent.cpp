#include "gamemessageevent.h"
#include "game.h"
#include "card.h"

using namespace client;

GameMessageEvent::GameMessageEvent(Game* game, const GameMessage& gameMessage):
        GameEvent(game), m_gameMessage(gameMessage)
{
}

GameMessageEvent::~GameMessageEvent()
{
}

void GameMessageEvent::run()
{
    GameEvent::run();
    QString msg;
    QString playerName       = m_gameMessage.player ? mp_game->playerWidget(m_gameMessage.player)->name() : "";
    QString targetPlayerName = m_gameMessage.targetPlayer ? mp_game->playerWidget(m_gameMessage.targetPlayer)->name() : "";
    QString causedByName     = m_gameMessage.causedBy ? mp_game->playerWidget(m_gameMessage.causedBy)->name() : "";

    switch(m_gameMessage.type) {
    case GAMEMESSAGE_GAMESTARTED:
        mp_game->setGameState(GAMESTATE_PLAYING);
        msg = tr("The game has just started.");
        break;
    case GAMEMESSAGE_GAMEFINISHED:
        mp_game->setGameState(GAMESTATE_FINISHED);
        msg = tr("The game has finished.");
        break;
    case GAMEMESSAGE_PLAYERDRAWFROMDECK:
        msg = tr("<i>%1</i> drew %2 from the deck.").
                    arg(playerName).
                    arg(cardListToString(m_gameMessage.cards));
        break;
    case GAMEMESSAGE_PLAYERDRAWFROMGRAVEYARD:
        msg = tr("<i>%1</i> drew %2 from the discard pile.").
                    arg(playerName).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERDISCARDCARD:
        msg = tr("<i>%1</i> discarded %2.").
                    arg(playerName).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERPLAYCARD:
        if (m_gameMessage.targetCard.id) {
            msg = tr("<i>%1</i> played %2 on <i>%3</i>%4.").
                        arg(playerName).
                        arg(cardToString(m_gameMessage.card)).
                        arg(cardToString(m_gameMessage.targetCard)).
                        arg(m_gameMessage.targetPlayer ?
                                tr(" owned by <i>%1</i>").arg(targetPlayerName) : "");
        } else if (m_gameMessage.targetPlayer) {
            msg = tr("<i>%1</i> played %2 on <i>%3</i>.").
                        arg(playerName).
                        arg(cardToString(m_gameMessage.card)).
                        arg(targetPlayerName);
        } else {
            msg = tr("<i>%1</i> played %2.").
                        arg(playerName).
                        arg(cardToString(m_gameMessage.card));
        }
        break;
    case GAMEMESSAGE_PLAYERRESPONDWITHCARD:
        msg = tr("<i>%1</i> responded with %2.").
                    arg(playerName).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERPASS:
        msg = tr("<i>%1</i> did not reacted.").
                    arg(playerName);
        break;
    case GAMEMESSAGE_PLAYERPICKFROMSELECTION:
        msg = tr("<i>%1</i> took %2 from selection.").
                    arg(playerName).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERCHECKDECK:
        msg = tr("<i>%1</i> checked deck (because of %2) and ").
                    arg(playerName).
                    arg(cardToString(m_gameMessage.card));
        if (m_gameMessage.checkResult)
            msg += tr("was lucky.");
        else
            msg += tr("failed.");
        break;
    case GAMEMESSAGE_PLAYERSTEALCARD:
        msg = tr("<i>%1</i> took %2 from <i>%3</i>.").
                    arg(playerName).
                    arg(cardToString(m_gameMessage.card)).
                    arg(targetPlayerName);
        break;
    case GAMEMESSAGE_PLAYERCANCELCARD:
        msg = tr("<i>%1</i> canceled %2 from <i>%3</i>.").
                    arg(playerName).
                    arg(cardToString(m_gameMessage.card)).
                    arg(targetPlayerName);
        break;
    case GAMEMESSAGE_DECKREGENERATE:
        msg = tr("The deck ran out of cards. Cards from the discard pile were shuffled and are now used as new deck.");
        break;
    case GAMEMESSAGE_PLAYERDIED:
        msg = tr("<i>%1</i> passed away. R.I.P.").
                    arg(playerName);
        break;
    case GAMEMESSAGE_INVALID:
        break;
    }
    if (!msg.isEmpty())
        mp_game->sendLogMessage(msg);
    qDebug() << msg;
    GameEvent::finish();
}

QString GameMessageEvent::cardToString(const CardData& cardData, bool withRankAndSuit)
{
    if (cardData.id == 0) {
        return tr("<i>unknown card</i>");
    }
    const Card* card = Card::findPlayingCard(cardData.type);
    if (card == 0)
        return "";

    QString res = "<i>" + card->name() + "</i>";
    if (withRankAndSuit)
        res += " (" + Card::rankToString(cardData.rank) +
               Card::suitToColorString(cardData.suit) + ")";
    return res;
}

QString GameMessageEvent::cardListToString(QList<CardData> cardList)
{
    if (cardList.size() == 0)
        return "";
    QStringList cardStrings;
    foreach(const CardData& cardData, cardList) {
        cardStrings.append(cardToString(cardData));
    }
    QString result;
    QStringListIterator it(cardStrings);
    result = it.next();
    while(it.hasNext()) {
        QString next = it.next();
        if (it.hasNext()) {
            result = tr("%1, %2").arg(result).arg(next);
        } else {
            result = tr("%1 and %2").arg(result).arg(next);
        }
    }
    return result;
}
