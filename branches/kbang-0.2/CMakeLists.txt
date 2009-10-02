project(KBang)

cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_BUILD_TYPE release)

#set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH}
#                       ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/ )
                   
#include(PCHSupport_26)

option(BUILD_CLIENT "Builds client" ON)
option(BUILD_SERVER "Builds server" ON)


if(BUILD_CLIENT)
    find_package(Qt4 4.5.1 COMPONENTS QtCore QtGui QtXml QtNetwork REQUIRED)
else(BUILD_CLIENT)
    find_package(Qt4 4.5.1 COMPONENTS QtCore QtXml QtNetwork REQUIRED)
endif(BUILD_CLIENT)
include(${QT_USE_FILE})

add_subdirectory(src/common)

if(BUILD_CLIENT)
    add_subdirectory(src/client)
endif(BUILD_CLIENT)

if (BUILD_SERVER)

endif (BUILD_SERVER)
