#include <QWidget>
#include "cardwidgetfactory.h"
#include "game.h"
#include "cardwidget.h"

using namespace client;

CardWidgetFactory::CardWidgetFactory(Game* game):
        mp_game(game)
{
}

CardWidget* CardWidgetFactory::createBulletsCard(QWidget* parent)
{
    CardWidget* cardWidget = createCardWidget(parent);
    cardWidget->setSize(CardWidget::SIZE_SMALL);
    cardWidget->setCardClass("back-bullets");
    return cardWidget;
}

CardWidget* CardWidgetFactory::createBackCard(QWidget* parent)
{
    CardWidget* cardWidget = createCardWidget(parent);
    cardWidget->setSize(CardWidget::SIZE_SMALL);
    cardWidget->setCardClass("back-bang");
    return cardWidget;
}

CardWidget* CardWidgetFactory::createCardWidget(QWidget* parent)
{
    CardWidget* cardWidget = new CardWidget(parent);
    registerCard(cardWidget);
    return cardWidget;
}


void CardWidgetFactory::registerCard(CardWidget* cardWidget)
{
    cardWidget->setGameObjectClickHandler(mp_game->cardWidgetClickHandler());
}

