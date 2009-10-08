#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include "debug/debugblock.h"
#include "opt_cardsets.h"
#include <QListWidgetItem>
#include <QPushButton>

using namespace client;


OptionsDialog::OptionsDialog(QWidget* parent):
        QDialog(parent),
        mp_ui(new Ui::OptionsDialog)
{
    mp_ui->setupUi(this);
    mp_ui->tabList->clear();
    setAttribute(Qt::WA_DeleteOnClose);
    connect(mp_ui->tabList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(doChangeTab(QListWidgetItem*)));
    connect(mp_ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)),
            this, SLOT(doOk()));
    connect(mp_ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked(bool)),
            this, SLOT(doApply()));
    connect(mp_ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked(bool)),
            this, SLOT(reject()));
    registerTab(new OptionsCardsets(this));
    mp_ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(0);
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
        optionsTab->restoreOptions();
    }
    
    mp_ui->tabs->setCurrentWidget(tab);
    mp_ui->tabNameLabel->setText(optionsTab->name());
    mp_ui->tabDescLabel->setText(optionsTab->desc());
    
    
    ///@todo icon
}

void OptionsDialog::setDirty(OptionsTab* tab)
{
    mp_ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(1);
    connect(this, SIGNAL(applyOptions()),
            tab, SLOT(applyOptions()));
}

void OptionsDialog::doOk()
{
    doApply();
    accept();
}

void OptionsDialog::doApply()
{
    DEBUG_BLOCK;
    emit applyOptions();
    disconnect(this, SIGNAL(applyOptions()));
    mp_ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(0);
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
