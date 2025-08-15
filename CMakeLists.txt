cmake_minimum_required(VERSION 3.31)
project(Obsidian)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")

# Force static linking of the C++ runtime
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

# Make sure MinGW can find SFML's static libraries
set(SFML_STATIC_LIBRARIES TRUE)

# Optional: turn on Release mode if not already set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()




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
        Sprites/Hitbox/Hitbox.cpp
        Sprites/Hitbox/Hitbox.h
)

target_link_libraries(Obsidian sfml-graphics sfml-window sfml-system )

