cmake_minimum_required(VERSION 3.16)

project(CS1D_baseball VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Sql)

# Add GoogleTest
enable_testing()
add_subdirectory(googletest)  # assumes googletest is in subdirectory
include(GoogleTest)

set(PROJECT_SOURCES
    main.cpp
    loginwindow.cpp
    loginwindow.h
    loginwindow.ui
    mergedtableview.h
    mergedtableview.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CS1D_baseball
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        logos.qrc
        mainmenu.h mainmenu.cpp mainmenu.ui
        teamdisplay.h teamdisplay.cpp teamdisplay.ui
        plantour.ui
        plantour.h
        plantour.cpp
        reguser.ui
        reguser.h
        reguser.cpp
        utility.h utility.cpp
        main.h
        db.h db.cpp
        displayteams.h displayteams.cpp displayteams.ui
        displaystadiums.ui
        displaystadiums.h
        displaystadiums.cpp
        maintenance.ui
        maintenance.h
        maintenance.cpp
        mapdisp.h mapdisp.cpp mapdisp.ui
        tripdisplay.cpp tripdisplay.h tripdisplay.ui
        teamselectdialog.h
        mergedtableview.h
        mergedtableview.cpp
        purchasesouvenirs.cpp purchasesouvenirs.h purchasesouvenirs.ui
        #souvenirdialog.cpp souvenirdialog.h
    )

    target_include_directories(CS1D_baseball PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

else()
    if(ANDROID)
        add_library(CS1D_baseball SHARED ${PROJECT_SOURCES})
    else()
        add_executable(CS1D_baseball ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(CS1D_baseball PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Sql Qt6::Core)

set_target_properties(CS1D_baseball PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CS1D_baseball
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CS1D_baseball
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CS1D_baseball)
endif()

# -------------------------------
# GoogleTest Unit Test Section
# -------------------------------
# Add your test source file(s) here
add_executable(baseball_tests
    tests/test_main.cpp
    #tests/test_graph.cpp
    # add more test files as needed
)

target_include_directories(baseball_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(baseball_tests
    GTest::gtest_main
    GTest::gmock_main
)

gtest_discover_tests(baseball_tests)
