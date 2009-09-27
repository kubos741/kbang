#ifndef OPTIONSDLG_H
#define OPTIONSDLG_H

#include <QDialog>
#include <QSet>

class QListWidgetItem;

namespace Ui {
class OptionsDialog;
}

namespace client {

class OptionsTab;

class OptionsDialog: public QDialog
{
    Q_OBJECT;
public:
    OptionsDialog(QWidget* parent = 0);
    ~OptionsDialog();

    void openTab(const QString& id);

signals:
    void applyOptions();

private slots:
    void doOk();
    void doApply();
    void doChangeTab(QListWidgetItem* item);

private:
    void registerTab(OptionsTab*);
    Ui::OptionsDialog*  mp_ui;
    QHash<QString, OptionsTab*>  m_tabs;
    QSet<QWidget*>               m_loadedTabWidgets;
};

}

#endif
