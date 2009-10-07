#include "actionparser.h"
#include "util.h"


/* static */
QString ActionParser::elementName(ActionData::Type)
{
	NOT_IMPLEMENTED();
}


/* static */
void ActionParser::write(QXmlStreamWriter* w, const ActionDataPtr& d)
{
    w->writeStartElement("action");
    switch (d->t()) {
    case ActionData::CreateGameType: writeCreateGame(w, d.staticCast<ActionCreateGameData>());
        break;
    case ActionData::JoinGameType: writeJoinGame(w, d.staticCast<ActionJoinGameData>());
        break;
    case ActionData::LeaveGameType: writeLeaveGame(w, d.staticCast<ActionLeaveGameData>());
        break;
    case ActionData::StartGameType: writeStartGame(w, d.staticCast<ActionStartGameData>());
        break;
    case ActionData::ChatMessageType: writeChatMessage(w, d.staticCast<ActionChatMessageData>());
        break;
    case ActionData::DrawCardType: writeDrawCard(w, d.staticCast<ActionDrawCardData>());
        break;
    case ActionData::PlayCardType: writePlayCard(w, d.staticCast<ActionPlayCardData>());
        break;
    case ActionData::UseAbilityType: writeUseAbility(w, d.staticCast<ActionUseAbilityData>());
        break;
    case ActionData::EndTurnType: writeEndTurn(w, d.staticCast<ActionEndTurnData>());
        break;
    case ActionData::PassType: writePass(w, d.staticCast<ActionPassData>());
        break;
    case ActionData::DiscardType: writeDiscard(w, d.staticCast<ActionDiscardData>());
        break;
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
    } else if (n->name() == elementName(ActionData::CreateGameType)) {
        res = readCreateGame(n);
    } else if (n->name() == elementName(ActionData::JoinGameType)) {
        res = readJoinGame(n);
    } else if (n->name() == elementName(ActionData::LeaveGameType)) {
        res = readLeaveGame(n);
    } else if (n->name() == elementName(ActionData::StartGameType)) {
        res = readStartGame(n);
    } else if (n->name() == elementName(ActionData::ChatMessageType)) {
        res = readChatMessage(n);
    } else if (n->name() == elementName(ActionData::DrawCardType)) {
        res = readDrawCard(n);
    } else if (n->name() == elementName(ActionData::PlayCardType)) {
        res = readPlayCard(n);
    } else if (n->name() == elementName(ActionData::UseAbilityType)) {
        res = readUseAbility(n);
    } else if (n->name() == elementName(ActionData::EndTurnType)) {
        res = readEndTurn(n);
    } else if (n->name() == elementName(ActionData::PassType)) {
        res = readPass(n);
    } else if (n->name() == elementName(ActionData::DiscardType)) {
        res = readDiscard(n);
    }
    return res;
}


/* static */
void ActionParser::writeCreateGame(QXmlStreamWriter* w, const ActionCreateGameDataPtr& d)
{
    NOT_IMPLEMENTED();
}


/* static */
ActionCreateGameDataPtr ActionParser::readCreateGame(XmlNode* n)
{
    NOT_IMPLEMENTED();
}


/* static */
void ActionParser::writeJoinGame(QXmlStreamWriter* w, const ActionJoinGameDataPtr& d)
{
    NOT_IMPLEMENTED();
}


/* static */
ActionJoinGameDataPtr ActionParser::readJoinGame(XmlNode* n)
{
    NOT_IMPLEMENTED();
}


/* static */
void ActionParser::writeLeaveGame(QXmlStreamWriter* w, const ActionLeaveGameDataPtr& d)
{
    NOT_IMPLEMENTED();
}


/* static */
ActionLeaveGameDataPtr ActionParser::readLeaveGame(XmlNode* n)
{
    NOT_IMPLEMENTED();
}


/* static */
void ActionParser::writeStartGame(QXmlStreamWriter* w, const ActionStartGameDataPtr& d)
{
    NOT_IMPLEMENTED();
}


/* static */
ActionStartGameDataPtr ActionParser::readStartGame(XmlNode* n)
{
    NOT_IMPLEMENTED();
}


/* static */
void ActionParser::writeChatMessage(QXmlStreamWriter* w, const ActionChatMessageDataPtr& d)
{
    NOT_IMPLEMENTED();
}


/* static */
ActionChatMessageDataPtr ActionParser::readChatMessage(XmlNode* n)
{
    NOT_IMPLEMENTED();
}


/* static */
void ActionParser::writeDrawCard(QXmlStreamWriter* w, const ActionDrawCardDataPtr& d)
{
    NOT_IMPLEMENTED();
}


/* static */
ActionDrawCardDataPtr ActionParser::readDrawCard(XmlNode* n)
{
    NOT_IMPLEMENTED();
}


/* static */
void ActionParser::writePlayCard(QXmlStreamWriter* w, const ActionPlayCardDataPtr& d)
{
    NOT_IMPLEMENTED();
}


/* static */
ActionPlayCardDataPtr ActionParser::readPlayCard(XmlNode* n)
{
    NOT_IMPLEMENTED();
}


/* static */
void ActionParser::writeUseAbility(QXmlStreamWriter* w, const ActionUseAbilityDataPtr& d)
{
    NOT_IMPLEMENTED();
}


/* static */
ActionUseAbilityDataPtr ActionParser::readUseAbility(XmlNode* n)
{
    NOT_IMPLEMENTED();
}


/* static */
void ActionParser::writeEndTurn(QXmlStreamWriter* w, const ActionEndTurnDataPtr& d)
{
    NOT_IMPLEMENTED();
}


/* static */
ActionEndTurnDataPtr ActionParser::readEndTurn(XmlNode* n)
{
    NOT_IMPLEMENTED();
}


/* static */
void ActionParser::writePass(QXmlStreamWriter* w, const ActionPassDataPtr& d)
{
    NOT_IMPLEMENTED();
}


/* static */
ActionPassDataPtr ActionParser::readPass(XmlNode* n)
{
    NOT_IMPLEMENTED();
}


/* static */
void ActionParser::writeDiscard(QXmlStreamWriter* w, const ActionDiscardDataPtr& d)
{
    NOT_IMPLEMENTED();
}


/* static */
ActionDiscardDataPtr ActionParser::readDiscard(XmlNode* n)
{
    NOT_IMPLEMENTED();
}
