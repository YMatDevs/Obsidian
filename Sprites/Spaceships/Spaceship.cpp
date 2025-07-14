//
// Created by yashmathur on 5/19/25.
//

#include "Spaceship.h"

#include <cmath>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../CoreFunctions/CoreFunctions.h"


// Constructor
Spaceship::Spaceship(int maxSpeed, sf::Vector2f pos,const std::string& choice) {
    // this->maxSpeed = maxSpeed;
    this->position = pos;
    this->currentSpeed = sf::Vector2i(0, 0);

    this->texture.loadFromFile("Assets/"+choice+"/Idle.png");
    this->sprite.setTexture(this->texture);

    const sf::FloatRect bounds = this->sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}


// Movement Function
void Spaceship::move(float deltaTime, bool thrust, const int8_t direction) {

    if (direction != 0) { sprite.rotate(ROTATION_SPEED * deltaTime * static_cast<float>(direction)); }

    const float rotation = sprite.getRotation() * 3.14159f / 180.0f;
    if (thrust) {
        currentSpeed.x += ACCELERATION * deltaTime * std::cos(rotation);
        currentSpeed.y += ACCELERATION * deltaTime * std::sin(rotation);
    }

    currentSpeed.x *= (1.0f - DRAG * deltaTime);
    currentSpeed.y *= (1.0f - DRAG * deltaTime);

    float speed = std::sqrt( currentSpeed.x*currentSpeed.x + currentSpeed.y*currentSpeed.y);
    if ( speed > PLAYER_MAX_SPEED ) { const float scale = PLAYER_MAX_SPEED / speed; currentSpeed.x *= scale; currentSpeed.y *= scale; }

    sprite.move(currentSpeed.x*deltaTime, currentSpeed.y*deltaTime);
}

void Spaceship::stop() { currentSpeed.x = 0.0f; currentSpeed.y = 0.0f; }

