#ifndef ABSTRACTPLAYERCONTROLLER_H
#define ABSTRACTPLAYERCONTROLLER_H

#include <QString>
#include "parser/parserstructs.h"

class CardAbstract;


/**
 * Abstract class that defines the interface to notify back PlayerControllers
 * about events.
 */
class AbstractPlayerController
{
public:
    /**
     * This method is called when someone sends a chat message.
     * \param playerId The id of the sender.
     * \param playerName The name of the sender.
     * \param message The chat message.
     */
    virtual void onIncomingMessage(int playerId, const QString& playerName, const QString& message) = 0;

    virtual void onPlayerJoinedGame(int playerId, const StructPlayer& playerStruct) = 0;

    virtual void onPlayerLeavedGame(int playerId) = 0;

    virtual void onGameStarted(const StructGame& structGame, const StructPlayerList& structPlayerList) = 0;

    /**
     * This method is called when a player draws a card. If the controlled player draws a card, the
     * card attribute points to that card, otherwise card is null.
     */
    virtual void onPlayerDrawedCard(int playerId, const CardAbstract* card) = 0;

    virtual ~AbstractPlayerController() = 0;
};


#endif // ABSTRACTPLAYERCONTROLLER_H
