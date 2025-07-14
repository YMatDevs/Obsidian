//
// Created by yashmathur on 5/18/25.
//

#ifndef ASTEROID_H
#define ASTEROID_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Asteroid
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed = 100.0f;      // Pixels per second
    float rotationSpeed = 45.0f; // Degrees per second

public:
    Asteroid();

    void update(float deltaTime);  // deltaTime = time since last frame
    const sf::FloatRect getBounds() const;  // For collision
};


#endif //ASTEROID_H
