HEADERS += queryget.h \
	   parser.h \
	   parserstructs.h \
	   queryresult.h \
	   ../util.h \
	   testparser/testparser.h \
	   testparser/mocksocket.h \
	   xmlnode.h

SOURCES += parser.cpp \
	   queryget.cpp \
	   queryresult.cpp \
	   ../util.cpp \
	   testparser/testparser.cpp \
	   testparser/mocksocket.cpp \
	   xmlnode.cpp

TEMPLATE = app

QT += xml 

CONFIG += qtestlib

     

INCLUDEPATH += .. \
               testparser

