cmake_minimum_required(VERSION 3.10)

project(CMakeTesting)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "C:/Qt/6.10.1/msvc2022_64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(CMakeTesting main.cpp  
    # Headers
    src/public/MainWindow.h
    src/public/Buttons/MainButton.h
    src/public/Buttons/AddButton.h
    src/public/Database/Database.h
    # Source files
    src/private/MainWindow.cpp
    src/private/Buttons/MainButton.cpp
    src/private/Buttons/AddButton.cpp 
    src/private/Database/Database.cpp "src/private/Sidebar/Sidebar.cpp" "src/public/Sidebar/Sidebar.h")

target_include_directories(CMakeTesting PRIVATE 
    src/public/
    libs/sqlite
)

target_link_libraries(CMakeTesting PRIVATE
    Qt6::Widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/sqlite/sqlite3.lib
)