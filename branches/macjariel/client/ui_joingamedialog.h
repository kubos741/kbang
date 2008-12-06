/********************************************************************************
** Form generated from reading ui file 'joingamedialog.ui'
**
** Created: Sat Nov 8 21:35:22 2008
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_JOINGAMEDIALOG_H
#define UI_JOINGAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_JoinGameDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *mp_gameListView;
    QTreeWidget *mp_playerListView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *mp_refreshButton;
    QPushButton *mp_playButton;
    QPushButton *mp_spectateButton;
    QPushButton *mp_cancelButton;

    void setupUi(QDialog *JoinGameDialog)
    {
    if (JoinGameDialog->objectName().isEmpty())
        JoinGameDialog->setObjectName(QString::fromUtf8("JoinGameDialog"));
    JoinGameDialog->resize(692, 277);
    verticalLayout = new QVBoxLayout(JoinGameDialog);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    mp_gameListView = new QTreeWidget(JoinGameDialog);
    mp_gameListView->setObjectName(QString::fromUtf8("mp_gameListView"));
    mp_gameListView->setFocusPolicy(Qt::NoFocus);
    mp_gameListView->setAlternatingRowColors(true);
    mp_gameListView->setIndentation(15);
    mp_gameListView->setRootIsDecorated(false);
    mp_gameListView->setItemsExpandable(false);
    mp_gameListView->setSortingEnabled(true);
    mp_gameListView->setAnimated(true);
    mp_gameListView->setAllColumnsShowFocus(false);

    horizontalLayout_2->addWidget(mp_gameListView);

    mp_playerListView = new QTreeWidget(JoinGameDialog);
    mp_playerListView->setObjectName(QString::fromUtf8("mp_playerListView"));
    mp_playerListView->setFocusPolicy(Qt::NoFocus);
    mp_playerListView->setEditTriggers(QAbstractItemView::EditKeyPressed);
    mp_playerListView->setAlternatingRowColors(true);
    mp_playerListView->setSelectionMode(QAbstractItemView::NoSelection);
    mp_playerListView->setIndentation(15);
    mp_playerListView->setRootIsDecorated(false);
    mp_playerListView->setItemsExpandable(false);
    mp_playerListView->setSortingEnabled(false);
    mp_playerListView->setAnimated(true);
    mp_playerListView->setAllColumnsShowFocus(false);

    horizontalLayout_2->addWidget(mp_playerListView);


    verticalLayout->addLayout(horizontalLayout_2);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    mp_refreshButton = new QPushButton(JoinGameDialog);
    mp_refreshButton->setObjectName(QString::fromUtf8("mp_refreshButton"));

    horizontalLayout->addWidget(mp_refreshButton);

    mp_playButton = new QPushButton(JoinGameDialog);
    mp_playButton->setObjectName(QString::fromUtf8("mp_playButton"));

    horizontalLayout->addWidget(mp_playButton);

    mp_spectateButton = new QPushButton(JoinGameDialog);
    mp_spectateButton->setObjectName(QString::fromUtf8("mp_spectateButton"));

    horizontalLayout->addWidget(mp_spectateButton);

    mp_cancelButton = new QPushButton(JoinGameDialog);
    mp_cancelButton->setObjectName(QString::fromUtf8("mp_cancelButton"));

    horizontalLayout->addWidget(mp_cancelButton);


    verticalLayout->addLayout(horizontalLayout);


    retranslateUi(JoinGameDialog);
    QObject::connect(mp_cancelButton, SIGNAL(clicked()), JoinGameDialog, SLOT(close()));

    QMetaObject::connectSlotsByName(JoinGameDialog);
    } // setupUi

    void retranslateUi(QDialog *JoinGameDialog)
    {
    JoinGameDialog->setWindowTitle(QApplication::translate("JoinGameDialog", "Join Game", 0, QApplication::UnicodeUTF8));
    mp_gameListView->headerItem()->setText(0, QApplication::translate("JoinGameDialog", "Game", 0, QApplication::UnicodeUTF8));
    mp_gameListView->headerItem()->setText(1, QApplication::translate("JoinGameDialog", "State", 0, QApplication::UnicodeUTF8));
    mp_gameListView->headerItem()->setText(2, QApplication::translate("JoinGameDialog", "Players", 0, QApplication::UnicodeUTF8));
    mp_playerListView->headerItem()->setText(0, QApplication::translate("JoinGameDialog", "Player", 0, QApplication::UnicodeUTF8));
    mp_refreshButton->setText(QApplication::translate("JoinGameDialog", "Refresh", 0, QApplication::UnicodeUTF8));
    mp_playButton->setText(QApplication::translate("JoinGameDialog", "Play", 0, QApplication::UnicodeUTF8));
    mp_spectateButton->setText(QApplication::translate("JoinGameDialog", "Spectate", 0, QApplication::UnicodeUTF8));
    mp_cancelButton->setText(QApplication::translate("JoinGameDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(JoinGameDialog);
    } // retranslateUi

};

namespace Ui {
    class JoinGameDialog: public Ui_JoinGameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINGAMEDIALOG_H
