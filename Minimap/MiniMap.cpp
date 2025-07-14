//
// Created by yashmathur on 5/17/25.
//

#include "MiniMap.h"


MiniMap::MiniMap(sf::Vector2f windowSize, sf::Vector2f mapSize)
{
    this->rectangle.setSize(sf::Vector2f(windowSize.x * 0.25f, windowSize.y * 0.25f));
    this->rectangle.setFillColor(sf::Color::Transparent);
    this->rectangle.setOutlineColor(sf::Color::White);
    this->rectangle.setOutlineThickness(2.0f);
    this->rectangle.setPosition(windowSize.x * 0.75f, 0);  // Offset if you want space

    this->view.setSize(mapSize);  // Show entire world on minimap
    this->view.setCenter(mapSize.x / 2.0f, mapSize.y / 2.0f);
    this->view.setViewport(sf::FloatRect(0.75f, 0.0f, 0.25f, 0.25f));

    this->playerDot.setRadius(300.0f);
    this->playerDot.setFillColor(sf::Color::Green);
    this->playerDot.setOrigin(15, 15);  // center origin
}

