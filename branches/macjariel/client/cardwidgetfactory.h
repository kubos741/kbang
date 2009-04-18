#ifndef CARDWIDGETFACTORY_H
#define CARDWIDGETFACTORY_H

#include "util.h"

class QWidget;

namespace client
{

class Game;
class CardWidget;

class CardWidgetFactory: private NonCopyable
{
friend class Game;
public:
    CardWidget* createBulletsCard(QWidget* parent = 0);
    //CardWidget* createCharacterCard(QWidget* parent = 0); /// \todo Characters
    CardWidget* createBackCard(QWidget* parent = 0);

    void registerCard(CardWidget* cardWidget);

private:
    CardWidgetFactory(Game* game);
    CardWidget* createCardWidget(QWidget* parent);
    Game* mp_game;
};

}
#endif // CARDWIDGETFACTORY_H
