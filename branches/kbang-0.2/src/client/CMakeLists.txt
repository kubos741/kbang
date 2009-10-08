

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cards
    ${CMAKE_CURRENT_SOURCE_DIR}/dialogs
    ${CMAKE_CURRENT_SOURCE_DIR}/events
    ${CMAKE_CURRENT_SOURCE_DIR}/managers
    ${CMAKE_CURRENT_SOURCE_DIR}/options
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
    ${CMAKE_CURRENT_BINARY_DIR}
)



SET(client_SRCS
        serverconnection.cpp
        game.cpp
        textformatter.cpp
        dialogs/aboutdialog.cpp
        dialogs/newserverdialog.cpp
        dialogs/creategamedialog.cpp
        dialogs/connecttoserverdialog.cpp
        dialogs/joingamedialog.cpp
        main.cpp
        cards/cardsetmanager.cpp
        cards/cardsetinfo.cpp
        cards/cardbank.cpp
        cards/card.cpp
        managers/gameactionmanager.cpp
        managers/cardwidgetsizemanager.cpp
        events/gameeventhandler.cpp
        events/setplayerscmd.cpp
        events/gameeventplayer.cpp
        events/cardmovementcmd.cpp
        events/gameeventcmd.cpp
        events/gameeventqueue.cpp
        events/gameevent.cpp
        events/gamecontextcmd.cpp
        mainwindow.cpp
        options/optionstab.cpp
        options/optionsdialog.cpp
        options/opt_cardsets.cpp
        widgets/graveyardwidget.cpp
        widgets/chatwidget.cpp
        widgets/cardwidget.cpp
        widgets/cardpilewidget.cpp
        widgets/logwidget.cpp
        widgets/deckwidget.cpp
        widgets/playerwidget.cpp
        widgets/cardzoomwidget.cpp
        widgets/selectavatarwidget.cpp
        widgets/localplayerwidget.cpp
        widgets/cardpocket.cpp
        widgets/opponentwidget.cpp
        widgets/characterwidget.cpp
        widgets/cardlistwidget.cpp
)

SET(client_HEADERS
        dialogs/creategamedialog.h
        dialogs/connecttoserverdialog.h
        dialogs/aboutdialog.h
        dialogs/joingamedialog.h
        dialogs/newserverdialog.h
        cards/cardsetmanager.h
        cards/card.h
        cards/cardsetinfo.h
        cards/cardbank.h
        serverconnection.h
        managers/gameactionmanager.h
        managers/cardwidgetsizemanager.h
        clienttypes.h
        game.h
        events/gameevent.h
        events/setplayerscmd.h
        events/gameeventhandler.h
        events/gamecontextcmd.h
        events/cardmovementcmd.h
        events/gameeventcmd.h
        events/gameeventplayer.h
        events/gameeventqueue.h
        options/opt_cardsets.h
        options/optionstab.h
        options/optionsdialog.h
        mainwindow.h
        widgets/playerwidget.h
        widgets/cardpocket.h
        widgets/opponentwidget.h
        widgets/deckwidget.h
        widgets/logwidget.h
        widgets/graveyardwidget.h
        widgets/cardpilewidget.h
        widgets/cardzoomwidget.h
        widgets/characterwidget.h
        widgets/selectavatarwidget.h
        widgets/cardlistwidget.h
        widgets/localplayerwidget.h
        widgets/chatwidget.h
        widgets/cardwidget.h
        textformatter.h
) 

SET(client_UI
        dialogs/aboutdialog.ui
        dialogs/newserverdialog.ui
        dialogs/connecttoserverdialog.ui
        dialogs/joingamedialog.ui
        dialogs/creategamedialog.ui
        options/opt_cardsets.ui
        options/optionsdialog.ui
        widgets/logwidget.ui
        widgets/localplayerwidget.ui
        widgets/chatwidget.ui
        widgets/opponentwidget.ui
        mainwindow.ui
)

QT4_WRAP_CPP(client_MOC_SRCS ${client_HEADERS})
QT4_WRAP_UI(client_UI_HEADERS ${client_UI})

ADD_EXECUTABLE(kbang-client ${client_SRCS} ${client_MOC_SRCS}
    ${client_HEADERS} ${client_UI_HEADERS})

TARGET_LINK_LIBRARIES(kbang-client kbang-common ${QT_LIBRARIES})

