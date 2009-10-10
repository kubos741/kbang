#include "actionparser.h"
#include "gamestructparser.h"
#include "simpletypeparser.h"
#include "util.h"

/*[[[cog
import cog
from actiondefs import *
]]]
[[[end]]]*/


/* static */
QString ActionParser::elementName(ActionData::Type type)
{
    switch (type) {
    /*[[[cog
    for a in Actions:
        cog.outl("case ActionData::%(actionType)-16s: return %(elemName)s;" % a)
        cog.outl("    break;")
    ]]]*/
    case ActionData::ChatMessageType : return "chat-message";
        break;
    case ActionData::CreateGameType  : return "create-game";
        break;
    case ActionData::DiscardType     : return "discard";
        break;
    case ActionData::DrawCardType    : return "draw-card";
        break;
    case ActionData::EndTurnType     : return "end-turn";
        break;
    case ActionData::JoinGameType    : return "join-game";
        break;
    case ActionData::LeaveGameType   : return "leave-game";
        break;
    case ActionData::PassType        : return "pass";
        break;
    case ActionData::PlayCardType    : return "play-card";
        break;
    case ActionData::StartGameType   : return "start-game";
        break;
    case ActionData::UseAbilityType  : return "use-ability";
        break;
    //[[[end]]]
    default:
        NOT_REACHED();
        break;
    }
}

/* static */
void ActionParser::write(QXmlStreamWriter* w, const ActionDataPtr& d)
{
    w->writeStartElement("action");
    switch (d->t()) {
    /*[[[cog
    for a in Actions:
        cog.outl("case ActionData::%(actionType)s:" % a)
        cog.outl("    write%(actionName)s(w, d.staticCast<%(structName)s>());" % a)
        cog.outl("    break;")
    ]]]*/
    case ActionData::ChatMessageType:
        writeChatMessage(w, d.staticCast<ActionChatMessageData>());
        break;
    case ActionData::CreateGameType:
        writeCreateGame(w, d.staticCast<ActionCreateGameData>());
        break;
    case ActionData::DiscardType:
        writeDiscard(w, d.staticCast<ActionDiscardData>());
        break;
    case ActionData::DrawCardType:
        writeDrawCard(w, d.staticCast<ActionDrawCardData>());
        break;
    case ActionData::EndTurnType:
        writeEndTurn(w, d.staticCast<ActionEndTurnData>());
        break;
    case ActionData::JoinGameType:
        writeJoinGame(w, d.staticCast<ActionJoinGameData>());
        break;
    case ActionData::LeaveGameType:
        writeLeaveGame(w, d.staticCast<ActionLeaveGameData>());
        break;
    case ActionData::PassType:
        writePass(w, d.staticCast<ActionPassData>());
        break;
    case ActionData::PlayCardType:
        writePlayCard(w, d.staticCast<ActionPlayCardData>());
        break;
    case ActionData::StartGameType:
        writeStartGame(w, d.staticCast<ActionStartGameData>());
        break;
    case ActionData::UseAbilityType:
        writeUseAbility(w, d.staticCast<ActionUseAbilityData>());
        break;
    //[[[end]]]
    default:
        NOT_REACHED();
    }
    w->writeEndElement();
}

/* static */
ActionDataPtr ActionParser::read(XmlNode* n)
{
    ActionDataPtr res;
    if (n == 0) {
        return res;
    /*[[[cog
    for a in Actions:
        cog.outl("} else if (n->name() == %(elemName)s) {" % a)
        cog.outl("    res = read%(actionName)s(n);" % a)
    cog.outl("}");
    ]]]*/
    } else if (n->name() == "chat-message") {
        res = readChatMessage(n);
    } else if (n->name() == "create-game") {
        res = readCreateGame(n);
    } else if (n->name() == "discard") {
        res = readDiscard(n);
    } else if (n->name() == "draw-card") {
        res = readDrawCard(n);
    } else if (n->name() == "end-turn") {
        res = readEndTurn(n);
    } else if (n->name() == "join-game") {
        res = readJoinGame(n);
    } else if (n->name() == "leave-game") {
        res = readLeaveGame(n);
    } else if (n->name() == "pass") {
        res = readPass(n);
    } else if (n->name() == "play-card") {
        res = readPlayCard(n);
    } else if (n->name() == "start-game") {
        res = readStartGame(n);
    } else if (n->name() == "use-ability") {
        res = readUseAbility(n);
    }
    //[[[end]]]
    return res;
}



/*[[[cog
for a in Actions:
    cog.outl("void ActionParser::write%(actionName)s(QXmlStreamWriter* w, const %(structName)sPtr& d)" % a)
    cog.outl(a.genWriter("w", "d", True))

    cog.outl("%(structName)sPtr ActionParser::read%(actionName)s(XmlNode* n)" % a)
    cog.outl("{");
    cog.outl("    Q_ASSERT(n->name() == %(elemName)s);" % a)
    cog.outl("    %(structName)sPtr res(new %(structName)s());" % a)

    for s in a["simpleMembers"]:
        cog.outl("    fromString(n->attribute(%(elemName)s), res->%(name)s);" % s)

    if (len(a["complexMembers"]) > 0):
        cog.outl("    foreach (XmlNode* ch, n->getChildren()) {")
        for s in a["complexMembers"]:
            cog.outl("        if (ch->name() == %(elemName)s) {" % s)
            cog.outl("            GameStructParser::read(ch, res->%(name)s);" % s)
            cog.outl("            continue;")
            cog.outl("        }")
        cog.outl("    }")
    cog.outl("    return res;")
    cog.outl("}\n")
]]]*/
void ActionParser::writeChatMessage(QXmlStreamWriter* w, const ActionChatMessageDataPtr& d)
{
    w->writeStartElement("chat-message");
    w->writeAttribute("message", toString(d->message));
    w->writeEndElement();
}

ActionChatMessageDataPtr ActionParser::readChatMessage(XmlNode* n)
{
    Q_ASSERT(n->name() == "chat-message");
    ActionChatMessageDataPtr res(new ActionChatMessageData());
    fromString(n->attribute("message"), res->message);
    return res;
}

void ActionParser::writeCreateGame(QXmlStreamWriter* w, const ActionCreateGameDataPtr& d)
{
    w->writeStartElement("create-game");
    GameStructParser::write(w, d->createGameData, "game-data");
    GameStructParser::write(w, d->createPlayerData, "player-data");
    w->writeEndElement();
}

ActionCreateGameDataPtr ActionParser::readCreateGame(XmlNode* n)
{
    Q_ASSERT(n->name() == "create-game");
    ActionCreateGameDataPtr res(new ActionCreateGameData());
    foreach (XmlNode* ch, n->getChildren()) {
        if (ch->name() == "game-data") {
            GameStructParser::read(ch, res->createGameData);
            continue;
        }
        if (ch->name() == "player-data") {
            GameStructParser::read(ch, res->createPlayerData);
            continue;
        }
    }
    return res;
}

void ActionParser::writeDiscard(QXmlStreamWriter* w, const ActionDiscardDataPtr& d)
{
    w->writeStartElement("discard");
    w->writeAttribute("card-id", toString(d->cardId));
    w->writeEndElement();
}

ActionDiscardDataPtr ActionParser::readDiscard(XmlNode* n)
{
    Q_ASSERT(n->name() == "discard");
    ActionDiscardDataPtr res(new ActionDiscardData());
    fromString(n->attribute("card-id"), res->cardId);
    return res;
}

void ActionParser::writeDrawCard(QXmlStreamWriter* w, const ActionDrawCardDataPtr& d)
{
    w->writeStartElement("draw-card");
    w->writeEndElement();
}

ActionDrawCardDataPtr ActionParser::readDrawCard(XmlNode* n)
{
    Q_ASSERT(n->name() == "draw-card");
    ActionDrawCardDataPtr res(new ActionDrawCardData());
    return res;
}

void ActionParser::writeEndTurn(QXmlStreamWriter* w, const ActionEndTurnDataPtr& d)
{
    w->writeStartElement("end-turn");
    w->writeEndElement();
}

ActionEndTurnDataPtr ActionParser::readEndTurn(XmlNode* n)
{
    Q_ASSERT(n->name() == "end-turn");
    ActionEndTurnDataPtr res(new ActionEndTurnData());
    return res;
}

void ActionParser::writeJoinGame(QXmlStreamWriter* w, const ActionJoinGameDataPtr& d)
{
    w->writeStartElement("join-game");
    w->writeAttribute("game-id", toString(d->gameId));
    w->writeAttribute("player-id", toString(d->playerId));
    w->writeAttribute("game-password", toString(d->gamePassword));
    w->writeAttribute("game-participant-type", toString(d->gameParticipantType));
    GameStructParser::write(w, d->createPlayerData, "player-data");
    w->writeEndElement();
}

ActionJoinGameDataPtr ActionParser::readJoinGame(XmlNode* n)
{
    Q_ASSERT(n->name() == "join-game");
    ActionJoinGameDataPtr res(new ActionJoinGameData());
    fromString(n->attribute("game-id"), res->gameId);
    fromString(n->attribute("player-id"), res->playerId);
    fromString(n->attribute("game-password"), res->gamePassword);
    fromString(n->attribute("game-participant-type"), res->gameParticipantType);
    foreach (XmlNode* ch, n->getChildren()) {
        if (ch->name() == "player-data") {
            GameStructParser::read(ch, res->createPlayerData);
            continue;
        }
    }
    return res;
}

void ActionParser::writeLeaveGame(QXmlStreamWriter* w, const ActionLeaveGameDataPtr& d)
{
    w->writeStartElement("leave-game");
    w->writeEndElement();
}

ActionLeaveGameDataPtr ActionParser::readLeaveGame(XmlNode* n)
{
    Q_ASSERT(n->name() == "leave-game");
    ActionLeaveGameDataPtr res(new ActionLeaveGameData());
    return res;
}

void ActionParser::writePass(QXmlStreamWriter* w, const ActionPassDataPtr& d)
{
    w->writeStartElement("pass");
    w->writeEndElement();
}

ActionPassDataPtr ActionParser::readPass(XmlNode* n)
{
    Q_ASSERT(n->name() == "pass");
    ActionPassDataPtr res(new ActionPassData());
    return res;
}

void ActionParser::writePlayCard(QXmlStreamWriter* w, const ActionPlayCardDataPtr& d)
{
    w->writeStartElement("play-card");
    w->writeAttribute("played-card-id", toString(d->playedCardId));
    w->writeAttribute("target-card-id", toString(d->targetCardId));
    w->writeAttribute("discard-card-id", toString(d->discardCardId));
    w->writeAttribute("target-player-id", toString(d->targetPlayerId));
    w->writeEndElement();
}

ActionPlayCardDataPtr ActionParser::readPlayCard(XmlNode* n)
{
    Q_ASSERT(n->name() == "play-card");
    ActionPlayCardDataPtr res(new ActionPlayCardData());
    fromString(n->attribute("played-card-id"), res->playedCardId);
    fromString(n->attribute("target-card-id"), res->targetCardId);
    fromString(n->attribute("discard-card-id"), res->discardCardId);
    fromString(n->attribute("target-player-id"), res->targetPlayerId);
    return res;
}

void ActionParser::writeStartGame(QXmlStreamWriter* w, const ActionStartGameDataPtr& d)
{
    w->writeStartElement("start-game");
    w->writeEndElement();
}

ActionStartGameDataPtr ActionParser::readStartGame(XmlNode* n)
{
    Q_ASSERT(n->name() == "start-game");
    ActionStartGameDataPtr res(new ActionStartGameData());
    return res;
}

void ActionParser::writeUseAbility(QXmlStreamWriter* w, const ActionUseAbilityDataPtr& d)
{
    w->writeStartElement("use-ability");
    w->writeAttribute("target-player-id", toString(d->targetPlayerId));
    GameStructParser::write(w, d->targetCardsId, "target-cards");
    w->writeEndElement();
}

ActionUseAbilityDataPtr ActionParser::readUseAbility(XmlNode* n)
{
    Q_ASSERT(n->name() == "use-ability");
    ActionUseAbilityDataPtr res(new ActionUseAbilityData());
    fromString(n->attribute("target-player-id"), res->targetPlayerId);
    foreach (XmlNode* ch, n->getChildren()) {
        if (ch->name() == "target-cards") {
            GameStructParser::read(ch, res->targetCardsId);
            continue;
        }
    }
    return res;
}

//[[[end]]]