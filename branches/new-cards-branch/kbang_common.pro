TEMPLATE = lib
UI_DIR = uics/common
MOC_DIR = mocs/common
OBJECTS_DIR = obj/common
CONFIG += staticlib
CONFIG += debug
#CONFIG += release

QT += xml
QT += network

INCLUDEPATH += src/common
HEADERS += src/common/parser/ioproxy.h \
    src/common/parser/parser.h \
    src/common/parser/queryget.h \
    src/common/parser/queryresult.h \
    src/common/parser/xmlnode.h \
    src/common/config.h \
    src/common/util.h \
    src/common/gametypes.h \
    src/common/gamestructs.h \
	src/common/debug/debugblock.h

	
SOURCES += src/common/parser/ioproxy.cpp \
    src/common/parser/parser.cpp \
    src/common/parser/queryget.cpp \
    src/common/parser/queryresult.cpp \
    src/common/parser/xmlnode.cpp \
    src/common/config.cpp \
    src/common/util.cpp \
    src/common/gametypes.cpp \
    src/common/gamestructs.cpp \
	src/common/debug/debugblock.cpp

	
TARGET = lib/kbang_common
QMAKE_CXXFLAGS_DEBUG += -Wall
