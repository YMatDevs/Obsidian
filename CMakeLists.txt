cmake_minimum_required(VERSION 3.31)
project(Obsidian)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Obsidian main.cpp
        Sprites/Player/Player.cpp
        Sprites/Player/Player.h
        SpaceMap/SpaceMap.cpp
        SpaceMap/SpaceMap.h
        Minimap/MiniMap.cpp
        Minimap/MiniMap.h
        Sprites/Asteroid/Asteroid.cpp
        Sprites/Asteroid/Asteroid.h
        Sprites/Spaceships/Spaceship.cpp
        Sprites/Spaceships/Spaceship.h
        CoreFunctions/CoreFunctions.cpp
        CoreFunctions/CoreFunctions.h
        Screens/Screen.cpp
        Screens/Screen.h
        Sprites/Bullet/Bullets.cpp
        Sprites/Bullet/Bullets.h
        Sprites/Enemy/Enemy.cpp
        Sprites/Enemy/Enemy.h
)

target_link_libraries(Obsidian sfml-graphics sfml-window sfml-system)
