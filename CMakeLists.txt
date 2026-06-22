cmake_minimum_required(VERSION 3.10)

project(CMakeTesting)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "C:/Qt/6.11.1/msvc2022_64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    src/private/MainWindow.cpp
    src/private/Database/Database.cpp
 "src/private/Content/Content.cpp" 
 "src/private/Content/ContentHeaderWidget.cpp" 
 "src/private/Invoice/InvoiceWidget.cpp" 
 "src/private/Content/AddContentWidget.cpp"
 "src/private/Content/EditContentWidget.cpp")

set(HEADERS
    src/public/MainWindow.h
    src/public/Database/Database.h
 "src/public/Content/Content.h" 
 "src/public/Content/ContentHeaderWidget.h" 
 "src/public/Invoice/InvoiceWidget.h" 
 "src/public/Invoice.h" 
 "src/public/Content/AddContentWidget.h"
 "src/public/Content/EditContentWidget.h")

add_executable(CMakeTesting ${SOURCES} ${HEADERS})

target_include_directories(CMakeTesting PRIVATE 
    src/public/
    libs/sqlite
)

target_link_libraries(CMakeTesting PRIVATE
    Qt6::Widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/sqlite/sqlite3.lib
)

 add_custom_command(TARGET CMakeTesting POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/sqlite/sqlite3.dll
    $<TARGET_FILE_DIR:CMakeTesting>
)
