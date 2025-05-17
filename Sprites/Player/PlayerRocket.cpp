//
// Created by yashmathur on 5/17/25.
//

#include "PlayerRocket.h"

#include <complex>

PlayerRocket::PlayerRocket(std::string choice) {

    texture.loadFromFile("Assets/"+choice+"/Idle.png");
    sprite.setTexture(texture);
    this->movementSpeed = 200.0f;
    this->rotationSpeed = 200.0f;

    sf::FloatRect bounds = sprite.getLocalBounds();

    sprite.setOrigin(bounds.width/2, bounds.height/2);
}

void PlayerRocket::move(const float offsetX, const float offsetY) {
    float rot = sprite.getRotation() * 3.14159f / 180.0f;

    sprite.move(-offsetY * movementSpeed * std::cos(rot), -offsetY * movementSpeed * std::sin(rot));
}


void PlayerRocket::rotate(float deltaTime) {
    sprite.rotate(rotationSpeed * deltaTime);
}
