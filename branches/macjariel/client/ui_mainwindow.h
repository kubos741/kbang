/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Sat Nov 8 21:35:22 2008
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *mp_actionConnectToServer;
    QAction *mp_actionExit;
    QAction *mp_actionDisconnectFromServer;
    QAction *mp_actionJoinGame;
    QAction *mp_actionLeaveGame;
    QAction *actionConfigure_Profile;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QFrame *mp_chatFrame;
    QSpacerItem *horizontalSpacer;
    QFrame *mp_playerFrame;
    QSpacerItem *horizontalSpacer_2;
    QFrame *mp_logFrame;
    QMenuBar *menubar;
    QMenu *menuGame;
    QMenu *menuTools;
    QStatusBar *mp_statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(818, 738);
    MainWindow->setAutoFillBackground(false);
    mp_actionConnectToServer = new QAction(MainWindow);
    mp_actionConnectToServer->setObjectName(QString::fromUtf8("mp_actionConnectToServer"));
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/images/icon-connect.svg")), QIcon::Normal, QIcon::Off);
    mp_actionConnectToServer->setIcon(icon);
    mp_actionExit = new QAction(MainWindow);
    mp_actionExit->setObjectName(QString::fromUtf8("mp_actionExit"));
    mp_actionDisconnectFromServer = new QAction(MainWindow);
    mp_actionDisconnectFromServer->setObjectName(QString::fromUtf8("mp_actionDisconnectFromServer"));
    mp_actionJoinGame = new QAction(MainWindow);
    mp_actionJoinGame->setObjectName(QString::fromUtf8("mp_actionJoinGame"));
    mp_actionLeaveGame = new QAction(MainWindow);
    mp_actionLeaveGame->setObjectName(QString::fromUtf8("mp_actionLeaveGame"));
    actionConfigure_Profile = new QAction(MainWindow);
    actionConfigure_Profile->setObjectName(QString::fromUtf8("actionConfigure_Profile"));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setAutoFillBackground(false);
    verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalSpacer = new QSpacerItem(258, 572, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    mp_chatFrame = new QFrame(centralwidget);
    mp_chatFrame->setObjectName(QString::fromUtf8("mp_chatFrame"));
    mp_chatFrame->setMinimumSize(QSize(150, 0));
    mp_chatFrame->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 15);"));
    mp_chatFrame->setFrameShape(QFrame::NoFrame);
    mp_chatFrame->setFrameShadow(QFrame::Raised);

    horizontalLayout->addWidget(mp_chatFrame);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    mp_playerFrame = new QFrame(centralwidget);
    mp_playerFrame->setObjectName(QString::fromUtf8("mp_playerFrame"));
    mp_playerFrame->setMinimumSize(QSize(200, 100));
    mp_playerFrame->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 15);"));
    mp_playerFrame->setFrameShadow(QFrame::Raised);

    horizontalLayout->addWidget(mp_playerFrame);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer_2);

    mp_logFrame = new QFrame(centralwidget);
    mp_logFrame->setObjectName(QString::fromUtf8("mp_logFrame"));
    mp_logFrame->setMinimumSize(QSize(150, 0));
    mp_logFrame->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 15);"));
    mp_logFrame->setFrameShadow(QFrame::Raised);

    horizontalLayout->addWidget(mp_logFrame);


    verticalLayout->addLayout(horizontalLayout);

    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 818, 26));
    menubar->setAutoFillBackground(false);
    menuGame = new QMenu(menubar);
    menuGame->setObjectName(QString::fromUtf8("menuGame"));
    menuTools = new QMenu(menubar);
    menuTools->setObjectName(QString::fromUtf8("menuTools"));
    MainWindow->setMenuBar(menubar);
    mp_statusbar = new QStatusBar(MainWindow);
    mp_statusbar->setObjectName(QString::fromUtf8("mp_statusbar"));
    MainWindow->setStatusBar(mp_statusbar);

    menubar->addAction(menuGame->menuAction());
    menubar->addAction(menuTools->menuAction());
    menuGame->addAction(mp_actionConnectToServer);
    menuGame->addAction(mp_actionDisconnectFromServer);
    menuGame->addSeparator();
    menuGame->addAction(mp_actionJoinGame);
    menuGame->addAction(mp_actionLeaveGame);
    menuGame->addAction(mp_actionExit);
    menuTools->addAction(actionConfigure_Profile);

    retranslateUi(MainWindow);
    QObject::connect(mp_actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    mp_actionConnectToServer->setText(QApplication::translate("MainWindow", "&Connect to Server", 0, QApplication::UnicodeUTF8));
    mp_actionExit->setText(QApplication::translate("MainWindow", "&Exit", 0, QApplication::UnicodeUTF8));
    mp_actionDisconnectFromServer->setText(QApplication::translate("MainWindow", "&Disconnect from Server", 0, QApplication::UnicodeUTF8));
    mp_actionJoinGame->setText(QApplication::translate("MainWindow", "&Join Game", 0, QApplication::UnicodeUTF8));
    mp_actionLeaveGame->setText(QApplication::translate("MainWindow", "&Leave Game", 0, QApplication::UnicodeUTF8));
    actionConfigure_Profile->setText(QApplication::translate("MainWindow", "Configure Profile", 0, QApplication::UnicodeUTF8));
    menuGame->setTitle(QApplication::translate("MainWindow", "Game", 0, QApplication::UnicodeUTF8));
    menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
