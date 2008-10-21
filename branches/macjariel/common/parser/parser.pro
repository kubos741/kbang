HEADERS += 
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
 playeractions.cpp \
 clientcontroller.cpp
TEMPLATE = app

CONFIG -= release

CONFIG += debug

QT += xml \
network
