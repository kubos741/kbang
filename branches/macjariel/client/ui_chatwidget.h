/********************************************************************************
** Form generated from reading ui file 'chatwidget.ui'
**
** Created: Sat Nov 8 21:35:22 2008
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CHATWIDGET_H
#define UI_CHATWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QLineEdit>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *mp_chatView;
    QLineEdit *mp_messageBox;

    void setupUi(QWidget *ChatWidget)
    {
    if (ChatWidget->objectName().isEmpty())
        ChatWidget->setObjectName(QString::fromUtf8("ChatWidget"));
    ChatWidget->resize(299, 247);
    verticalLayout = new QVBoxLayout(ChatWidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    mp_chatView = new QTextBrowser(ChatWidget);
    mp_chatView->setObjectName(QString::fromUtf8("mp_chatView"));
    mp_chatView->setFocusPolicy(Qt::NoFocus);
    mp_chatView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    verticalLayout->addWidget(mp_chatView);

    mp_messageBox = new QLineEdit(ChatWidget);
    mp_messageBox->setObjectName(QString::fromUtf8("mp_messageBox"));

    verticalLayout->addWidget(mp_messageBox);


    retranslateUi(ChatWidget);

    QMetaObject::connectSlotsByName(ChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ChatWidget)
    {
    ChatWidget->setWindowTitle(QApplication::translate("ChatWidget", "Form", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ChatWidget);
    } // retranslateUi

};

namespace Ui {
    class ChatWidget: public Ui_ChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWIDGET_H
