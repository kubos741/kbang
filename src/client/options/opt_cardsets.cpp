#include "opt_cardsets.h"
#include "ui_opt_cardsets.h"
#include "optionsdialog.h"
#include "serverconnection.h"
#include "queries.h"
#include "cardsetmanager.h"

#include <QStandardItemModel>
#include "debug/debugblock.h"

namespace client {

///////////////
// functions
///////////////

QString localeListToString(const QList<QLocale>& locales)
{
    QStringList languages;
    foreach (const QLocale locale, locales) {
        languages << QLocale::languageToString(locale.language());
    }
    return languages.join(", ");
}

///////////////////////////////////
// class OptionsCardsetsUI
///////////////////////////////////

class OptionsCardsetsUI: public QWidget, public Ui::OptionsCardsets
{
public:
    OptionsCardsetsUI(QWidget* parent): QWidget(parent) {
        setupUi(this);
        localCardsetsWidget->header()->setResizeMode(QHeaderView::ResizeToContents);
        remoteCardsetsWidget->header()->setResizeMode(QHeaderView::ResizeToContents);
    }
    void setRemoteCardsetsModel(QAbstractItemModel*);
    friend class OptionsCardsets;
};

///////////////////////////////////
// class QueryCardsetHandler
///////////////////////////////////

class QueryCardsetHandler: public QueryResultHandler {
public:
    QueryCardsetHandler(OptionsCardsetsPrivate* pr): mp_pr(pr) {}
    virtual ~QueryCardsetHandler() {}
    virtual void resultReceived(const GameStructPtr& g);
    OptionsCardsetsPrivate* mp_pr;
};


///////////////////////////////////
// class OptionsCardsetsPrivate
///////////////////////////////////

class OptionsCardsetsPrivate: public QObject {
public:
    QStandardItemModel*     mp_localCardsetsModel;
    QStandardItemModel*     mp_remoteCardsetsModel;
    QStringList             m_slots;
    OptionsCardsetsUI*      mp_widget;
    QMap<QString, QString>  m_selectedCardsets;
    QueryCardsetHandler     m_queryHandler;
    OptionsDialog*          mp_optionsDialog;
    
    OptionsCardsetsPrivate(OptionsDialog* dialog):
            mp_optionsDialog(dialog),
            mp_localCardsetsModel(0),
            mp_remoteCardsetsModel(0),
            mp_widget(0),
            m_queryHandler(this),
            mp_optionsDialog(0) {}
    
    void constructModels();
    void updateLocalModel();
    void updateRemoteModel(const CardSetInfoListData&);
};

void OptionsCardsetsPrivate::constructModels()
{
    Q_ASSERT(mp_remoteCardsetsModel == 0);
    mp_localCardsetsModel = new QStandardItemModel(this);
    mp_localCardsetsModel->setColumnCount(4);
    mp_localCardsetsModel->setHorizontalHeaderLabels(QStringList() <<
            OptionsCardsets::tr("Name") <<
            OptionsCardsets::tr("Language") <<
            OptionsCardsets::tr("Revision") << "");
    mp_remoteCardsetsModel = new QStandardItemModel(this);
    mp_remoteCardsetsModel->setColumnCount(4);
    mp_remoteCardsetsModel->setHorizontalHeaderLabels(QStringList() <<
            OptionsCardsets::tr("Name") <<
            OptionsCardsets::tr("Language") <<
            OptionsCardsets::tr("Revision") << "");
}

void OptionsCardsetsPrivate::updateLocalModel()
{
    if (mp_localCardsetsModel == 0) { return; }
    mp_localCardsetsModel->clear();
    QStandardItem* rootItem = mp_localCardsetsModel->invisibleRootItem();
    const QList<CardSetInfo>& list = CardSetManager::instance().localCardSets();
    
    foreach (const QString& slotId, CardSetManager::instance().knownSlots()) {
        QStandardItem* item = new QStandardItem(slotId);
        item->setData(slotId, Qt::UserRole);
        mp_localCardsetsModel->invisibleRootItem()->appendRow(item);
    }
       
    foreach (const CardSetInfo& cardset, list) {
        QStandardItem* slotItem = 0;
        for (int i = 0; i < rootItem->rowCount(); ++i) {
            slotItem = rootItem->child(i);
            if (slotItem->data(Qt::UserRole).toString() == cardset.slotId()) {
                break;
            }
            slotItem = 0;
        }
        if (slotItem == 0) {
            slotItem = new QStandardItem();
            slotItem->setText(CardSetManager::slotDisplayName(cardset.slotId()));
            slotItem->setData(cardset.slotId(), Qt::UserRole);
            rootItem->appendRow(slotItem);
            continue;
        }
        QList<QStandardItem*> cardsetRow;
        QStandardItem* cardsetItem = new QStandardItem();
        cardsetItem->setData(cardset.id(), Qt::UserRole);
        cardsetItem->setText(cardset.name());
        cardsetRow.append(cardsetItem);
        cardsetRow.append(new QStandardItem(localeListToString(cardset.locales())));
        cardsetRow.append(new QStandardItem(QString::number(cardset.revision())));
        slotItem->appendRow(cardsetRow);
    }
}

void OptionsCardsetsPrivate::updateRemoteModel(const CardSetInfoListData& list)
{
    if (mp_remoteCardsetsModel == 0) { return; }
    mp_remoteCardsetsModel->clear();
    QStandardItem* rootItem = mp_remoteCardsetsModel->invisibleRootItem();
    
    foreach (const CardSetInfoData& data, list) {
        QStandardItem* slotItem = 0;
        for (int i = 0; i < rootItem->rowCount(); ++i) {
            slotItem = rootItem->child(i);
            if (slotItem->data(Qt::UserRole).toString() == data.slotId) {
                break;
            }
            slotItem = 0;
        }
        if (slotItem == 0) {
            slotItem = new QStandardItem();
            slotItem->setText(CardSetManager::slotDisplayName(data.slotId));
            slotItem->setData(data.slotId, Qt::UserRole);
            rootItem->appendRow(slotItem);
            continue;
        }
        QList<QStandardItem*> cardsetRow;
        QStandardItem* cardsetItem = new QStandardItem();
        cardsetItem->setData(data.id, Qt::UserRole);
        cardsetItem->setText(data.name);
        cardsetRow.append(cardsetItem);
        cardsetRow.append(new QStandardItem(localeListToString(data.locales)));
        cardsetRow.append(new QStandardItem(QString::number(data.revision)));
        /// @todo append download button
        slotItem->appendRow(cardsetRow);
    }
}

void OptionsCardsets::doActivateLocalItem(const QModelIndex& index)
{
    QStandardItem* item = d_ptr->mp_localCardsetsModel->itemFromIndex(index);
    if (item == 0) { return; }
    if (item->data(Qt::UserRole) == 0) { return; }
    ///@todo implement this
}

void OptionsCardsets::doActivateRemoteItem(const QModelIndex& index)
{
    QStandardItem* item = d_ptr->mp_localCardsetsModel->itemFromIndex(index);
    if (item == 0) { return; }
    if (item->data(Qt::UserRole) == 0) { return; }
    ///@todo implement this
}

void OptionsCardsets::refreshRemoteModel()
{
    QueryCardsetInfoGetPtr query(new QueryCardsetInfoGet());
    ServerConnection::instance()->sendQueryGet(query, &d_ptr->m_queryHandler);
}

void QueryCardsetHandler::resultReceived(const GameStructPtr& g)
{
    if (g->t() == GameStruct::CardSetInfoListType) {
        mp_pr->updateRemoteModel(*g.staticCast<CardSetInfoListData>());
    }
}

///////////////////////////////
// class OptionsCardsets
///////////////////////////////

OptionsCardsets::OptionsCardsets(OptionsDialog* optionsDialog):
        OptionsTab(optionsDialog, "cardsets", tr("Card Sets"),
                   tr("Select card sets and download new")),
        d_ptr(new OptionsCardsetsPrivate(optionsDialog))
{
}

OptionsCardsets::~OptionsCardsets()
{
}

QWidget* OptionsCardsets::widget()
{
    if (d_ptr->mp_widget == 0) {
        d_ptr->mp_widget = new OptionsCardsetsUI(mp_optionsDialog);
        d_ptr->constructModels();
        d_ptr->mp_widget->localCardsetsWidget->setModel(
            d_ptr->mp_localCardsetsModel);
        d_ptr->mp_widget->remoteCardsetsWidget->setModel(
            d_ptr->mp_remoteCardsetsModel);
        d_ptr->updateLocalModel();
        
        connect(d_ptr->mp_widget->localCardsetsWidget, SIGNAL(activated(QModelIndex)),
                d_ptr, SLOT(doActivateLocalItem(QModelIndex)));
        connect(d_ptr->mp_widget->remoteCardsetsWidget, SIGNAL(activated(QModelIndex)),
                d_ptr, SLOT(doActivateRemoteItem(QModelIndex)));
    }
    return d_ptr->mp_widget;
}

void OptionsCardsets::applyOptions()
{
    ///@todo implement this
}

void OptionsCardsets::restoreOptions()
{
    ///@todo implement this
}

}