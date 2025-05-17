cmake_minimum_required(VERSION 3.31)
project(Obsidian)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Obsidian main.cpp
        Controls/Control.cpp
        Controls/Control.h
        Sprites/Player/PlayerRocket.cpp
        Sprites/Player/PlayerRocket.h
)

target_link_libraries(Obsidian sfml-graphics sfml-window sfml-system)
