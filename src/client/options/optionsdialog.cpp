s#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include "debug/debugblock.h"
#include "opt_cardsets.h"
#include <QListWidgetItem>

using namespace client;


OptionsDialog::OptionsDialog(QWidget* parent):
        QDialog(parent),
        mp_ui(new Ui::OptionsDialog)
{
    mp_ui->setupUi(this);
    mp_ui->tabList->clear();
    connect(mp_ui->tabList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(doChangeTab(QListWidgetItem*)));
    registerTab(new OptionsCardsets(this));
    //openTab("cardsets");
}

OptionsDialog::~OptionsDialog()
{
}

void OptionsDialog::openTab(const QString& id)
{
    if (id.isEmpty()) {
        return;
    }

    QHash<QString, OptionsTab*>::iterator it = m_tabs.find(id);
    if (it == m_tabs.end()) {
            return;
    }
    OptionsTab* optionsTab = it.value();
    QWidget* tab = optionsTab->widget();
    
    if (!m_loadedTabWidgets.contains(tab)) {
        m_loadedTabWidgets.insert(tab);
        mp_ui->tabs->addWidget(tab);
    }
    
    mp_ui->tabs->setCurrentWidget(tab);
    mp_ui->tabNameLabel->setText(optionsTab->name());
    mp_ui->tabDescLabel->setText(optionsTab->desc());
    
    
    ///@todo icon
}


void OptionsDialog::doOk()
{
}

void OptionsDialog::doApply()
{
}

void OptionsDialog::doChangeTab(QListWidgetItem* item)
{
    openTab(item->data(Qt::UserRole).toString());
}

void OptionsDialog::registerTab(OptionsTab* tab)
{
    m_tabs[tab->id()] = tab;
    QListWidgetItem* item = new QListWidgetItem(tab->icon(), tab->name(),
                                                mp_ui->tabList);
    item->setData(Qt::UserRole, tab->id());
}
