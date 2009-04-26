#ifndef CARDWIDGETCLICKHANDLER_H
#define CARDWIDGETCLICKHANDLER_H

class QString;

namespace client
{

class Game;
class CardWidget;
class PlayerWidget;


class GameObjectClickHandler
{
friend class Game;
public:
    bool isClickable(CardWidget*);
    void onCardClicked(CardWidget*);
    void onPlayerClicked(PlayerWidget*);
    void onEndTurnClicked();
    void onPassClicked();
    void setDiscardMode(bool inDiscardMode);

private:
    GameObjectClickHandler(Game* game);
    void onMainCardClicked(CardWidget*);


    void setActiveCard(CardWidget* cardWidget);
    void unsetActiveCard();

    void setSelectPlayerState();
    void debug(const QString&);

    enum {
        STATE_MAIN,
        STATE_SELECT_CARD,
        STATE_SELECT_PLAYER
    } m_state;


    Game*       mp_game;
    CardWidget* mp_activeCard;
    bool        m_inDiscardMode;
};
}

#endif // CARDWIDGETCLICKHANDLER_H
