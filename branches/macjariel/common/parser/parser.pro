HEADERS += queryget.h \
	   parser.h \
	parserstructs.h \
queryresult.h \
util.h
SOURCES += parser.cpp \
queryget.cpp \
queryresult.cpp \
util.cpp
TEMPLATE = app

QT += xml

INCLUDEPATH += ..

