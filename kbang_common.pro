TEMPLATE = lib
UI_DIR = uics/common
MOC_DIR = mocs/common
OBJECTS_DIR = obj/common
CONFIG += staticlib
CONFIG += debug

# CONFIG += release
QT += xml
QT += network
INCLUDEPATH += src/common
HEADERS += src/common/debug/debugblock.h \
    src/common/parser/gameeventparser.h \
    src/common/parser/gamestructparser.h \
    src/common/parser/ioproxy.h \
    src/common/parser/parser.h \
    src/common/parser/servereventparser.h \
    src/common/parser/queryget.h \
    src/common/parser/queryresult.h \
    src/common/parser/xmlnode.h \
    src/common/config.h \
    src/common/gameactions.h \
    src/common/gameevents.h \
    src/common/gametypes.h \
    src/common/gamestructs.h \
    src/common/serverevents.h \
    src/common/util.h \
    src/common/tar/tar.h
SOURCES += src/common/parser/servereventparser.cpp \
    src/common/debug/debugblock.cpp \
    src/common/parser/gameeventparser.cpp \
    src/common/parser/ioproxy.cpp \
    src/common/parser/parser.cpp \
    src/common/parser/queryget.cpp \
    src/common/parser/queryresult.cpp \
    src/common/parser/xmlnode.cpp \
    src/common/config.cpp \
    src/common/gameevents.cpp \
    src/common/gametypes.cpp \
    src/common/gamestructs.cpp \
    src/common/serverevents.cpp \
    src/common/util.cpp \
    src/common/parser/gamestructparser.cpp \
    src/common/tar/tar.cpp
TARGET = lib/kbang_common
QMAKE_CXXFLAGS_DEBUG += -Wall
