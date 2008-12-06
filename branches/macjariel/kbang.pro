
TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += common \
           server \
           servertester \
    	   tests/testparser \
	   client
