/********************************************************************************
** Form generated from reading ui file 'connecttoserverdialog.ui'
**
** Created: Sat Nov 8 21:35:22 2008
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CONNECTTOSERVERDIALOG_H
#define UI_CONNECTTOSERVERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectToServerDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_4;
    QLabel *label_4;
    QLineEdit *mp_lineEditProfileName;
    QLabel *label1;
    QLineEdit *mp_lineEditHostName;
    QLabel *label3;
    QLineEdit *mp_lineEditNickName;
    QLabel *label2;
    QSpinBox *mp_spinBoxPort;
    QSpacerItem *horizontalSpacer_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QTreeWidget *mp_favoriteList;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *mp_buttonSaveFavorite;
    QPushButton *mp_buttonDeleteFavorite;
    QWidget *tab_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QWidget *tab_3;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *mp_connectButton;
    QPushButton *mp_cancelButton;

    void setupUi(QDialog *ConnectToServerDialog)
    {
    if (ConnectToServerDialog->objectName().isEmpty())
        ConnectToServerDialog->setObjectName(QString::fromUtf8("ConnectToServerDialog"));
    ConnectToServerDialog->resize(438, 384);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(ConnectToServerDialog->sizePolicy().hasHeightForWidth());
    ConnectToServerDialog->setSizePolicy(sizePolicy);
    ConnectToServerDialog->setMinimumSize(QSize(0, 0));
    ConnectToServerDialog->setMaximumSize(QSize(16777215, 16777215));
    verticalLayout_2 = new QVBoxLayout(ConnectToServerDialog);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
    gridLayout_4 = new QGridLayout();
    gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
    label_4 = new QLabel(ConnectToServerDialog);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    gridLayout_4->addWidget(label_4, 0, 0, 1, 1);

    mp_lineEditProfileName = new QLineEdit(ConnectToServerDialog);
    mp_lineEditProfileName->setObjectName(QString::fromUtf8("mp_lineEditProfileName"));

    gridLayout_4->addWidget(mp_lineEditProfileName, 0, 1, 1, 1);

    label1 = new QLabel(ConnectToServerDialog);
    label1->setObjectName(QString::fromUtf8("label1"));

    gridLayout_4->addWidget(label1, 0, 3, 1, 1);

    mp_lineEditHostName = new QLineEdit(ConnectToServerDialog);
    mp_lineEditHostName->setObjectName(QString::fromUtf8("mp_lineEditHostName"));

    gridLayout_4->addWidget(mp_lineEditHostName, 0, 4, 1, 1);

    label3 = new QLabel(ConnectToServerDialog);
    label3->setObjectName(QString::fromUtf8("label3"));

    gridLayout_4->addWidget(label3, 1, 0, 1, 1);

    mp_lineEditNickName = new QLineEdit(ConnectToServerDialog);
    mp_lineEditNickName->setObjectName(QString::fromUtf8("mp_lineEditNickName"));

    gridLayout_4->addWidget(mp_lineEditNickName, 1, 1, 1, 1);

    label2 = new QLabel(ConnectToServerDialog);
    label2->setObjectName(QString::fromUtf8("label2"));

    gridLayout_4->addWidget(label2, 1, 3, 1, 1);

    mp_spinBoxPort = new QSpinBox(ConnectToServerDialog);
    mp_spinBoxPort->setObjectName(QString::fromUtf8("mp_spinBoxPort"));
    mp_spinBoxPort->setMaximum(65536);
    mp_spinBoxPort->setValue(6543);

    gridLayout_4->addWidget(mp_spinBoxPort, 1, 4, 1, 1);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout_4->addItem(horizontalSpacer_3, 0, 2, 1, 1);


    verticalLayout_2->addLayout(gridLayout_4);

    tabWidget = new QTabWidget(ConnectToServerDialog);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    verticalLayout = new QVBoxLayout(tab);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    mp_favoriteList = new QTreeWidget(tab);
    new QTreeWidgetItem(mp_favoriteList);

    mp_favoriteList->setObjectName(QString::fromUtf8("mp_favoriteList"));
    mp_favoriteList->setIndentation(15);
    mp_favoriteList->setRootIsDecorated(false);
    mp_favoriteList->setUniformRowHeights(false);
    mp_favoriteList->setItemsExpandable(false);
    mp_favoriteList->setSortingEnabled(true);
    mp_favoriteList->setAnimated(true);
    mp_favoriteList->setAllColumnsShowFocus(true);

    verticalLayout->addWidget(mp_favoriteList);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    mp_buttonSaveFavorite = new QPushButton(tab);
    mp_buttonSaveFavorite->setObjectName(QString::fromUtf8("mp_buttonSaveFavorite"));

    horizontalLayout_3->addWidget(mp_buttonSaveFavorite);

    mp_buttonDeleteFavorite = new QPushButton(tab);
    mp_buttonDeleteFavorite->setObjectName(QString::fromUtf8("mp_buttonDeleteFavorite"));

    horizontalLayout_3->addWidget(mp_buttonDeleteFavorite);


    verticalLayout->addLayout(horizontalLayout_3);

    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    gridLayout = new QGridLayout(tab_2);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(tab_2);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(label, 0, 0, 1, 1);

    tabWidget->addTab(tab_2, QString());
    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    gridLayout_3 = new QGridLayout(tab_3);
    gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
    label_3 = new QLabel(tab_3);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setAlignment(Qt::AlignCenter);

    gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

    tabWidget->addTab(tab_3, QString());

    verticalLayout_2->addWidget(tabWidget);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalSpacer = new QSpacerItem(228, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    mp_connectButton = new QPushButton(ConnectToServerDialog);
    mp_connectButton->setObjectName(QString::fromUtf8("mp_connectButton"));
    mp_connectButton->setEnabled(false);
    mp_connectButton->setDefault(true);

    horizontalLayout_2->addWidget(mp_connectButton);

    mp_cancelButton = new QPushButton(ConnectToServerDialog);
    mp_cancelButton->setObjectName(QString::fromUtf8("mp_cancelButton"));

    horizontalLayout_2->addWidget(mp_cancelButton);


    verticalLayout_2->addLayout(horizontalLayout_2);


#ifndef QT_NO_SHORTCUT
    label_4->setBuddy(mp_lineEditProfileName);
    label1->setBuddy(mp_lineEditHostName);
    label3->setBuddy(mp_lineEditNickName);
    label2->setBuddy(mp_spinBoxPort);
#endif // QT_NO_SHORTCUT

    QWidget::setTabOrder(mp_lineEditHostName, mp_spinBoxPort);
    QWidget::setTabOrder(mp_spinBoxPort, mp_lineEditNickName);
    QWidget::setTabOrder(mp_lineEditNickName, tabWidget);
    QWidget::setTabOrder(tabWidget, mp_favoriteList);
    QWidget::setTabOrder(mp_favoriteList, mp_buttonSaveFavorite);
    QWidget::setTabOrder(mp_buttonSaveFavorite, mp_buttonDeleteFavorite);
    QWidget::setTabOrder(mp_buttonDeleteFavorite, mp_connectButton);
    QWidget::setTabOrder(mp_connectButton, mp_cancelButton);

    retranslateUi(ConnectToServerDialog);

    tabWidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(ConnectToServerDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectToServerDialog)
    {
    ConnectToServerDialog->setWindowTitle(QApplication::translate("ConnectToServerDialog", "Connect To KBang Server", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("ConnectToServerDialog", "P&rofile Name:", 0, QApplication::UnicodeUTF8));
    label1->setText(QApplication::translate("ConnectToServerDialog", "&Server Address:", 0, QApplication::UnicodeUTF8));
    label3->setText(QApplication::translate("ConnectToServerDialog", "Your &Nickname:", 0, QApplication::UnicodeUTF8));
    label2->setText(QApplication::translate("ConnectToServerDialog", "&Port:", 0, QApplication::UnicodeUTF8));
    mp_spinBoxPort->setSuffix(QString());
    mp_favoriteList->headerItem()->setText(0, QApplication::translate("ConnectToServerDialog", "Name", 0, QApplication::UnicodeUTF8));
    mp_favoriteList->headerItem()->setText(1, QApplication::translate("ConnectToServerDialog", "Server Address", 0, QApplication::UnicodeUTF8));
    mp_favoriteList->headerItem()->setText(2, QApplication::translate("ConnectToServerDialog", "Port", 0, QApplication::UnicodeUTF8));
    mp_favoriteList->headerItem()->setText(3, QApplication::translate("ConnectToServerDialog", "Nickname", 0, QApplication::UnicodeUTF8));

    const bool __sortingEnabled = mp_favoriteList->isSortingEnabled();
    mp_favoriteList->setSortingEnabled(false);
    mp_favoriteList->topLevelItem(0)->setText(0, QApplication::translate("ConnectToServerDialog", "localhost", 0, QApplication::UnicodeUTF8));
    mp_favoriteList->topLevelItem(0)->setText(1, QApplication::translate("ConnectToServerDialog", "127.0.0.1", 0, QApplication::UnicodeUTF8));
    mp_favoriteList->topLevelItem(0)->setText(2, QApplication::translate("ConnectToServerDialog", "6543", 0, QApplication::UnicodeUTF8));

    mp_favoriteList->setSortingEnabled(__sortingEnabled);
    mp_buttonSaveFavorite->setText(QApplication::translate("ConnectToServerDialog", "Save", 0, QApplication::UnicodeUTF8));
    mp_buttonDeleteFavorite->setText(QApplication::translate("ConnectToServerDialog", "Delete", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ConnectToServerDialog", "Favorite Servers", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ConnectToServerDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This is a nice-to-have feature. <span style=\" font-weight:600;\">Maybe </span>it will be implemented in the future.</p></body></html>", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ConnectToServerDialog", "Internet Servers", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("ConnectToServerDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This is a nice-to-have feature. <span style=\" font-weight:600;\">Maybe</span> it will be implemented in the future.</p></body></html>", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("ConnectToServerDialog", "LAN Servers", 0, QApplication::UnicodeUTF8));
    mp_connectButton->setText(QApplication::translate("ConnectToServerDialog", "&Connect", 0, QApplication::UnicodeUTF8));
    mp_cancelButton->setText(QApplication::translate("ConnectToServerDialog", "C&ancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ConnectToServerDialog);
    } // retranslateUi

};

namespace Ui {
    class ConnectToServerDialog: public Ui_ConnectToServerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTTOSERVERDIALOG_H
