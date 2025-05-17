#include <optional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include <iostream>
#include <string>


#include "Sprites/Player/PlayerRocket.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Obsidian");

    window.setFramerateLimit(60);

    PlayerRocket playerRocket("Fighter");

    sf::Clock clock;
    clock.restart();

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event)) { if (event.type == sf::Event::Closed) { window.close(); } }

        float deltaTime = clock.restart().asSeconds();

        float x = 0.0f;
        float y = 0.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) y -= deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) y += deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x -= deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x += deltaTime;

        playerRocket.move(0, y);
        playerRocket.rotate(x);




        window.clear(sf::Color::Black);

        window.draw(playerRocket.sprite);

        window.display();
    }
    return 0;
}