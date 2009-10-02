#ifndef ACTIONPARSER_H
#define ACTIONPARSER_H

#include "actions.h"
#include <QXmlStreamWriter>
#include "parser/xmlnode.h"

class ActionParser
{
public:
    static QString elementName(ActionData::Type);

    static void write(QXmlStreamWriter*, const ActionDataPtr&);
    static ActionDataPtr read(XmlNode*);

    static void writeCreateGame(QXmlStreamWriter*, const ActionCreateGameDataPtr&);
    static ActionCreateGameDataPtr readCreateGame(XmlNode*);

    static void writeJoinGame(QXmlStreamWriter*, const ActionJoinGameDataPtr&);
    static ActionJoinGameDataPtr readJoinGame(XmlNode*);

    static void writeLeaveGame(QXmlStreamWriter*, const ActionLeaveGameDataPtr&);
    static ActionLeaveGameDataPtr readLeaveGame(XmlNode*);

    static void writeStartGame(QXmlStreamWriter*, const ActionStartGameDataPtr&);
    static ActionStartGameDataPtr readStartGame(XmlNode*);

    static void writeChatMessage(QXmlStreamWriter*, const ActionChatMessageDataPtr&);
    static ActionChatMessageDataPtr readChatMessage(XmlNode*);

    static void writeDrawCard(QXmlStreamWriter*, const ActionDrawCardDataPtr&);
    static ActionDrawCardDataPtr readDrawCard(XmlNode*);

    static void writePlayCard(QXmlStreamWriter*, const ActionPlayCardDataPtr&);
    static ActionPlayCardDataPtr readPlayCard(XmlNode*);

    static void writeUseAbility(QXmlStreamWriter*, const ActionUseAbilityDataPtr&);
    static ActionUseAbilityDataPtr readUseAbility(XmlNode*);

    static void writeEndTurn(QXmlStreamWriter*, const ActionEndTurnDataPtr&);
    static ActionEndTurnDataPtr readEndTurn(XmlNode*);

    static void writePass(QXmlStreamWriter*, const ActionPassDataPtr&);
    static ActionPassDataPtr readPass(XmlNode*);

    static void writeDiscard(QXmlStreamWriter*, const ActionDiscardDataPtr&);
    static ActionDiscardDataPtr readDiscard(XmlNode*);
};

#endif // ACTIONPARSER_H
