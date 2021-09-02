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

add_executable(Quoridor
        include/TitleScreen.h
        include/GameField.h
        include/Controller.h
        include/VictoryScreen.h
        src/main.cpp
        src/TitleScreen.cpp
        src/GameField.cpp
        src/Controller.cpp
        src/PathFinder.cpp
        src/VictoryScreen.cpp
        src/Bot.cpp
        src/OtherTypes.cpp
)

target_link_libraries(Quoridor Qt5::Widgets)
