#include "textformatter.h"
#include "game.h"
#include "playerwidget.h"
#include <QTextDocument>

using namespace client;

QString TextFormatter::playerName(PlayerId id)
{
    Game* game = Game::currentGame();
    if (!game) {
        return QString();
    }
    PlayerWidget* widget = game->playerWidget(id);
    if (!widget) {
        return QString();
    }
    return QString("<font color=\"navy\">%1</font>").
            arg(Qt::escape(widget->name()));
}
