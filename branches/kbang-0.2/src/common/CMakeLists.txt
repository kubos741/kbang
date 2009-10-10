

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
        parser/simpletypeparser.h
        debug/debugblock.h
        queries.h
        gamestructs.h
        serverevents.h
        gametypes.h
        gameevents.h
        config.h
        util.h
        actions.h
)

SET(common_COG
    actions.h
    gamestructs.h
    parser/actionparser.cpp
    parser/actionparser.h
    parser/gamestructparser.h
    parser/gamestructparser.cpp
)

SET(COG_COMMAND cog.py)
SET(COG_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../cog)

ADD_CUSTOM_TARGET(Cog ALL ${COG_COMMAND} -r -I ${COG_INCLUDE} ${common_COG}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)



QT4_WRAP_CPP(common_MOC_SRCS ${common_HEADERS})


ADD_LIBRARY(kbang-common ${common_SRCS} ${common_MOC_SRCS} ${common_HEADERS})

#ADD_PRECOMPILED_HEADER(kbang-common ${CMAKE_CURRENT_SOURCE_DIR}/common.h)
