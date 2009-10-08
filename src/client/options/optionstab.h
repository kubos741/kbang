#ifndef OPTIONSTAB_H
#define OPTIONSTAB_H

#include <QObject>
#include <QIcon>

namespace client {
class OptionsDialog;

class OptionsTab: public QObject
{
    Q_OBJECT;
public:
    OptionsTab(OptionsDialog* optionsDialog, QString id, QString name,
               QString desc, QIcon icon = QIcon());
    virtual ~OptionsTab();

    QString id() const {
        return m_id;
    }

    QString name() const {
        return m_name;
    }

    QString desc() const {
        return m_desc;
    }

    QIcon icon() const {
        return m_icon;
    }

    virtual QWidget* widget() = 0;

public slots:
    virtual void applyOptions();
    virtual void restoreOptions();

protected:
    void setDirty();
    
    OptionsDialog*  mp_optionsDialog;

private:
    QString         m_id;
    QString         m_name;
    QString         m_desc;
    QIcon           m_icon;
};
}

#endif // OPTIONSTAB_H
