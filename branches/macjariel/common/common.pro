TEMPLATE     = lib
CONFIG      += staticlib
QT          += xml 
INCLUDEPATH += testparser

##########
# PARSER #
##########

HEADERS += parser/parser.h \
           parser/parserstructs.h \
           parser/queryget.h \
           parser/queryresult.h \
           parser/xmlnode.h

SOURCES += parser/parser.cpp \
           parser/queryget.cpp \
           parser/queryresult.cpp \
           parser/xmlnode.cpp


########
# MISC #
########

HEADERS += util.h

SOURCES += util.cpp


