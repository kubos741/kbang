#ifndef OPTIONSCARDSETS_H
#define OPTIONSCARDSETS_H

#include "optionstab.h"
#include "gametypes.h"
#include <QMap>

class QTreeWidgetItem;
class QStandardItemModel;

namespace client {

class OptionsCardsetsUI;

class OptionsCardsets: public OptionsTab
{
    Q_OBJECT;
public:
    OptionsCardsets(OptionsDialog* optionsDialog);
    virtual ~OptionsCardsets();
    virtual QWidget* widget();

private slots:
    void doUpdateData(QTreeWidgetItem*, int);

private:
    void reloadLocalCardsets();
    void reloadRemoteCardsets();

    void initModels();

    QStringList             m_slotList;
    OptionsCardsetsUI*      mp_widget;
    QMap<QString, QString>  m_selectedCardsets;
    QStandardItemModel*     mp_remoteCardsetsModel;

};

}

#endif // OPTIONSCARDSETS_H
