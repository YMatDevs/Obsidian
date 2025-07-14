//
// Created by yashmathur on 6/8/25.
//

#include "Enemy.h"

Enemy::Enemy(const std::string choice) : Spaceship(5000, sf::Vector2f (4096.0f, 4096.0f), choice)
{
    currentHealth = 0;
}
