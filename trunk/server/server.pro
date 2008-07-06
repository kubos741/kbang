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
 consolecommand.h \
 client.h \
 tcpserver.h \
 clientxmlparser.h \
 stanza.h \
 common.h \
 stanzaquery.h \
 config.h \
 stanzaaction.h
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
 consolecommand.cpp \
 client.cpp \
 tcpserver.cpp \
 clientxmlparser.cpp \
 stanza.cpp \
 stanzaquery.cpp \
 config.cpp \
 stanzaaction.cpp
TEMPLATE = app

CONFIG -= release

CONFIG += debug

QT += xml \
network
