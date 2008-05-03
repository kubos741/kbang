HEADERS += abstractplayerctrl.h \
gamearbiter.h \
abstractcard.h \
charactercard.h \
player.h \
playingcard.h \
weaponcard.h \
 gameserver.h \
 gamestate.h \
 gamestarter.h \
 console.h \
 consolecommand.h
SOURCES += main.cpp \
gamearbiter.cpp \
charactercard.cpp \
player.cpp \
weaponcard.cpp \
playingcard.cpp \
 gameserver.cpp \
 gamestate.cpp \
 gamestarter.cpp \
 console.cpp \
 consolecommand.cpp
TEMPLATE = app

CONFIG -= release

CONFIG += debug

