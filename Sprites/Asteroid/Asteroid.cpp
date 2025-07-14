//
// Created by yashmathur on 5/18/25.
//

#include "Asteroid.h"

#include "../../CoreFunctions/CoreFunctions.h"


Asteroid::Asteroid() {
    sprite.setTexture(asteroidTexture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(rand() % 800, -50); // Random X, start above screen
}


void Asteroid::update(float deltaTime) {
    sprite.move(0, speed * deltaTime);
    sprite.rotate(rotationSpeed * deltaTime);
}

const sf::FloatRect Asteroid::getBounds() const {
    return sprite.getGlobalBounds();
}
