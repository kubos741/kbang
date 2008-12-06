/********************************************************************************
** Form generated from reading ui file 'logwidget.ui'
**
** Created: Sat Nov 8 21:35:22 2008
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LOGWIDGET_H
#define UI_LOGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogWidget
{
public:
    QGridLayout *gridLayout;
    QTabWidget *mp_tabWidget;
    QWidget *mp_tabLog;
    QGridLayout *gridLayout_3;
    QTextBrowser *mp_logView;
    QWidget *mp_tabDebug;
    QGridLayout *gridLayout_2;
    QTextBrowser *mp_xmlView;

    void setupUi(QWidget *LogWidget)
    {
    if (LogWidget->objectName().isEmpty())
        LogWidget->setObjectName(QString::fromUtf8("LogWidget"));
    LogWidget->resize(296, 279);
    gridLayout = new QGridLayout(LogWidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    mp_tabWidget = new QTabWidget(LogWidget);
    mp_tabWidget->setObjectName(QString::fromUtf8("mp_tabWidget"));
    mp_tabLog = new QWidget();
    mp_tabLog->setObjectName(QString::fromUtf8("mp_tabLog"));
    gridLayout_3 = new QGridLayout(mp_tabLog);
    gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
    mp_logView = new QTextBrowser(mp_tabLog);
    mp_logView->setObjectName(QString::fromUtf8("mp_logView"));
    mp_logView->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 0);"));
    mp_logView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    gridLayout_3->addWidget(mp_logView, 0, 0, 1, 1);

    mp_tabWidget->addTab(mp_tabLog, QString());
    mp_tabDebug = new QWidget();
    mp_tabDebug->setObjectName(QString::fromUtf8("mp_tabDebug"));
    gridLayout_2 = new QGridLayout(mp_tabDebug);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    mp_xmlView = new QTextBrowser(mp_tabDebug);
    mp_xmlView->setObjectName(QString::fromUtf8("mp_xmlView"));
    mp_xmlView->setAutoFillBackground(false);
    mp_xmlView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mp_xmlView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mp_xmlView->setOpenLinks(false);

    gridLayout_2->addWidget(mp_xmlView, 0, 0, 1, 1);

    mp_tabWidget->addTab(mp_tabDebug, QString());

    gridLayout->addWidget(mp_tabWidget, 0, 0, 1, 1);

    mp_tabWidget->raise();
    mp_tabWidget->raise();

    retranslateUi(LogWidget);

    mp_tabWidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(LogWidget);
    } // setupUi

    void retranslateUi(QWidget *LogWidget)
    {
    LogWidget->setWindowTitle(QApplication::translate("LogWidget", "Form", 0, QApplication::UnicodeUTF8));
    mp_tabWidget->setTabText(mp_tabWidget->indexOf(mp_tabLog), QApplication::translate("LogWidget", "Log", 0, QApplication::UnicodeUTF8));
    mp_xmlView->setHtml(QApplication::translate("LogWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
    mp_tabWidget->setTabText(mp_tabWidget->indexOf(mp_tabDebug), QApplication::translate("LogWidget", "Xml", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(LogWidget);
    } // retranslateUi

};

namespace Ui {
    class LogWidget: public Ui_LogWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGWIDGET_H
