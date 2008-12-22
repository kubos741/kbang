HEADERS += abstractplayerctrl.h \
abstractcard.h \
charactercard.h \
player.h \
playingcard.h \
weaponcard.h \
 gameserver.h \
 game.h \
 console.h \
 consolecommand.h \
 client.h \
 tcpserver.h \
 common.h \
 config.h \
 publicgameview.h \
 publicplayerview.h \
 privateplayerview.h \
 cardabstract.h \
 cardplayable.h \
 cardbang.h \
 cardmissed.h \
 cards.h
SOURCES += main.cpp \
charactercard.cpp \
player.cpp \
weaponcard.cpp \
playingcard.cpp \
 gameserver.cpp \
 game.cpp \
 console.cpp \
 consolecommand.cpp \
 client.cpp \
 tcpserver.cpp \
 config.cpp \
 common.cpp \
 publicgameview.cpp \
 abstractplayerctrl.cpp \
 publicplayerview.cpp \
 privateplayerview.cpp \
 cardabstract.cpp \
 cardplayable.cpp \
 cardbang.cpp \
 cardmissed.cpp
TEMPLATE = app

CONFIG -= release

CONFIG += debug

QT += xml \
network
INCLUDEPATH += ../common

LIBS += ../common/libcommon.a

TARGETDEPS += ../common/libcommon.a

QMAKE_CXXFLAGS_DEBUG += -Wall
