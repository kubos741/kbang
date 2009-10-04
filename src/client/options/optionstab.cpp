#include "optionstab.h"
#include "optionsdialog.h"


using namespace client;

OptionsTab::OptionsTab(OptionsDialog* optionsDialog, QString id,
                       QString name, QString desc, QIcon icon):
        QObject(optionsDialog),
        mp_optionsDialog(optionsDialog),
        m_id(id),
        m_name(name),
        m_desc(desc),
        m_icon(icon)
{
}

OptionsTab::~OptionsTab()
{
}

void OptionsTab::applyOptions()
{
}

void OptionsTab::restoreOptions()
{
}
