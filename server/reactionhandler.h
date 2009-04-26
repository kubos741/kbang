#ifndef REACTIONHANDLER_H
#define REACTIONHANDLER_H

#include <QObject>

class PlayingCard;

class ReactionHandler
{
public:
    virtual ~ReactionHandler() {}
    virtual void respondPass();
    virtual void respondCard(PlayingCard* targetCard);
};

#endif // REACTIONHANDLER_H
