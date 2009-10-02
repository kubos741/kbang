#include "opt_cardsets.h"
#include "ui_opt_cardsets.h"
#include "optionsdialog.h"

#include <QStandardItemModel>
#include <QtDebug>



using namespace client;

QString localeListToString(QList<QLocale> locales)
{
    QStringList languages;
    foreach (const QLocale locale, cardset.locales) {
        languages << QLocale::languageToString(locale.language());
    }
    return languages.join(", ");
}

class client::OptionsCardsetsUI: public QWidget, public Ui::OptionsCardsets
{
public:
    OptionsCardsetsUI(QWidget* parent);
    void setRemoteCardsetsModel(QAbstractItemModel*);
    friend class OptionsCardsets;
};

OptionsCardsetsUI::OptionsCardsetsUI(QWidget* parent):
        QWidget(parent)
{
    setupUi(this);
    localCardsetsWidget->header()->setResizeMode(QHeaderView::ResizeToContents);
}

void OptionsCardsetsUI::setRemoteCardsetsModel(QAbstractItemModel* model)
{
    remoteCardsetsWidget->setModel(model);
    remoteCardsetsWidget->header()->setResizeMode(QHeaderView::ResizeToContents);
}

OptionsCardsets::OptionsCardsets(OptionsDialog* optionsDialog):
        OptionsTab(optionsDialog, "cardsets", tr("Card Sets"), tr("Select card sets and download new")),
        mp_widget(0),
        mp_remoteCardsetsModel(0)
{
    m_slotList << "bang-original" << "bang-dodge-city" << "bang-high-noon";
}

OptionsCardsets::~OptionsCardsets()
{
}

QWidget* OptionsCardsets::widget()
{
    if (mp_widget == 0) {
        mp_widget = new OptionsCardsetsUI(mp_optionsDialog);
        initModels();
        mp_widget->setRemoteCardsetsModel(mp_remoteCardsetsModel);
        reloadLocalCardsets();
        connect(mp_widget->localCardsetsWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
                this, SLOT(doUpdateData(QTreeWidgetItem*,int)));
    }
    return mp_widget;
}

void OptionsCardsets::doUpdateData(QTreeWidgetItem* item, int)
{
    QTreeWidgetItem* parent = item->parent();
    Q_ASSERT(parent != 0);
    if (item->checkState(0) != Qt::Checked) {
        return;
    }
    for (int i = 0; i < parent->childCount(); ++i) {
        if (parent->child(i) != item) {
            qDebug() << parent->child(i) << item;
            parent->child(i)->setCheckState(0, Qt::Unchecked);
        }
    }
    m_selectedCardsets[parent->data(0, Qt::UserRole).toString()] =
            item->data(0, Qt::UserRole).toString();
}


void OptionsCardsets::updateRemoteCardsetsModel(const CardSetInfoListData& list)
{
    if (mp_remoteCardsetsModel == 0) {
        return;
    }
    foreach (const CardSetInfoData& data, list) {
        QStandardItem* root = mp_remoteCardsetsModel->invisibleRootItem();
        QStandardItem* slotItem = 0;
        for (int i = 0; i < root->rowCount(); ++i) {
             slotItem = root->child(i);
             if (slotItem->data(Qt::UserRole).toString() == data.slot) {
                 break;
             }
             slotItem = 0;
        }
        if (slotItem == 0) {
            // Cardset with unknown slot encountered
            continue;
        }
        QStandardItem* cardsetItem = 0;
        int index;
        for (index = 0; index < slotItem->rowCount(); ++index) {
             cardsetItem = slotItem->child(index);
             if (cardsetItem->data(Qt::UserRole).toString() == data.name) {
                 break;
             }
             cardsetItem = 0;
        }
        if (cardsetItem == 0) {
            // Add new cardset
            cardsetItem = new QStandardItem(data.displayName);  /// @todo translate
            cardsetItem->setData(data.name, Qt::UserRole);
            QList<QStandardItem*> row;
            row.append(cardsetItem);
            row.append(new QStandardItem(localeListToString(data.locales)));
            row.append(new QStandardItem(QString::number(data.revision)));
            // @todo append download button
            slotItem->appendRow(row);
        } else {
            // Update cardset
            cardsetItem->setText(data.displayName);  /// @todo translate
            slotItem->child(index, 1)->setText(localeListToString(data.locales));
            slotItem->child(index, 2)->setText(QString::number(data.revision));

        }
    }

}


void OptionsCardsets::reloadLocalCardsets()
{
    if (mp_widget == 0) {
        return;
    }
    /// @todo use real data instead of testing
    QStringList knownSlots;
    knownSlots << "bang-original" << "bang-dodge-city" << "bang-high-noon" <<
                  "bang-fistful-of-cards" << "bang-the-bullet";

    QList<CardSetInfoData> cardsets;
    CardSetInfoData x;
    x.name = "bang-original-v3-cs_CZ";
    x.displayName = "Original Bang! (version 3)";
    x.locales.append(QLocale("cs_CZ"));
    x.slot = "bang-original";
    x.revision = 1;
    cardsets.append(x);

    x.name = "bang-original-v3-orig";
    x.displayName = "Original Bang! (version 3)";
    x.locales.clear();
    x.locales.append(QLocale("it_IT"));
    x.locales.append(QLocale("en"));
    x.slot = "bang-original";
    x.revision = 1;
    cardsets.append(x);


    /// @todo end

    mp_widget->localCardsetsWidget->clear();
    foreach (const QString& slot, knownSlots) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, slot);
        item->setData(0, Qt::UserRole, slot);
        mp_widget->localCardsetsWidget->addTopLevelItem(item);
        foreach (const CardSetInfoData& cardset, cardsets) {
            if (cardset.slot == slot) {
                QTreeWidgetItem* cardsetItem = new QTreeWidgetItem();
                cardsetItem->setText(0, x.displayName);
                QStringList langs;
                foreach (const QLocale l, cardset.locales) {
                    langs << QLocale::languageToString(l.language());
                }
                cardsetItem->setText(1, langs.join(", "));
                cardsetItem->setText(2, QString::number(cardset.revision));
                cardsetItem->setData(0, Qt::UserRole, x.name);
                if (m_selectedCardsets[slot] == x.name) {
                    cardsetItem->setCheckState(0, Qt::Checked);
                } else {
                    cardsetItem->setCheckState(0, Qt::Unchecked);
                }
                item->addChild(cardsetItem);
            }
        }
        if (item->childCount() == 0) {
                QTreeWidgetItem* cardsetItem = new QTreeWidgetItem();
                cardsetItem->setText(0, tr("No cardsets for this slot."));
                QFont font;
                font.setItalic(1);
                cardsetItem->setData(0, Qt::FontRole, font);
                item->addChild(cardsetItem);
        }
    }
    mp_widget->localCardsetsWidget->expandAll();
}

void OptionsCardsets::reloadRemoteCardsets()
{

}

void OptionsCardsets::initModels()
{
    Q_ASSERT(mp_remoteCardsetsModel == 0);
    mp_remoteCardsetsModel = new QStandardItemModel(this);
    mp_remoteCardsetsModel->setColumnCount(4);
    mp_remoteCardsetsModel->setHorizontalHeaderLabels(QStringList() <<
                                                      tr("Name") <<
                                                      tr("Language") <<
                                                      tr("Revision") << "");
    foreach (const QString& slotId, m_slotList) {
        QStandardItem* item = new QStandardItem(slotId);
        item->setData(slotId, Qt::UserRole);
        mp_remoteCardsetsModel->invisibleRootItem()->appendRow(item);
    }
}
