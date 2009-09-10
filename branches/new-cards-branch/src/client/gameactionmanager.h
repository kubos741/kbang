#ifndef CARDWIDGETCLICKHANDLER_H
#define CARDWIDGETCLICKHANDLER_H

#include <QList>

class QString;

namespace client
{

class Game;
class CardWidget;
class PlayerWidget;

/**
 * @note The functionality of GameActionManager will be probably changed. Now
 * the GameActionManager knows all cards and knows what to do when a card is
 * clicked. In some cases GameActionManager needs to switch into select
 * card/player mode after a card is clicked and the logic to determine what
 * to do is hard-wired in GameActionManager. There are two proposed scenarios:
 *  1. Every "ruleset" in KBang will describe rules that will tell clients how
 *     to behave. This rules would be stored in xml files. Advantages: server
 *     does not have to be changed (maybe only the distribution of xml files).
 *     Disadvantages: it may be hard to simply describe all the situations, for
 *     example we need to allow Calamity Janet play Missed as Bang!.
 *  2. After a card is clicked, Client will send a simple play-card command and
 *     if the card needs extra information, Server will respond with error, that
 *     will tell client to specify something. Advantages: client is more simple,
 *     server can change rules (fix bugs) without need to change client.
 *     Disadvantages: client will communicate more with server.
 *
 * @todo At the moment GameActionManager is broken.
 */
class GameActionManager
{
friend class Game;
public:
    bool isClickable(CardWidget*);
    bool onCardClicked(CardWidget*);
    void onCardRightClicked(CardWidget*);
    void onPlayerClicked(PlayerWidget*);
    void onEndTurnClicked();
    void onPassClicked();
    void setDiscardMode(bool inDiscardMode);

private:
    GameActionManager(Game* game);
    void onMainCardClicked(CardWidget*);
    void onCharacterClicked(CardWidget*);

    void selectPlayer(CardWidget* activeCard);
    void selectCards(CardWidget* activeCard, int cardCount = 1);
    void unsetActiveCard();

    void addToSelection(CardWidget* card);
    void removeFromSelection(CardWidget* card);

    void useAbilityWithCards();
    void playWithCards();

    void debug(const QString&);

    enum {
        STATE_MAIN,
        STATE_SELECT_CARDS,
        STATE_SELECT_PLAYER,
        STATE_DISCARD
    } m_state;


    Game*               mp_game;
    CardWidget*         mp_activeCard;
    QList<CardWidget*>  m_cardSelection;
    int                 m_selectionSize;
};
}

#endif // CARDWIDGETCLICKHANDLER_H
