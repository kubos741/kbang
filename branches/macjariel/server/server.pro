HEADERS += charactercard.h \
    player.h \
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
    cards.h \
    gamecycle.h \
    gameexceptions.h \
    gameinfo.h \
    gametable.h \
    playerctrl.h \
    gameeventhandler.h \
    voidai.h
SOURCES += main.cpp \
    charactercard.cpp \
    player.cpp \
    gameserver.cpp \
    game.cpp \
    console.cpp \
    consolecommand.cpp \
    client.cpp \
    tcpserver.cpp \
    config.cpp \
    common.cpp \
    publicgameview.cpp \
    publicplayerview.cpp \
    privateplayerview.cpp \
    cardabstract.cpp \
    cardplayable.cpp \
    cardbang.cpp \
    cardmissed.cpp \
    gamecycle.cpp \
    gameinfo.cpp \
    gametable.cpp \
    playerctrl.cpp \
    voidai.cpp \
    gameeventhandler.cpp
TEMPLATE = app
CONFIG -= release
CONFIG += debug
QT += xml \
    network
INCLUDEPATH += ../common
LIBS += ../common/libcommon.a
TARGETDEPS += ../common/libcommon.a
QMAKE_CXXFLAGS_DEBUG += -Wall
