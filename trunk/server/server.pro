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
 clientxmlparser.h \
 stanza.h \
 common.h \
 stanzaquery.h \
 config.h \
 stanzaaction.h \
 publicgameview.h \
 clientplayerctrl.h \
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
 clientxmlparser.cpp \
 stanza.cpp \
 stanzaquery.cpp \
 config.cpp \
 stanzaaction.cpp \
 common.cpp \
 publicgameview.cpp \
 clientplayerctrl.cpp \
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
