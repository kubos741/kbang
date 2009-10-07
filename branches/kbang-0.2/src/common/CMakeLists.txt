

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(common_SRCS
        config.cpp
		gameevents.cpp
        gametypes.cpp
        serverevents.cpp
        queries.cpp
        util.cpp
        parser/actionparser.cpp
        parser/gameeventparser.cpp
        parser/gamestructparser.cpp
        parser/servereventparser.cpp
        parser/querygetparser.cpp
        parser/parser.cpp
        parser/xmlnode.cpp
        parser/ioproxy.cpp
        debug/debugblock.cpp
)


SET(common_HEADERS
        common.h
    #        tar/tar.h
        parser/querygetparser.h
        parser/servereventparser.h
        parser/actionparser.h
        parser/gameeventparser.h
        parser/ioproxy.h
        parser/gamestructparser.h
        parser/parser.h
        parser/xmlnode.h
        parser/datastreammanager.h
        debug/debugblock.h
        queries.h
        gamestructs.h
        serverevents.h
        gametypes.h
        gameactions.h
        gameevents.h
        config.h
        util.h
        actions.h
)



QT4_WRAP_CPP(common_MOC_SRCS ${common_HEADERS})


ADD_LIBRARY(kbang-common ${common_SRCS} ${common_MOC_SRCS} ${common_HEADERS})

#ADD_PRECOMPILED_HEADER(kbang-common ${CMAKE_CURRENT_SOURCE_DIR}/common.h)
