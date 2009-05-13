HEADERS += player.h \
    gameserver.h \
    game.h \
    console.h \
    consolecommand.h \
    client.h \
    tcpserver.h \
    common.h \
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
    cardfactory.h \
    carddrawcards.h \
    cardmultishoot.h \
    cardduel.h \
    cardgeneralstore.h \
    cardjail.h \
    reactionhandler.h \
    carddynamite.h \
    cardtaker.h \
    cardbarrel.h \
    gameeventbroadcaster.h \
    gamelogger.h \
    characterbase.h \
    charactercalamityjanet.h \
    characterblackjack.h \
    characterlist.h \
    charactercassidygringo.h \
    charactersuzylafayette.h \
    characterpropertychange.h \
    characterjourdonnais.h \
    characterpedroramirez.h \
    characterjessejones.h \
    charactersidketchum.h \
    characterkitcarlson.h \
    playerreaper.h \
    charactervulturesam.h \
    checkdeckresulthandler.h \
    characterluckyduke.h
SOURCES += main.cpp \
    player.cpp \
    gameserver.cpp \
    game.cpp \
    console.cpp \
    consolecommand.cpp \
    client.cpp \
    tcpserver.cpp \
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
    cardfactory.cpp \
    carddrawcards.cpp \
    cardmultishoot.cpp \
    cardduel.cpp \
    cardgeneralstore.cpp \
    cardjail.cpp \
    reactionhandler.cpp \
    carddynamite.cpp \
    cardtaker.cpp \
    cardbarrel.cpp \
    gameeventbroadcaster.cpp \
    gamelogger.cpp \
    characterbase.cpp \
    charactercalamityjanet.cpp \
    characterblackjack.cpp \
    characterlist.cpp \
    charactercassidygringo.cpp \
    charactersuzylafayette.cpp \
    characterpropertychange.cpp \
    characterjourdonnais.cpp \
    characterpedroramirez.cpp \
    characterjessejones.cpp \
    charactersidketchum.cpp \
    characterkitcarlson.cpp \
    playerreaper.cpp \
    charactervulturesam.cpp \
    characterluckyduke.cpp
TEMPLATE = app
CONFIG -= release
CONFIG += debug
QT += xml \
    network
INCLUDEPATH += ../common
LIBS += ../common/libcommon.a
TARGETDEPS += ../common/libcommon.a
QMAKE_CXXFLAGS_DEBUG += -Wall
