HEADERS += parser.h
SOURCES += parser.cpp
TEMPLATE = app

CONFIG -= release
CONFIG += debug

QT += xml \
      network
