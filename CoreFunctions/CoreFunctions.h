//
// Created by yashmathur on 5/20/25.
//

#ifndef COREFUNCTIONS_H
#define COREFUNCTIONS_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

/*************************** GAME CONFIG **********************************/

// Map
#define MAP_TILE_SIZE 2048

// Player
#define PLAYER_MAX_SPEED 2000
#define BULLET_SPEED 2500

// Spaceships
#define ROTATION_SPEED 200
#define ACCELERATION 500
#define DRAG 0.1f

// Player Bullets
#define MAX_BULLETS 50
#define BULLET_DEBOUNCE 5
#define TIME_TO_LIVE 5
#define BULLET_DAMAGE 1

// Asteroids
#define NUMBER_OF_ASTEROIDS_LEVEL1 20
#define NUMBER_OF_ASTEROIDS_LEVEL2 70
#define NUMBER_OF_ASTEROIDS_LEVEL3 150

/*************************************************************************/


extern sf::Vector2f windowSize; // = sf::Vector2f(800, 600);

void initWindow(sf::RenderWindow& window);
void initGame();

extern int debouncer;


extern sf::Texture bulletTexture;
extern sf::Texture asteroidTexture;



#endif //COREFUNCTIONS_H
