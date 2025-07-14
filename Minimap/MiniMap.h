//
// Created by yashmathur on 5/17/25.
//

#ifndef MINIMAP_H
#define MINIMAP_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>

class MiniMap
{

    public:
    sf::View view;
    sf::RectangleShape rectangle;
    sf::CircleShape playerDot;

    MiniMap(sf::Vector2f windowSize, sf::Vector2f mapSize);
};

#endif //MINIMAP_H
