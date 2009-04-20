HEADERS += player.h \
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
    playingcard.h \
    reactioncard.h \
    tablecard.h \
    weaponcard.h \
    cardbang.h \
    cardmissed.h \
    cards.h \
    gamecycle.h \
    gameexceptions.h \
    gameinfo.h \
    gametable.h \
    playerctrl.h \
    gameeventhandler.h \
    voidai.h \
    cardbeer.h \
    cardhorse.h \
    cardfactory.h
SOURCES += main.cpp \
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
    playingcard.cpp \
    reactioncard.cpp \
    tablecard.cpp \
    weaponcard.cpp \
    cardbang.cpp \
    cardmissed.cpp \
    gamecycle.cpp \
    gameinfo.cpp \
    gametable.cpp \
    playerctrl.cpp \
    voidai.cpp \
    gameeventhandler.cpp \
    cardbeer.cpp \
    cardhorse.cpp \
    cardfactory.cpp
TEMPLATE = app
CONFIG -= release
CONFIG += debug
QT += xml \
    network
INCLUDEPATH += ../common
LIBS += ../common/libcommon.a
TARGETDEPS += ../common/libcommon.a
QMAKE_CXXFLAGS_DEBUG += -Wall
