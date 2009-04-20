TEMPLATE = lib
CONFIG += staticlib \
    debug
QT += xml

# #########
# PARSER #
# #########
HEADERS += parser/ioproxy.h \
    parser/parser.h \
    parser/parserstructs.h \
    parser/queryget.h \
    parser/queryresult.h \
    parser/xmlnode.h
SOURCES += parser/ioproxy.cpp \
    parser/parser.cpp \
    parser/parserstructs.cpp \
    parser/queryget.cpp \
    parser/queryresult.cpp \
    parser/xmlnode.cpp

# #######
# MISC #
# #######
HEADERS += util.h
SOURCES += util.cpp
CONFIG -= release
QMAKE_CXXFLAGS_DEBUG += -Wall
