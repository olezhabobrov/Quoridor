cmake_minimum_required(VERSION 3.5)

project(Quoridor)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(include)
#include_directories(Forms)

add_executable(Quoridor
        include/Types.h
        include/TitleScreen.h
        include/GameField.h
        include/Controller.h
        src/main.cpp
        src/TitleScreen.cpp
        src/TitleScreen.ui
        src/GameField.cpp
        src/GameField.ui
        src/Controller.cpp
)

target_link_libraries(Quoridor Qt5::Widgets)
