
#include <QApplication>
#include "optionsdialog.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    client::OptionsDialog dialog(0);
    dialog.show();
    return app.exec();
}
