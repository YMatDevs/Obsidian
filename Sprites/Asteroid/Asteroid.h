//
// Created by yashmathur on 5/18/25.
//

#ifndef ASTEROID_H
#define ASTEROID_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../../CoreFunctions/CoreFunctions.h"

class Asteroid
{
private:
    sf::Texture texture;

    // float speed;      // Pixels per second
    float rotationSpeed; // Degrees per second
    // float angleDeg;
    // float angleRad;
    sf::Vector2f velocity;
    int health;

public:
    sf::Sprite sprite;
    float collisionShrink;
    Asteroid(sf::Vector2f playerPos, float spawnMinDistance, float spawnMaxDistance);
    void takeDamage();
    void update(float deltaTime);  // deltaTime = time since last frame
    const sf::FloatRect getBounds() const;  // For collision
};

#endif //ASTEROID_H
