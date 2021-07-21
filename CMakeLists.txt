cmake_minimum_required(VERSION 3.5)

project(Quoridor)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC_SEARCH_PATHS include)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(include)

add_compile_options(-lstdc++)


add_executable(Quoridor
        include/mainwindow.h
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.ui
)

target_link_libraries(Quoridor Qt5::Widgets)
