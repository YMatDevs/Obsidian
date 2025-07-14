//
// Created by yashmathur on 5/20/25.
//

#ifndef COREFUNCTIONS_H
#define COREFUNCTIONS_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>


// Game Constants
#define MAP_TILE_SIZE 2048
#define PLAYER_MAX_SPEED 2000
#define BULLET_SPEED 2500

extern sf::Vector2f windowSize; // = sf::Vector2f(800, 600);

void initWindow(sf::RenderWindow& window);

extern int debouncer;


extern sf::Texture bulletTexture;
extern sf::Texture asteroidTexture;



#endif //COREFUNCTIONS_H
