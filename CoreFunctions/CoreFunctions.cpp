//
// Created by yashmathur on 5/20/25.
//

#include "CoreFunctions.h"

#include <SFML/Graphics/RenderWindow.hpp>


sf::Vector2f windowSize = sf::Vector2f(800, 600);
int debouncer = 0;


void initWindow(sf::RenderWindow& window) {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(desktop, "Obsidian", sf::Style::Default);
    window.setFramerateLimit(60);
    windowSize = sf::Vector2f(window.getSize());
    debouncer = 0;
}

sf::Texture bulletTexture;
sf::Texture asteroidTexture;