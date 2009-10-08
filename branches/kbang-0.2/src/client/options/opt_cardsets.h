#ifndef OPTIONSCARDSETS_H
#define OPTIONSCARDSETS_H

#include "optionstab.h"

class QModelIndex;
class QStandardItem;

namespace client {

class OptionsCardsetsPrivate;

class OptionsCardsets: public OptionsTab
{
    Q_OBJECT;
public:
    OptionsCardsets(OptionsDialog* optionsDialog);
    virtual ~OptionsCardsets();
    virtual QWidget* widget();

public slots:
    void applyOptions();
    void restoreOptions();

private slots:
    void doLocalItemChanged(QStandardItem*);
    void doActivateRemoteItem(const QModelIndex&);
    void refreshRemoteModel();
        
    
private:
    friend class OptionsCardsetsPrivate;
    OptionsCardsetsPrivate* d_ptr;
};    
/*
private slots:
    void doUpdateData(QTreeWidgetItem*, int);
    

void refreshRemoteCardsets();
    void updateRemoteCardsets();
    void reloadLocalCardsets();
    void reloadRemoteCardsets();

    void initModels();

    QStringList             m_slotList;
    OptionsCardsetsUI*      mp_widget;
    QMap<QString, QString>  m_selectedCardsets;
    QStandardItemModel*     mp_remoteCardsetsModel;
    QueryResultHandler*     mp_queryHandler;
*/

}

#endif // OPTIONSCARDSETS_H
