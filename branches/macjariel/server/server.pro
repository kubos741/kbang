HEADERS += abstractplayerctrl.h \
gamearbiter.h \
abstractcard.h \
charactercard.h \
player.h \
playingcard.h \
weaponcard.h \
 gameserver.h \
 game.h \
 gamestarter.h \
 console.h \
 consolecommand.h \
 client.h \
 tcpserver.h \
 common.h \
 config.h \
 publicgameview.h \
 playerctrlevents.h \
 publicplayerview.h \
 privateplayerview.h \
 playercontrollerrunner.h \
 playeractions.h
SOURCES += main.cpp \
gamearbiter.cpp \
charactercard.cpp \
player.cpp \
weaponcard.cpp \
playingcard.cpp \
 gameserver.cpp \
 game.cpp \
 gamestarter.cpp \
 console.cpp \
 consolecommand.cpp \
 client.cpp \
 tcpserver.cpp \
 config.cpp \
 common.cpp \
 publicgameview.cpp \
 abstractplayerctrl.cpp \
 playerctrlevents.cpp \
 publicplayerview.cpp \
 privateplayerview.cpp \
 playercontrollerrunner.cpp \
 playeractions.cpp
TEMPLATE = app

CONFIG -= release

CONFIG += debug

QT += xml \
network
INCLUDEPATH += ../common

LIBS += ../common/libcommon.a

TARGETDEPS += ../common/libcommon.a

